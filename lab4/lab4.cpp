#include <iostream>
using namespace std;

class Person {
protected:
    string name;
    int age;
public:
    Person(string name = "", int age = 0) : name(name), age(age) {}
    void setPersonData() {
        cout << "Введите имя: ";
        cin >> name;
        cout << "Введите возраст: ";
        cin >> age;
    }
    void showInfo() {
        cout << "Имя: " << name << ", Возраст: " << age << endl;
    }
};

class Employee : public Person {
private:
    static int employeeCount;
    int* salaries;
    int numSalaries;
public:
    Employee() {
        salaries = nullptr;
        numSalaries = 0;
        employeeCount++;
    }

    ~Employee() {
        delete[] salaries;
    }

    void setEmployeeData() {
        setPersonData();
        cout << "Введите количество зарплат: ";
        cin >> numSalaries;
        salaries = new int[numSalaries];
        cout << "Введите " << numSalaries << " зарплат(ы): ";
        for (int i = 0; i < numSalaries; ++i) {
            cin >> salaries[i];
        }
    }

    int totalSalary() {
        int sum = 0;
        for (int i = 0; i < numSalaries; ++i) {
            sum += salaries[i];
        }
        return sum;
    }

    double averageSalary() {
        if (numSalaries == 0) return 0;
        return static_cast<double>(totalSalary()) / numSalaries;
    }

    static int getEmployeeCount() {
        return employeeCount;
    }

    void showEmployeeInfo() {
        showInfo();
        cout << "Общая сумма зарплат: " << totalSalary() << endl;
        cout << "Средняя зарплата: " << averageSalary() << endl;
    }
};

int Employee::employeeCount = 0;

int main() {
    setlocale(LC_ALL, "Russian");

    Employee** employees = nullptr; 
    int employeeCount = 0;
    char choice;
    do {
        Employee** temp = new Employee* [employeeCount + 1];
        for (int i = 0; i < employeeCount; ++i) {
            temp[i] = employees[i];
        }

        Employee* emp = new Employee();
        cout << "\nВвод данных для нового сотрудника:" << endl;
        emp->setEmployeeData();
        temp[employeeCount] = emp;

        delete[] employees;
        employees = temp;
        employeeCount++;

        cout << "Добавить ещё одного сотрудника? (1/0): ";
        cin >> choice;

    } while (choice == '1');

    cout << "\nИнформация о сотрудниках:" << endl;
    for (int i = 0; i < employeeCount; ++i) {
        cout << "\nСотрудник " << i + 1 << ":" << endl;
        employees[i]->showEmployeeInfo();
    }

    cout << "\nОбщее количество сотрудников: " << Employee::getEmployeeCount() << endl;

  
    for (int i = 0; i < employeeCount; ++i) {
        delete employees[i];
    }
    delete[] employees;

    return 0;
}
