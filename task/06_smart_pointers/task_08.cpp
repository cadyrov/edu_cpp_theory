#include <iostream>
#include <cassert>
#include <memory>
#include <vector>

// Task 8: Контейнеры с умными указателями
//
// Реализуйте класс ResourceManager, который:
// 1. Хранит коллекцию ресурсов через unique_ptr
// 2. Управляет жизненным циклом ресурсов
// 3. Поддерживает добавление и удаление ресурсов

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
    std::vector<std::unique_ptr<Resource>> resources_;
    
public:
    // TODO: Добавить ресурс
    void addResource(std::unique_ptr<Resource> resource) {
        // TODO: добавьте unique_ptr в вектор
    }
    
    // TODO: Создать и добавить ресурс
    void createResource() {
        // TODO: создайте ресурс через make_unique и добавьте
    }
    
    // TODO: Удалить ресурс по индексу
    void removeResource(size_t index) {
        // TODO: удалите ресурс из вектора
    }
    
    // TODO: Получить количество ресурсов
    size_t getResourceCount() const {
        // TODO: реализуйте
        return 0;
    }
    
    // TODO: Получить ресурс по индексу (без передачи владения)
    Resource* getResource(size_t index) {
        // TODO: верните указатель на ресурс без передачи владения
        return nullptr;
    }
    
    // TODO: Очистить все ресурсы
    void clear() {
        // TODO: очистите вектор (ресурсы автоматически освободятся)
    }
};

// Код для проверки
void testResourceManager() {
    ResourceManager manager;
    
    // Создание ресурсов
    manager.createResource();
    manager.createResource();
    manager.createResource();
    
    assert(manager.getResourceCount() == 3);
    
    // Доступ к ресурсам
    auto* res1 = manager.getResource(0);
    assert(res1 != nullptr);
    assert(res1->getId() == 1);
    
    // Удаление ресурса
    manager.removeResource(1);
    assert(manager.getResourceCount() == 2);
    
    // Добавление внешнего ресурса
    auto external = std::make_unique<Resource>();
    manager.addResource(std::move(external));
    assert(manager.getResourceCount() == 3);
    
    // Очистка
    manager.clear();
    assert(manager.getResourceCount() == 0);
    
    std::cout << "ResourceManager tests passed!\n";
}

int main() {
    testResourceManager();
    return 0;
}

