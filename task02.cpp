#include <iostream>

// Последовательный контейнер с резервированием памяти
template <typename T>
class Array {
private:
    T* data;
    int size;
    int numberOfElements;

    void resize(int newSize) {
        int* newData = new T[newSize];
        for (int i = 0; i < numberOfElements; ++i) {
            newData[i] = data[i];
        }
        delete[] data;
        data = newData;
        size = newSize;
    }

public:
    Array() : data(nullptr), size(0), numberOfElements(0) {}

    ~Array() {
        if (data != nullptr) {
            delete[] data;
        }
    }

    void push_back(const T& value) {
        if (numberOfElements == size) {
            resize((size * 2) + 1);
        }
        data[numberOfElements++] = value;
    }

    void insert(int index, const T& value) {
        if (index < 0 || index > numberOfElements) {
            std::cout << "Неверно указан индекс добавляемого элемента!" << std::endl;
            return;
        }
        if (numberOfElements == size) {
            resize((size * 2) + 1);
        }
        for (int i = numberOfElements; i > index; --i) {
            data[i] = data[i - 1];
        }
        data[index] = value;
        ++numberOfElements;
    }

    void erase(int index) {
        if (index < 0 || index >= numberOfElements) {
            std::cout << "Неверно указан индекс удаляемого элемента!" << std::endl;
            return;
        }
        for (int i = index; i < numberOfElements - 1; ++i) {
            data[i] = data[i + 1];
        }
        --numberOfElements;
        }

    void print() const {
        for (int i = 0; i < numberOfElements; ++i) {
            std::cout << data[i];
            if (i < numberOfElements - 1) {
            std::cout << ", ";
            }
        }
    }

    int& operator[](int index) {
        return data[index];
    }

    std::ostream& operator<<(std::ostream& os) const {
        for (int i = 0; i < numberOfElements; ++i) {
            os << data[i]; 
            if (i < numberOfElements - 1) {
            os << ", ";
            }
        }
        return os;
    }

    int get_selectedSize() const {
        return size;
    }

    int get_size() const {
        return numberOfElements;
    }
};

// int main() {
//     std::cout << "Пользовательский код с демонстрацией возможностей последовательного контейнера с резервированием памяти." << std::endl;
//     Array<int> array;
//     for (int i = 0; i < 10; i++) {
//         array.push_back(i);
//     }
//     std::cout << "В контейнер добавлены числа от 0 до 9: ";
//     array.print();
//     std::cout << std::endl;
//     std::cout << "Количество элементов в контейнере: " << array.get_size() << std::endl;
//     std::cout << "Размер контейнера: " << array.get_selectedSize() << std::endl;
//     return 0;
// }