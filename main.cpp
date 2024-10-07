#include <iostream>

// Шаблон класса, который может работать с любым типом данных, представленным параметром T
template <typename T> 
// Последовательный контейнер
class Array {
private:
    T* data; // указатель на динамически выделенную память, в которой хранятся элементы контейнера
    int size; // размер выделенной памяти для контейнера
    int numberOfElements; // количество элементов в контейнере
    // Изменение размера контейнера
    void resize(int newSize) {
        if (newSize == size) {
            return; // изменение размера не требуется
        }
        T* newData = new T[newSize]; // выделение новой памяти размером newSize
        if (newSize > size) {
            std::move(data, data + numberOfElements, newData); // копирование существующих элементов, если новый размер больше
        } else {
            std::move(data, data + newSize, newData); // перемещение элементов, если новый размер меньше
        }
        delete[] data; // освобождение старой памяти
        data = newData; // обновление указателя data на новую память
        size = newSize; // обновление размера size контейнера
    }

public:
    // Структура, представляющая итератор для обхода контейнера
    struct Iterator { 
        T* current; // указатель на текущий элемент в контейнере
        // Конструктор, инициализирующий current указателем на элемент контейнера
        Iterator(T* ptr) : current(ptr) {} 
        // Перегрузка оператора * для получения ссылки на текущий элемент
        T& operator*() { 
            if (current == nullptr) {
                std::cout << "Неверный индекс!" << std::endl;
            }
            return *current;
        }
        // Метод для получения ссылки на текущий элемент
        T& get() { 
            if (current == nullptr) {
                std::cout << "Неверный индекс!" << std::endl;
            }
            return *current;
        }
        // Перегрузка оператора ++ для перехода к следующему элементу контейнера
        Iterator& operator++() { 
            ++current;
            return *this;
        }
        // Перегрузка оператора != для сравнения двух итераторов
        bool operator!=(const Iterator& other) const { 
            return current != other.current;
        }
    };
    // Возвращает итератор, указывающий на первый элемент контейнера
    Iterator begin() { 
        return Iterator(data); 
    }
    // Возвращает итератор, указывающий на элемент, следующий за последним элементом контейнера
    Iterator end() { 
        return Iterator(data + numberOfElements); 
    }
    // Конструктор
    Array() : data(nullptr), size(0), numberOfElements(0) {} // инициализация контейнера с нулевым размером и указателем на nullptr
    // Перемещающий конструктор ?
    Array(Array&& other) noexcept 
        : data(other.data), size(other.size), numberOfElements(other.numberOfElements) {
        other.data = nullptr;
        other.size = 0;
        other.numberOfElements = 0;
    }
    // Перемещающий оператор присваивания ?
    Array& operator=(Array&& other) noexcept {
        if (this != &other) {
            delete[] data;
            data = other.data;
            size = other.size;
            numberOfElements = other.numberOfElements;
            other.data = nullptr;
            other.size = 0;
            other.numberOfElements = 0;
        }
        return *this;
    }
    // Добавление элемента в конец контейнера
    void push_back(const T& value) { 
        if (numberOfElements == size) {
            resize((size * 2) + 1); // увеличение размера контейнера, если количество элементов равно текущему размеру
        }
        data[numberOfElements++] = value; // добавление элемента value в конец контейнера
    }
    // Добавление элемента в контейнер по заданному индексу
    void insert(int index, const T& value) {
        if (index < 0 || index > numberOfElements) {
            std::cout << "Неверный индекс!" << std::endl;
            return;
        }
        if (numberOfElements == size) {
            resize((size * 2) + 1); // увеличение размера контейнера, если количество элементов равно текущему размеру
        }
        for (int i = numberOfElements; i > index; --i) {
            data[i] = data[i - 1]; // сдвиг элементов, начиная с index, на одну позицию вправо, чтобы освободить место для нового элемента
        }
        data[index] = value; // добавление элемента в контейнер по заданному индексу
        ++numberOfElements; // увеличение количества элементов в контейнере на 1
    }
    // Удаление элемента из контейнера по заданному индексу
    void erase(int index) {
        if (index < 0 || index >= numberOfElements) {
            std::cout << "Неверный индекс!" << std::endl;
            return;
        }
        for (int i = index; i < numberOfElements - 1; ++i) {
            data[i] = data[i + 1]; // сдвиг элементов, начиная с index, на одну позицию влево, чтобы заполнить пустоту
        }
        --numberOfElements; // уменьшение количества элементов в контейнере на 1
    }
    // Вывод в консоль всех элементов контейнера, разделенных запятыми
    void print() const {
        for (int i = 0; i < numberOfElements; ++i) {
            std::cout << data[i];
            if (i < numberOfElements - 1) {
                std::cout << ", ";
            }
        }
    }
    // Перегрузка оператора [] для доступа к элементам контейнера по индексу
    int& operator[](int index) {
        return data[index];
    }
    // Возвращает размер выделенной памяти для контейнера
    int get_selectedSize() const {
        return size;
    }
    // Возвращает количество элементов в контейнере
    int get_size() const {
        return numberOfElements;
    }
    // Деструктор
    ~Array() {
        if (data != nullptr) {
            delete[] data; // освобождение памяти, выделенной для контейнера, если она была выделена
        }
    }
};

