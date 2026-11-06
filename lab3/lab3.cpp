#include <iostream>
#include <cmath>
#include <vector>
using namespace std;

class Shape {
public:
    virtual double area() const = 0;         
    virtual double perimeter() const = 0;    
    virtual void display() const = 0;        
    virtual ~Shape() {}                      
};

class Circle : public Shape {
private:
    double radius;
public:
    Circle(double r) : radius(r) {}

    double area() const override {
        return M_PI * radius * radius;
    }

    double perimeter() const override {
        return 2 * M_PI * radius;
    }

    void display() const override {
        cout << "Круг: радиус = " << radius
            << ", площадь = " << area()
            << ", периметр = " << perimeter() << endl;
    }
};

class Triangle : public Shape {
private:
    double a, b, c;
public:
    Triangle(double side1, double side2, double side3)
        : a(side1), b(side2), c(side3) {}

    double area() const override {
        double s = (a + b + c) / 2.0; // Полупериметр
        return sqrt(s * (s - a) * (s - b) * (s - c)); // Формула Герона
    }

    double perimeter() const override {
        return a + b + c;
    }

    void display() const override {
        cout << "Треугольник: стороны = (" << a << ", " << b << ", " << c << ")"
            << ", площадь = " << area()
            << ", периметр = " << perimeter() << endl;
    }
};

class ShapeManager {
private:
    vector<Shape*> shapes;
public:
    ~ShapeManager() {
        for (auto s : shapes)
            delete s;
    }

    void addShape(Shape* s) {
        shapes.push_back(s);
    }

    void removeShape(size_t index) {
        if (index < 1 || index > shapes.size()) {
            cout << "Неверный индекс!\n";
            return;
        }
        delete shapes[index - 1];
        shapes.erase(shapes.begin() + (index - 1));
        cout << "Фигура удалена!\n";
    }

    void displayAll() const {
        if (shapes.empty()) {
            cout << "Коллекция фигур пуста.\n";
            return;
        }
        cout << "\nСписок всех фигур:\n";
        for (size_t i = 0; i < shapes.size(); ++i) {
            cout << "[" << i + 1 << "] ";
            shapes[i]->display();
        }
    }

    double totalArea() const {
        double sum = 0;
        for (auto s : shapes)
            sum += s->area();
        return sum;
    }

    double totalPerimeter() const {
        double sum = 0;
        for (auto s : shapes)
            sum += s->perimeter();
        return sum;
    }
};

int main() {
    setlocale(LC_ALL, "Russian");

    ShapeManager manager;
    int choice;

    do {
        cout << " === МЕНЮ === \n";
        cout << "1. Добавить круг\n";
        cout << "2. Добавить треугольник\n";
        cout << "3. Удалить фигуру\n";
        cout << "4. Показать все фигуры\n";
        cout << "5. Показать общую площадь и периметр\n";
        cout << "0. Выход\n";
        cout << "Ваш выбор: ";
        cin >> choice;

        switch (choice) {
        case 1: {
            double r;
            cout << "Введите радиус круга: ";
            cin >> r;
            manager.addShape(new Circle(r));
            cout << "Круг добавлен!\n";
            break;
        }
        case 2: {
            double a, b, c;
            cout << "Введите три стороны треугольника: ";
            cin >> a >> b >> c;
            if (a + b > c && a + c > b && b + c > a) {
                manager.addShape(new Triangle(a, b, c));
                cout << "Треугольник добавлен!\n";
            }
            else {
                cout << "Такой треугольник невозможен!\n";
            }
            break;
        }
        case 3: {
            size_t index;
            cout << "Введите номер фигуры для удаления: ";
            cin >> index;
            manager.removeShape(index);
            break;
        }
        case 4:
            manager.displayAll();
            break;
        case 5:
            cout << "Общая площадь всех фигур: " << manager.totalArea() << endl;
            cout << "Общий периметр всех фигур: " << manager.totalPerimeter() << endl;
            break;
        case 0:
            cout << "Выход из программы...\n";
            break;
        default:
            cout << "Неверный выбор. Попробуйте снова.\n";
        }
    } while (choice != 0);

    return 0;
}
