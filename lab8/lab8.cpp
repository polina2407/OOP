#include <windows.h>
#include <vector>
#include <cstdlib>
#include <ctime>

// Константы для идентификаторов таймера
#define TIMER_REDRAW 1

// Структура для хранения информации о фигуре
struct Shape {
    int type;       // 0-прямоугольник, 1-круг, 2-треугольник
    int x, y;       // позиция
    int width, height; // размер
    COLORREF color; // цвет
};

// Глобальные переменные
std::vector<Shape> shapes;
COLORREF currentColor = RGB(255, 0, 0); // начальный цвет - красный
bool randomizeSize = false;

// Прототипы функций
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
void DrawShapes(HDC hdc);
void CreateInitialShapes();
void RandomizeSizes();

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    // Инициализация генератора случайных чисел
    srand(static_cast<unsigned int>(time(nullptr)));

    const wchar_t CLASS_NAME[] = L"ShapeWindowClass";

    WNDCLASS wc = {};
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = CLASS_NAME;
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);

    RegisterClass(&wc);

    HWND hwnd = CreateWindowEx(
        0,
        CLASS_NAME,
        L"Рисование фигур - R-красный, G-зеленый, B-синий, S-случайный размер",
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, 800, 600,
        NULL,
        NULL,
        hInstance,
        NULL
    );

    if (hwnd == NULL) {
        return 0;
    }

    // Создаем начальные фигуры
    CreateInitialShapes();

    ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd);

    // Запускаем таймер для периодического обновления
    SetTimer(hwnd, TIMER_REDRAW, 100, NULL);

    MSG msg = {};
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    KillTimer(hwnd, TIMER_REDRAW);
    return 0;
}

// Создание начальных фигур
void CreateInitialShapes() {
    shapes.clear();

    // Прямоугольники
    shapes.push_back({ 0, 100, 100, 120, 80, RGB(255, 0, 0) });
    shapes.push_back({ 0, 300, 120, 150, 100, RGB(0, 255, 0) });

    // Круги
    shapes.push_back({ 1, 500, 100, 100, 100, RGB(0, 0, 255) });
    shapes.push_back({ 1, 200, 300, 120, 120, RGB(255, 255, 0) });

    // Треугольники
    shapes.push_back({ 2, 400, 300, 100, 100, RGB(255, 0, 255) });
    shapes.push_back({ 2, 600, 200, 80, 80, RGB(0, 255, 255) });
}

// Функция для случайного изменения размеров
void RandomizeSizes() {
    for (auto& shape : shapes) {
        shape.width = 50 + rand() % 151;  // от 50 до 200
        shape.height = 50 + rand() % 151; // от 50 до 200
        shape.x = 50 + rand() % 500;      // случайная позиция X
        shape.y = 50 + rand() % 300;      // случайная позиция Y
    }
}

// Функция отрисовки всех фигур
void DrawShapes(HDC hdc) {
    for (const auto& shape : shapes) {
        HBRUSH hBrush = CreateSolidBrush(shape.color);
        HBRUSH hOldBrush = (HBRUSH)SelectObject(hdc, hBrush);
        HPEN hPen = CreatePen(PS_SOLID, 2, RGB(0, 0, 0));
        HPEN hOldPen = (HPEN)SelectObject(hdc, hPen);

        switch (shape.type) {
        case 0: // Прямоугольник
            Rectangle(hdc, shape.x, shape.y, shape.x + shape.width, shape.y + shape.height);
            break;

        case 1: // Круг
            Ellipse(hdc, shape.x, shape.y, shape.x + shape.width, shape.y + shape.height);
            break;

        case 2: // Треугольник
        {
            POINT points[3] = {
                {shape.x + shape.width / 2, shape.y},
                {shape.x, shape.y + shape.height},
                {shape.x + shape.width, shape.y + shape.height}
            };
            Polygon(hdc, points, 3);
            break;
        }
        }

        SelectObject(hdc, hOldBrush);
        SelectObject(hdc, hOldPen);
        DeleteObject(hBrush);
        DeleteObject(hPen);
    }
}

// Оконная процедура
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch (uMsg) {
    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hwnd, &ps);

        // Очищаем область отрисовки
        RECT rect;
        GetClientRect(hwnd, &rect);
        FillRect(hdc, &rect, (HBRUSH)(COLOR_WINDOW + 1));

        // Рисуем фигуры
        DrawShapes(hdc);

        // Выводим инструкции
        SetTextColor(hdc, RGB(0, 0, 0));
        TextOut(hdc, 10, 10,
            L"R-красный G-зеленый B-синий S-случайный размер C-случайный цвет", 70);

        EndPaint(hwnd, &ps);
        break;
    }

    case WM_KEYDOWN:
        switch (wParam) {
        case 'R': // Красный
            currentColor = RGB(255, 0, 0);
            for (auto& shape : shapes) {
                shape.color = currentColor;
            }
            InvalidateRect(hwnd, NULL, TRUE);
            break;

        case 'G': // Зеленый
            currentColor = RGB(0, 255, 0);
            for (auto& shape : shapes) {
                shape.color = currentColor;
            }
            InvalidateRect(hwnd, NULL, TRUE);
            break;

        case 'B': // Синий
            currentColor = RGB(0, 0, 255);
            for (auto& shape : shapes) {
                shape.color = currentColor;
            }
            InvalidateRect(hwnd, NULL, TRUE);
            break;

        case 'S': // Случайный размер
            RandomizeSizes();
            InvalidateRect(hwnd, NULL, TRUE);
            break;

        case 'C': // Случайный цвет для каждой фигуры
            for (auto& shape : shapes) {
                shape.color = RGB(rand() % 256, rand() % 256, rand() % 256);
            }
            InvalidateRect(hwnd, NULL, TRUE);
            break;

        case VK_ESCAPE: // Выход
            PostQuitMessage(0);
            break;
        }
        break;

    case WM_TIMER:
        if (wParam == TIMER_REDRAW) {
            if (randomizeSize) {
                RandomizeSizes();
                InvalidateRect(hwnd, NULL, TRUE);
            }
        }
        break;

    case WM_DESTROY:
        PostQuitMessage(0);
        break;

    default:
        return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }
    return 0;
}