#include <iostream>
#include <cassert>
#include <memory>

// Task 3: std::weak_ptr для предотвращения циклических ссылок
//
// Реализуйте класс Node, который:
// 1. Использует shared_ptr для связи вперед
// 2. Использует weak_ptr для связи назад (предотвращение циклических ссылок)
// 3. Правильно обрабатывает освобождение памяти

class Node {
    int value_;
    std::shared_ptr<Node> next_;
    std::weak_ptr<Node> prev_;  // Слабая ссылка для предотвращения циклических ссылок
    
public:
    Node(int value) : value_(value) {
        std::cout << "Node " << value_ << " created\n";
    }
    
    ~Node() {
        std::cout << "Node " << value_ << " destroyed\n";
    }
    
    // TODO: Установить следующий узел
    void setNext(std::shared_ptr<Node> next) {
        // TODO: установите next_
    }
    
    // TODO: Установить предыдущий узел (через weak_ptr)
    void setPrev(std::weak_ptr<Node> prev) {
        // TODO: установите prev_
    }
    
    // TODO: Получить следующий узел
    std::shared_ptr<Node> getNext() const {
        // TODO: верните next_
        return nullptr;
    }
    
    // TODO: Получить предыдущий узел (из weak_ptr)
    std::shared_ptr<Node> getPrev() const {
        // TODO: преобразуйте weak_ptr в shared_ptr через lock()
        return nullptr;
    }
    
    int getValue() const { return value_; }
};

// Код для проверки
void testWeakPtr() {
    // Создание узлов
    auto node1 = std::make_shared<Node>(1);
    auto node2 = std::make_shared<Node>(2);
    auto node3 = std::make_shared<Node>(3);
    
    // Установка связей
    node1->setNext(node2);
    node2->setPrev(node1);
    node2->setNext(node3);
    node3->setPrev(node2);
    
    // Проверка связей
    assert(node1->getNext()->getValue() == 2);
    assert(node2->getPrev()->getValue() == 1);
    assert(node3->getPrev()->getValue() == 2);
    
    // Уничтожение node1 не должно привести к утечке
    node1.reset();
    
    // node2 все еще существует
    assert(node2->getNext()->getValue() == 3);
    
    // Попытка получить prev через weak_ptr должна вернуть nullptr
    auto prev = node2->getPrev();
    assert(prev == nullptr);  // node1 уже уничтожен
    
    std::cout << "Weak_ptr tests passed!\n";
}

int main() {
    testWeakPtr();
    return 0;
}

