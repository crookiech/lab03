#include <iostream>

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
    BidirectionalList() : head(nullptr), tail(nullptr), numberOfElements(0) {}

    ~BidirectionalList() {
        Node* current = head;
        while (current != nullptr) {
            Node* next = current->next;
            delete current;
            current = next;
        }
    }

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
            std::cout << "Неверный индекс элемента списка!" << std::endl;
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

    ~UnidirectionalList() {
        Node* current = head;
        while (current != nullptr) {
            Node* next = current->next;
            delete current;
            current = next;
        }
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
            std::cout << "Неверный индекс элемента списка!" << std::endl;
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
};

// int main() {
//   std::cout << "Пользовательский код с демонстрацией возможностей контейнера спискового типа." << std::endl;
//   UnidirectionalList<int> list;
//   list.insert(0, -2);
//   list.insert(1, -1);
//   for (int i = 0; i < 10; i++) {
//       list.push_back(i);
//   }
//   std::cout << "контейнер: ";
//   list.print();
// }