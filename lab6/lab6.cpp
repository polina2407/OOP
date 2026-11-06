#include <iostream>

class DynamicArray {
private:
    int* data;
    size_t size;

public:
  
    DynamicArray(size_t n) : size(n) {
        data = new int[n];
    }

    
    ~DynamicArray() {
        delete[] data;
    }

    
    class Iterator {
    private:
        int* ptr;
    public:
        Iterator(int* p) : ptr(p) {}

        int& operator*() {
            return *ptr;
        }

       
        Iterator& operator++() {
            ++ptr;
            return *this;
        }

        
        Iterator operator++(int) {
            Iterator temp = *this;
            ++ptr;
            return temp;
        }

        Iterator& operator--() {
            --ptr;
            return *this;
        }

        Iterator operator--(int) {
            Iterator temp = *this;
            --ptr;
            return temp;
        }

      
        bool operator!=(const Iterator& other) const {
            return ptr != other.ptr;
        }

        bool operator==(const Iterator& other) const {
            return ptr == other.ptr;
        }
    };


    Iterator begin() {
        return Iterator(data);
    }

    Iterator end() {
        return Iterator(data + size);
    }

    
    Iterator at(size_t index) {
        if (index >= size) {
            std::cout << "Ошибка: индекс " << index << " вне диапазона (0.." << size - 1 << ")." << std::endl;
            return end(); 
        }
        return Iterator(data + index);
    }

  
    void input() {
        std::cout << "Введите " << size << " целых чисел для массива:\n";
        for (size_t i = 0; i < size; ++i) {
            std::cout << "Элемент [" << i << "]: ";
            std::cin >> data[i];
        }
    }

    size_t getSize() const {
        return size;
    }
};

int main() {
    setlocale(LC_ALL, "Russian"); 

    size_t n;
    std::cout << "Введите размер массива: ";
    std::cin >> n;

    DynamicArray arr(n);
    arr.input();

    std::cout << "Элементы массива: ";
    for (auto it = arr.begin(); it != arr.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

  
    double sum = 0;
    for (auto it = arr.begin(); it != arr.end(); ++it) {
        sum += *it;
    }
    double average = sum / arr.getSize();
    std::cout << "Среднее значение элементов: " << average << std::endl;

    size_t index;
    std::cout << "Введите индекс элемента, который нужно вывести: ";
    std::cin >> index;

    auto it = arr.at(index);
    if (it != arr.end()) {
        std::cout << "Элемент с индексом " << index << ": " << *it << std::endl;
    }

    return 0;
}
