#include <iostream>
#include <fstream>
#include <string>

using namespace std;

void writeInputFile() {
    ofstream outFile("input.txt");
    if (!outFile.is_open()) {
        cerr << "Ошибка: не удалось создать файл input.txt!" << endl;
        return;
    }

    int linesCount;
    cout << "Введите количество строк: ";
    cin >> linesCount;
    cin.ignore();

    string line;
    cout << "Введите текст (" << linesCount << " строк):" << endl;
    for (int i = 0; i < linesCount; ++i) {
        cout << i + 1 << ": ";
        getline(cin, line);
        outFile << line << endl;
    }

    outFile.close();
    if (outFile.fail()) {
        cerr << "Ошибка при закрытии файла input.txt!" << endl;
    }
    else {
        cout << "Файл input.txt успешно создан." << endl;
    }
}

void copyFile() {
    ifstream inFile("input.txt");
    if (!inFile.is_open()) {
        cerr << "Ошибка: входной файл input.txt не найден!" << endl;
        return;
    }

    ofstream outFile("output.txt");
    if (!outFile.is_open()) {
        cerr << "Ошибка: не удалось создать файл output.txt!" << endl;
        inFile.close();
        return;
    }

    string line;
    while (getline(inFile, line)) {
        outFile << line << endl;
    }

    inFile.close();
    outFile.close();

    cout << "Файл успешно скопирован в output.txt." << endl;
}

void compareFiles() {
    ifstream file1("input.txt");
    ifstream file2("output.txt");

    if (!file1.is_open()) {
        cerr << "Ошибка: файл input.txt не найден!" << endl;
        return;
    }
    if (!file2.is_open()) {
        cerr << "Ошибка: файл output.txt не найден!" << endl;
        file1.close();
        return;
    }

    string line1, line2;
    int lineNumber = 0;
    bool identical = true;

    while (getline(file1, line1) && getline(file2, line2)) {
        lineNumber++;
        if (line1 != line2) {
            cout << "Различие в строке " << lineNumber << ":" << endl;
            cout << "input.txt: " << line1 << endl;
            cout << "output.txt: " << line2 << endl;
            identical = false;
           
        }
    }

    if (file1.eof() && getline(file2, line2)) {
        cout << "output.txt имеет больше строк (начиная со строки " << lineNumber + 1 << ")" << endl;
        identical = false;
    }
    else if (file2.eof() && getline(file1, line1)) {
        cout << "input.txt имеет больше строк (начиная со строки " << lineNumber + 1 << ")" << endl;
        identical = false;
    }

    file1.close();
    file2.close();

    if (identical) {
        cout << "Файлы идентичны." << endl;
    }
    else {
        cout << "Файлы имеют различия." << endl;
    }
}

void clearInputFile() {
    ofstream outFile("input.txt", ios::trunc);
    if (!outFile.is_open()) {
        cerr << "Ошибка: не удалось открыть файл input.txt для очистки!" << endl;
        return;
    }
    outFile.close();
    cout << "Файл input.txt успешно очищен." << endl;
}

void clearOutputFile() {
    ofstream outFile("output.txt", ios::trunc);
    if (!outFile.is_open()) {
        cerr << "Ошибка: не удалось открыть файл output.txt для очистки!" << endl;
        return;
    }
    outFile.close();
    cout << "Файл output.txt успешно очищен." << endl;
}

void clearBothFiles() {
    clearInputFile();
    clearOutputFile();
}

int main() {
    setlocale(LC_ALL, "RU");

    int choice;
    do {
        cout << "\n1. Ввести текст и сохранить в input.txt" << endl;
        cout << "2. Скопировать input.txt в output.txt" << endl;
        cout << "3. Сравнить файлы input.txt и output.txt" << endl;
        cout << "4. Очистить input.txt" << endl;
        cout << "5. Очистить output.txt" << endl;
        cout << "6. Очистить оба файла" << endl;
        cout << "7. Выход" << endl;
        cout << "Выберите пункт меню: ";
        cin >> choice;
        cin.ignore(); 

        switch (choice) {
        case 1:
            writeInputFile();
            break;
        case 2:
            copyFile();
            break;
        case 3:
            compareFiles();
            break;
        case 4:
            clearInputFile();
            break;
        case 5:
            clearOutputFile();
            break;
        case 6:
            clearBothFiles();
            break;
        case 7:
            cout << "Выход из программы..." << endl;
            break;
        default:
            cout << "Неверный выбор! Попробуйте снова." << endl;
        }

    } while (choice != 7);

    return 0;
}