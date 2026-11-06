#include <iostream>
#include <string>
using namespace std;



template <typename T>
class Stack {
private:
    T* data;        
    int top;       
    int capacity;  

public:
    Stack(int size = 10) {
        capacity = size;
        data = new T[capacity];
        top = -1;
    }

    ~Stack() {
        delete[] data;
    }

    void push(T value) {
        if (top == capacity - 1) {
            cout << "Ошибка: стек переполнен!" << endl;
            return;
        }
        data[++top] = value;
    }

    T pop() {
        if (isEmpty()) {
            cout << "Ошибка: стек пуст, нельзя извлечь элемент!" << endl;
            return T(); 
        }
        return data[top--];
    }

    bool isEmpty() const {
        return top == -1;
    }


    int size() const {
        return top + 1;
    }


    T peek() const {
        if (isEmpty()) {
            cout << "Ошибка: стек пуст!" << endl;
            return T();
        }
        return data[top];
    }

 
    T getElement(int index) const {
        if (index < 0 || index > top)
            return T();
        return data[index];
    }
};

template <typename T>
bool isStackEmpty(const Stack<T>& stack) {
    return stack.isEmpty();
}

template <typename T>
void printStack(const Stack<T>& stack) {
    if (stack.isEmpty()) {
        cout << "[Стек пуст]" << endl;
        return;
    }

    cout << "Содержимое стека (сверху вниз):" << endl;
    for (int i = stack.size() - 1; i >= 0; i--) {
        cout << stack.getElement(i) << endl;
    }
}

template <typename T>
void stackMenu(Stack<T>& stack) {
    int choice;
    T value;

    do {
        cout << "1. Добавить элемент в стек" << endl;
        cout << "2. Извлечь элемент из стека" << endl;
        cout << "3. Посмотреть верхний элемент" << endl;
        cout << "4. Проверить, пуст ли стек" << endl;
        cout << "5. Показать содержимое стека" << endl;
        cout << "0. Выход в главное меню" << endl;
        cout << "Выберите действие: ";
        cin >> choice;

        switch (choice) {
        case 1:
            cout << "Введите значение: ";
            cin >> value;
            stack.push(value);
            break;

        case 2:
            cout << "Извлечено: " << stack.pop() << endl;
            break;

        case 3:
            cout << "Верхний элемент: " << stack.peek() << endl;
            break;

        case 4:
            cout << (isStackEmpty(stack) ? "Стек пуст" : "Стек не пуст") << endl;
            break;

        case 5:
            printStack(stack);
            break;

        case 0:
            cout << "Возврат в главное меню..." << endl;
            break;

        default:
            cout << "Ошибка: неверный выбор!" << endl;
            break;
        }
    } while (choice != 0);
}

int main() {
    setlocale(LC_ALL, "Russian");
    int mainChoice;

    do {
 
        cout << "1. Стек типа int" << endl;
        cout << "2. Стек типа double" << endl;
        cout << "3. Стек типа string" << endl;
        cout << "0. Выход из программы" << endl;
        cout << "Выберите тип стека: ";
        cin >> mainChoice;

        switch (mainChoice) {
        case 1: {
            Stack<int> intStack(10);
            stackMenu(intStack);
            break;
        }
        case 2: {
            Stack<double> doubleStack(10);
            stackMenu(doubleStack);
            break;
        }
        case 3: {
            Stack<string> stringStack(10);
            stackMenu(stringStack);
            break;
        }
        case 0:
            cout << "Программа завершена." << endl;
            break;
        default:
            cout << "Ошибка: неверный выбор!" << endl;
            break;
        }
    } while (mainChoice != 0);

    return 0;
}