// Шаблон класса, который может работать с любым типом данных, представленным параметром T
template <typename T>
// Двунаправленный списковый контейнер
class BidirectionalList {
private:
    // Структура, представляющая узел контейнера
    struct Node {
        T value; // значение, хранящееся в узле
        Node* next; // указатель на следующий узел в контейнере
        Node* previous; // указатель на предыдущий узел в контейнере
        // Конструктор
        Node(const T& value) : value(value), next(nullptr), previous(nullptr) {} // инициализация значения узла, установка указателя next и previous в nullptr
    };
    Node* head; // указатель на первый узел контейнера
    Node* tail; // указатель на последний узел контейнера
    int numberOfElements; // количество элементов в контейнере
public:
    // Структура, представляющая итератор для обхода контейнера
    struct Iterator {
        // указатель на текущий узел
        Node* current;
        // Конструктор итератора, инициализирующий его указатель на Node* node
        Iterator(Node* node) : current(node) {}
        // Оператор разыменования 
        T& operator*() {
            if (current == nullptr){
                std::cout << "Неверный индекс!" << std::endl;
            }
            return current->value; // возвращает ссылку на значение текущего узла
        }
        // Возвращает ссылку на значение текущего узла
        T& get() {
            if (current == nullptr) {
                std::cout << "Неверный индекс!" << std::endl;
            }
            return current->value;
        }
        // Перегрузка оператора ++ для перехода к следующему элементу контейнера
        Iterator& operator++() {
            if (current != nullptr) current = current->next;
            return *this;
        }
        // Перегрузка оператора -- для перехода к предыдущему элементу контейнера
        Iterator& operator--() {
            if (current != nullptr && current->previous != nullptr)
                current = current->previous;
            return *this;
        }
        // Перегрузка оператора != для сравнения двух итераторов
        bool operator!=(const Iterator& other) const {
            return current != other.current;
        }
    };
    // Возвращает итератор, указывающий на первый узел списка
    Iterator begin() { 
        return Iterator(head); 
    }
    // Возвращает итератор, указывающий на конец списка
    Iterator end() { 
        return Iterator(nullptr); 
    }
    // Конструктор
    BidirectionalList() : head(nullptr), tail(nullptr), numberOfElements(0) {} // инициализирует контейнер как пустой
    // Перемещающий конструктор ?
    BidirectionalList(BidirectionalList&& other) noexcept 
        :  head(other.head), tail(other.tail), numberOfElements(other.numberOfElements) {
        other.head = nullptr;
        other.tail = nullptr;
        other.numberOfElements = 0;
    }
    // Перемещающий оператор присваивания ?
    BidirectionalList& operator=(BidirectionalList&& other) noexcept {
        if (this != &other) {
            while (head != nullptr) {
                Node* temp = head;
                head = head->next;
                delete temp;
            }
            head = other.head;
            tail = other.tail;
            numberOfElements = other.numberOfElements;
            other.head = nullptr;
            other.tail = nullptr;
            other.numberOfElements = 0;
        }
        return *this;
    }
    // Добавление элемента в конец контейнера ? 
    void push_back(const T& value) {
        Node* newNode = new Node(value); // создание нового узла
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
    // Добавление элемента в контейнер по заданному индексу ?
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
    // Удаление элемента из контейнера по заданному индексу
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
    // Вывод в консоль всех элементов контейнера, разделенных запятыми
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
    // Перегрузка оператора [] для доступа к элементам контейнера по индексу
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
    // Возвращает количество элементов в контейнере
    int get_size() const {
        return numberOfElements;
    }
    // Деструктор ?
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
    struct Iterator {
        Node* current;
        Iterator(Node* node) : current(node) {}
        T& operator*() {
            if (current == nullptr) {
                std::cout << "Неверный индекс!" << std::endl;
            }
            return current->value;
        }

        T& get() {
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

    Iterator begin() { 
        return Iterator(head); 
    }

    Iterator end() { 
        return Iterator(nullptr); 
    }

    UnidirectionalList() : head(nullptr), numberOfElements(0) {}

    // Перемещающий конструктор
    UnidirectionalList(UnidirectionalList&& other) noexcept 
        :  head(other.head), numberOfElements(other.numberOfElements) {
        other.head = nullptr;
        other.numberOfElements = 0;
    }

    // Перемещающий оператор присваивания
    UnidirectionalList& operator=(UnidirectionalList&& other) noexcept {
        if (this != &other) {
            while (head != nullptr) {
                Node* temp = head;
                head = head->next;
                delete temp;
            }
            head = other.head;
            numberOfElements = other.numberOfElements;

            other.head = nullptr;
            other.numberOfElements = 0;
        }
        return *this;
    }    

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
        if (index < 0 || index > numberOfElements) {
            return;
        }
        Node* newNode = new Node(value);
        if (index == 0) {
            newNode->next = head;
            head = newNode;
        } else {
            Node* current = head;
            for (int i = 0; i < index - 1; ++i) {
                current = current->next;
            }
            newNode->next = current->next;
            current->next = newNode;
        }
        ++numberOfElements;
    }

    void erase(int index) {
        if (index < 0 || index >= numberOfElements) {
            return;
        }
        if (index == 0) {
            Node* nodeToRemove = head;
            head = head->next;
            delete nodeToRemove;
        } else {
            Node* current = head;
            for (int i = 0; i < index - 1; ++i) {
                current = current->next;
            }
            Node* nodeToRemove = current->next;
            current->next = nodeToRemove->next;
            delete nodeToRemove;
        }
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
    // Перегрузка оператора [] для доступа к элементам контейнера по индексу
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
    // Возвращает количество элементов в контейнере
    int get_size() const {
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

template <typename Container>
void demonstrateContainer(const std::string& containerName) {
    std::cout << "Пользовательский код с демонстрацией возможностей " << containerName << "." << std::endl;
    Container container;
    for (int i = 0; i < 10; i++) {
        container.push_back(i);
    }
    std::cout << "В контейнер добавлены числа от 0 до 9: ";
    container.print();
    std::cout << std::endl;
    std::cout << "Размер контейнера: " << container.get_size() << std::endl;
    for (int i = 0; i < 3; i++) {
        container.erase(2);
    }
    std::cout << "Из контейнера удалили 3, 5 и 7 элементы (по счету): ";
    container.print();
    std::cout << std::endl;
    container.insert(0, 10);
    std::cout << "В начало контейнера добавили 10: ";
    container.print();
    std::cout << std::endl;
    container.insert(container.get_size() / 2, 20);
    std::cout << "В середину контейнера добавили 20: ";
    container.print();
    std::cout << std::endl;
    container.push_back(30);
    std::cout << "В конец контейнера добавили 30: ";
    container.print();
    std::cout << std::endl;
}

void customCode() {
    demonstrateContainer<Array<int> >("последовательного контейнера");
    std::cout << std::endl;
    demonstrateContainer<BidirectionalList<int> >("двунаправленного контейнера спискового типа");
    std::cout << std::endl;
    demonstrateContainer<UnidirectionalList<int> >("однонаправленного контейнера спискового типа");
}

// Функция для проверки работы перемещения
template <typename Container>
void demonstrateMoveSemantic(const std::string& containerName) {
    std::cout << "Тестирование семантики перемещения " << containerName << "." << std::endl;
    Container container1;
    container1.push_back(1);
    container1.push_back(1);
    container1.push_back(1);
    std::cout << "В контейнер container1 добавили три единицы: ";
    container1.print();
    std::cout << std::endl;
    Container container2 = std::move(container1); // Перемещение контейнера
    std::cout << "В контейнер container2 переместили контейнер container1: ";
    container2.print(); // Проверяем содержимое второго контейнера
    std::cout << std::endl;
    std::cout << "Содержимое контейнера container1 после перемещения: ";
    container1.print(); // Проверяем содержимое первого контейнера (должен быть пустым)
    std::cout << std::endl;
    if (container1.get_size() == 0) {
        std::cout << "container1 успешно перемещен и теперь пуст." << std::endl;
    } else {
        std::cout << "Ошибка: container1 не пуст!" << std::endl;
    }
    Container container3;
    container3.push_back(0);
    container3.push_back(0);
    container3.push_back(0);
    container3.push_back(0);
    std::cout << "В контейнер container3 добавили четыре нуля: ";
    container3.print();
    std::cout << std::endl;
    container3 = std::move(container2); // Перемещение с использованием оператора присваивания
    std::cout << "В контейнер container3 переместили контейнер container2: ";
    container3.print(); // Проверяем содержимое третьего контейнера
    std::cout << std::endl;
    std::cout << "Содержимое контейнера container2 после перемещения: ";
    container2.print(); // Проверяем содержимое второго контейнера (должен быть пустым)
    std::cout << std::endl;
    if (container2.get_size() == 0) {
        std::cout << "container2 успешно перемещен и теперь пуст." << std::endl;
    } else {
        std::cout << "Ошибка: container2 не пуст!" << std::endl;
    }
    std::cout << std::endl;
}

void testMoveSemantic() {
    demonstrateMoveSemantic<Array<int> >("последовательного контейнера");
    std::cout << std::endl;
    demonstrateMoveSemantic<BidirectionalList<int> >("двунаправленного контейнера спискового типа");
    std::cout << std::endl;
    demonstrateMoveSemantic<UnidirectionalList<int> >("однонаправленного контейнера спискового типа");
}

template <typename Container>
void demonstrateTestIterators(const std::string& containerName) {
    std::cout << "Тест итератора для " << containerName << "." << std::endl;
    Container container;
    for (int i = -5; i < 0; ++i) {
        container.push_back(i);
    }
    std::cout << "Содержимое контейнера, выведенное с помощью итератора: ";
    for (auto it = container.begin(); it != container.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
}

void testIterators() {
    demonstrateTestIterators<Array<int> >("последовательного контейнера");
    std::cout << std::endl;
    demonstrateTestIterators<BidirectionalList<int> >("двунаправленного контейнера спискового типа");
    std::cout << std::endl;
    demonstrateTestIterators<UnidirectionalList<int> >("однонаправленного контейнера спискового типа");
}

int main() {
    customCode();
    std::cout << std::endl;
    std::cout << "Пользовательский код с демонстрацией возможностей последовательного контейнера с резервированием памяти." << std::endl;
    Array<int> array;
    for (int i = 0; i < 10; i++) {
        array.push_back(i);
    }
    std::cout << "В контейнер добавлены числа от 0 до 9: ";
    array.print();
    std::cout << std::endl;
    std::cout << "Количество элементов в контейнере: " << array.get_size() << std::endl;
    std::cout << "Размер контейнера: " << array.get_selectedSize() << std::endl;
    std::cout << std::endl;
    testMoveSemantic();
    std::cout << std::endl;
    testIterators();
    std::cout << std::endl;
    return 0;
}
