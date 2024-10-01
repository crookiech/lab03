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
    testIterators(); // Запуск функции-теста
    return 0;
}
