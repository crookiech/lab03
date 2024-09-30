#include <iostream>
#include <fstream>

// Последовательный контейнер
template <typename T>
class Array {
private:
    T* data;
    int size;
    int numberOfElements;

    void resize(int newSize) {
        int* newData = new int[newSize];
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
          resize(size * 2);
      }
      data[numberOfElements++] = value;
  }

  void insert(int index, const T& value) {
      if (index < 0 || index >= numberOfElements) {
          std::cout << "Неверно указан индекс добавляемого элемента!" << std::endl;
          return;
      }
      if (numberOfElements == size) {
          resize(size * 2);
      }
      for (int i = numberOfElements; i > index; --i) {
          data[i] = data[i - 1]; // Сдвиг элементов
      }
      data[index] = value; // Добавление элемента
      ++numberOfElements;
  }

  void erase(int index) {
      if (index < 0 || index >= numberOfElements) {
          std::cout << "Неверно указан индекс удаляемого элемента!" << std::endl;
          return;
      }
      for (int i = index; i < numberOfElements - 1; ++i) {
          data[i] = data[i + 1]; // Сдвиг элементов
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

  int get_size() const {
      return size;
  }
  int get_numberOfElements() const {
      return numberOfElements;
  }
};

// Списковый контейнер
template <typename T>
class List {
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
  List() : head(nullptr), tail(nullptr), numberOfElements(0) {}

  ~List() {
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
    if (index == 0) {
      push_front(value);
      return;
    }
    Node* current = head;
    for (int i = 0; i < index - 1; ++i) {
      current = current->next;
    }
    Node* newNode = new Node(value);
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
      pop_front();
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

  void push_front(const T& value) {
    Node* newNode = new Node(value);
    if (head == nullptr) {
      head = newNode;
      tail = newNode;
    } else {
      newNode->next = head;
      head->previous = newNode;
      head = newNode;
    }
    ++numberOfElements;
  }

  void pop_front() {
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
    if (index >= numberOfElements) {
      return head->value;
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

int main() {
  std::cout << "Пользовательский код с демонстрацией возможностей последовательного контейнера." << std::endl;
  Array<int> array;
  for (int i = 0; i < 10; i++) {
      array.push_back(i);
  }
  std::cout << "В контейнер добавлены числа от 0 до 9: ";
  array.print();
  std::cout << std::endl;
  std::cout << "Размер контейнера: " << array.get_numberOfElements() << std::endl;
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
  array.insert(array.get_numberOfElements() / 2, 20);
  std::cout << "В середину контейнера добавили 20: ";
  array.print();
  std::cout << std::endl;
  array.push_back(30);
  std::cout << "В конец контейнера добавили 30: ";
  array.print();
  std::cout << std::endl;
  std::cout << "Пользовательский код с демонстрацией возможностей контейнера спискового типа." << std::endl;
  List<int> list;
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
  return 0;
}
