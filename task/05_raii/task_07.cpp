#include <iostream>
#include <cassert>
#include <memory>
#include <vector>

// Task 7: Порядок уничтожения
//
// Реализуйте класс ResourceManager, который:
// 1. Управляет несколькими ресурсами
// 2. Демонстрирует порядок уничтожения (обратный порядку объявления)
// 3. Правильно освобождает все ресурсы

class Resource {
    int id_;
    static int next_id_;
    
public:
    Resource() : id_(next_id_++) {
        std::cout << "Resource " << id_ << " created\n";
    }
    
    ~Resource() {
        std::cout << "Resource " << id_ << " destroyed\n";
    }
    
    int getId() const { return id_; }
};

int Resource::next_id_ = 1;

class ResourceManager {
    // TODO: Объявите ресурсы в определенном порядке
    // Порядок уничтожения будет обратным порядку объявления
    std::unique_ptr<Resource> resource1_;
    std::unique_ptr<Resource> resource2_;
    std::unique_ptr<Resource> resource3_;
    
public:
    // TODO: Конструктор
    ResourceManager() {
        // TODO: создайте ресурсы в порядке 1, 2, 3
    }
    
    // TODO: Деструктор не нужен (используется правило нуля)
    // Ресурсы уничтожатся автоматически в обратном порядке
    
    // Методы доступа
    Resource* getResource1() { return resource1_.get(); }
    Resource* getResource2() { return resource2_.get(); }
    Resource* getResource3() { return resource3_.get(); }
};

// Код для проверки
void testDestructionOrder() {
    std::cout << "Creating ResourceManager...\n";
    {
        ResourceManager manager;
        
        assert(manager.getResource1() != nullptr);
        assert(manager.getResource2() != nullptr);
        assert(manager.getResource3() != nullptr);
        
        std::cout << "ResourceManager created\n";
        // При выходе из блока ресурсы уничтожатся в обратном порядке
    }
    std::cout << "ResourceManager destroyed\n";
    
    // Ожидаемый порядок уничтожения: 3, 2, 1
    std::cout << "Destruction order tests passed!\n";
}

int main() {
    testDestructionOrder();
    return 0;
}

