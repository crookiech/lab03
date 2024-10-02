#include <iostream>

// Последовательный контейнер
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
    struct Iterator {
        T* current;

        Iterator(T* ptr) : current(ptr) {}

        T& operator*() {
            if (current == nullptr) {
                std::cout << "Неверный индекс!" << std::endl;
            }
            return *current;
        }

        Iterator& operator++() {
            ++current; // Переход к следующему элементу
            return *this;
        }

        bool operator!=(const Iterator& other) const {
            return current != other.current;
        }
    };

    Array() : data(nullptr), size(0), numberOfElements(0) {}

    void push_back(const T& value) {
        if (numberOfElements == size) {
            resize((size * 2) + 1);
        }
        data[numberOfElements++] = value;
    }

    void insert(int index, const T& value) {
        if (index < 0 || index > numberOfElements) {
            std::cout << "Неверный индекс!" << std::endl;
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
            std::cout << "Неверный индекс!" << std::endl;
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

    ~Array() {
        if (data != nullptr) {
            delete[] data;
        }
    }
};

// Двунаправленный списковый контейнер
template <typename T>
class BidirectionalList {
private:
    struct Node {
        T value;
        Node* next;
        Node* previous;
        Node(const T& value) : value(value), next(nullptr), previous(nullptr) {}
    };

    Node* head;
    Node* tail;
    int numberOfElements;

public:
    struct Iterator {
        Node* current;

        Iterator(Node* node) : current(node) {}

        T& operator*() {
            if (current == nullptr){
                std::cout << "Неверный индекс!" << std::endl;
            }
            return current->value;
        }

        Iterator& operator++() {
            if (current != nullptr) current = current->next;
            return *this;
        }

        Iterator& operator--() {
            if (current != nullptr && current->prev != nullptr)
                current = current->prev;
            return *this;
        }

        bool operator!=(const Iterator& other) const {
            return current != other.current;
        }
    };

    Iterator begin() { return Iterator(head); }
    Iterator end() { return Iterator(nullptr); }

    BidirectionalList() : head(nullptr), tail(nullptr), numberOfElements(0) {}

    void push_back(const T& value) {
        Node* newNode = new Node(value);
        if (head == nullptr) {
            head = newNode;
            tail = newNode;
        } else {
            tail->next = newNode;
            newNode->previous = tail;
            tail = newNode;
        }
        ++numberOfElements;
    }

    void insert(int index, const T& value) {
        if (index > numberOfElements) {
            return;
        }
        Node* newNode = new Node(value);
        if (index == 0) {
            if (head == nullptr) {
                head = newNode;
                tail = newNode;
            } else {
                newNode->next = head;
                head->previous = newNode;
                head = newNode;
            }
            ++numberOfElements;
            return;
        }
        Node* current = head;
        for (int i = 0; i < index - 1; ++i) {
            current = current->next;
        }
        newNode->next = current->next;
        current->next = newNode;
        newNode->previous = current;
        if (newNode->next != nullptr) {
            newNode->next->previous = newNode;
        } else {
            tail = newNode;
        }
        ++numberOfElements;
    }

    void erase(int index) {
        if (index >= numberOfElements) {
            return;
        }
        if (index == 0) {
            if (head == nullptr) {
                return;
            }
            Node* nodeToRemove = head;
            head = head->next;
            if (head != nullptr) {
                head->previous = nullptr;
            } else {
                tail = nullptr;
            }
            delete nodeToRemove;
            --numberOfElements;
            return;
        }
        Node* current = head;
        for (int i = 0; i < index - 1; ++i) {
            current = current->next;
        }
        Node* nodeToRemove = current->next;
        current->next = nodeToRemove->next;
        if (nodeToRemove->next != nullptr) {
            nodeToRemove->next->previous = current;
        } else {
            tail = current;
        }
        delete nodeToRemove;
        --numberOfElements;
    }

    void print() const {
        Node* current = head;
        while (current != nullptr) {
            std::cout << current->value;
            if (current->next != nullptr) {
                std::cout << ", ";
            }
            current = current->next;
        }
    }

    T& operator[](int index) {
        if (index < 0 || index >= numberOfElements) {
            std::cout << "Неверный индекс!" << std::endl;
        }
        Node* current = head;
        for (int i = 0; i < index; ++i) {
            current = current->next;
        }
            return current->value;
        }

    int get_numberOfElements() const {
        return numberOfElements;
    }

    ~BidirectionalList() {
        Node* current = head;
        while (current != nullptr) {
            Node* next = current->next;
            delete current;
            current = next;
        }
    }
};

// Однонаправленный списковый контейнер
template <typename T>
class UnidirectionalList {
private:
  struct Node {
    T value;
    Node* next;
    Node(const T& value) : value(value), next(nullptr) {}
  };

  Node* head;
  int numberOfElements;

public:
    UnidirectionalList() : head(nullptr), numberOfElements(0) {}

    struct Iterator {
        Node* current;
        Iterator(Node* node) : current(node) {}
        T& operator*() {
            if (current == nullptr) {
                std::cout << "Неверный индекс!" << std::endl;
            }
            return current->value;
        }
        Iterator& operator++() {
            if (current != nullptr) {
                current = current->next;
            }
            return *this;
        }
        bool operator!=(const Iterator& other) const {
            return current != other.current;
        }
    };

    Iterator begin() { return Iterator(head); }
    Iterator end() { return Iterator(nullptr); }

    void push_back(const T& value) {
        Node* newNode = new Node(value);
        if (head == nullptr) {
            head = newNode;
        } else {
            Node* current = head;
            while (current->next != nullptr) {
                current = current->next;
            }
            current->next = newNode;
        }
        ++numberOfElements;
    }

    void insert(int index, const T& value) {
        if (index < 0 || index > numberOfElements) { // Исправлено условие
            return;
        }
        Node* newNode = new Node(value);
        if (index == 0) {
            newNode->next = head; // Устанавливаем новый узел как голову
            head = newNode;
        } else {
            Node* current = head;
            for (int i = 0; i < index - 1; ++i) {
                current = current->next;
            }
            newNode->next = current->next; // Устанавливаем следующий узел
            current->next = newNode; // Устанавливаем новый узел
        }
        ++numberOfElements;
    }

    void erase(int index) {
        if (index < 0 || index >= numberOfElements) { // Исправлено условие
            return;
        }
        if (index == 0) {
            Node* nodeToRemove = head;
            head = head->next; // Перемещаем голову
            delete nodeToRemove; // Удаляем узел
        } else {
            Node* current = head;
            for (int i = 0; i < index - 1; ++i) {
                current = current->next; // Находим предыдущий узел
            }
            Node* nodeToRemove = current->next; // Узел для удаления
            current->next = nodeToRemove->next; // Пропускаем удаляемый узел
            delete nodeToRemove; // Удаляем узел
        }
        --numberOfElements; // Уменьшаем счетчик элементов
    }

    void print() const {
        Node* current = head;
        while (current != nullptr) {
            std::cout << current->value;
            if (current->next != nullptr) {
                std::cout << ", ";
            }
            current = current->next;
        }
        std::cout << std::endl; // Добавлено для лучшего форматирования вывода
    }

    T& operator[](int index) {
        if (index < 0 || index >= numberOfElements) { // Исправлено условие
            std::cout << "Неверный индекс!" << std::endl;
        }
        Node* current = head;
        for (int i = 0; i < index; ++i) {
            current = current->next;
        }
        return current->value; // Возвращаем значение узла
    }

    int get_numberOfElements() const {
        return numberOfElements;
    }

    ~UnidirectionalList() {
        Node* current = head;
        while (current != nullptr) {
            Node* next = current->next;
            delete current;
            current = next;
        }
    }
};

// Функция-тест для проверки работы итераторов
void testIterators() {
    // Тестирование односвязного списка
    UnidirectionalList<int> ulist;

    for (int i = 0; i < 5; ++i) {
        ulist.push_back(i);
    }

    std::cout << "Односвязный список: ";
    for (auto it = ulist.begin(); it != ulist.end(); ++it) {
        std::cout << *it << " "; // Вывод значений
    }
    std::cout << std::endl;

    // Тестирование двусвязного списка
    BidirectionalList<int> blist;

    for (int i = 5; i < 10; ++i) {
        blist.push_back(i);
    }

    std::cout << "Двусвязный список: ";
    for (auto it = blist.begin(); it != blist.end(); ++it) {
        std::cout << *it << " "; // Вывод значений
    }
    std::cout << std::endl;
}

int main() {
    std::cout << "Пользовательский код с демонстрацией возможностей последовательного контейнера." << std::endl;
    Array<int> array;
    for (int i = 0; i < 10; i++) {
        array.push_back(i);
    }
    std::cout << "В контейнер добавлены числа от 0 до 9: ";
    array.print();
    std::cout << std::endl;
    std::cout << "Размер контейнера: " << array.get_size() << std::endl;
    array.erase(2);
    array.erase(3);
    array.erase(4);
    std::cout << "Из контейнера удалили 3, 5 и 7 элементы (по счету): ";
    array.print();
    std::cout << std::endl;
    array.insert(0, 10);
    std::cout << "В начало контейнера добавили 10: ";
    array.print();
    std::cout << std::endl;
    array.insert(array.get_size() / 2, 20);
    std::cout << "В середину контейнера добавили 20: ";
    array.print();
    std::cout << std::endl;
    array.push_back(30);
    std::cout << "В конец контейнера добавили 30: ";
    array.print();
    std::cout << std::endl;
    std::cout << "Пользовательский код с демонстрацией возможностей контейнера спискового типа." << std::endl;
    BidirectionalList<int> list;
    for (int i = 0; i < 10; i++) {
        list.push_back(i);
    }
    std::cout << "В контейнер добавлены числа от 0 до 9: ";
    list.print();
    std::cout << std::endl;
    std::cout << "Размер контейнера: " << list.get_numberOfElements() << std::endl;
    list.erase(2);
    list.erase(3);
    list.erase(4);
    std::cout << "Из контейнера удалили 3, 5 и 7 элементы (по счету): ";
    list.print();
    std::cout << std::endl;
    list.insert(0, 10);
    std::cout << "В начало контейнера добавили 10: ";
    list.print();
    std::cout << std::endl;
    list.insert(list.get_numberOfElements() / 2, 20);
    std::cout << "В середину контейнера добавили 20: ";
    list.print();
    std::cout << std::endl;
    list.push_back(30);
    std::cout << "В конец контейнера добавили 30: ";
    list.print();
    std::cout << std::endl;
    std::cout << "Пользовательский код с демонстрацией возможностей последовательного контейнера с резервированием памяти." << std::endl;
    Array<int> array2;
    for (int i = 0; i < 10; i++) {
        array2.push_back(i);
    }
    std::cout << "В контейнер добавлены числа от 0 до 9: ";
    array2.print();
    std::cout << std::endl;
    std::cout << "Количество элементов в контейнере: " << array2.get_size() << std::endl;
    std::cout << "Размер контейнера: " << array.get_selectedSize() << std::endl;
    testIterators();
    return 0;
}
