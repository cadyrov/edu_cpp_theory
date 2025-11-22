#include <iostream>
#include <cassert>
#include <memory>
#include <vector>
#include <algorithm>

// Task 10: Продвинутое использование умных указателей
//
// Реализуйте класс AdvancedManager, который:
// 1. Комбинирует unique_ptr и shared_ptr
// 2. Использует weak_ptr для наблюдения
// 3. Правильно управляет жизненным циклом ресурсов
// 4. Поддерживает полиморфизм

class BaseResource {
public:
    virtual ~BaseResource() = default;
    virtual int getValue() const = 0;
    virtual void setValue(int v) = 0;
};

class ConcreteResource : public BaseResource {
    int value_;
public:
    ConcreteResource(int v) : value_(v) {}
    int getValue() const override { return value_; }
    void setValue(int v) override { value_ = v; }
};

class AdvancedManager {
    std::vector<std::unique_ptr<BaseResource>> owned_resources_;
    std::vector<std::shared_ptr<BaseResource>> shared_resources_;
    std::vector<std::weak_ptr<BaseResource>> observed_resources_;
    
public:
    // TODO: Добавить уникальный ресурс
    void addOwnedResource(std::unique_ptr<BaseResource> resource) {
        // TODO: добавьте unique_ptr в owned_resources_
    }
    
    // TODO: Добавить разделяемый ресурс
    void addSharedResource(std::shared_ptr<BaseResource> resource) {
        // TODO: добавьте shared_ptr в shared_resources_
        // TODO: добавьте weak_ptr в observed_resources_
    }
    
    // TODO: Создать и добавить разделяемый ресурс
    std::shared_ptr<BaseResource> createSharedResource(int value) {
        // TODO: создайте shared_ptr через make_shared
        // TODO: добавьте в shared_resources_ и observed_resources_
        return nullptr;
    }
    
    // TODO: Получить количество активных наблюдаемых ресурсов
    size_t getActiveObservedCount() const {
        // TODO: подсчитайте количество не expired weak_ptr
        return 0;
    }
    
    // TODO: Очистить неактивные наблюдаемые ресурсы
    void cleanupObserved() {
        // TODO: удалите все expired weak_ptr из observed_resources_
    }
    
    // TODO: Получить количество владеемых ресурсов
    size_t getOwnedCount() const {
        // TODO: реализуйте
        return 0;
    }
    
    // TODO: Получить количество разделяемых ресурсов
    size_t getSharedCount() const {
        // TODO: реализуйте
        return 0;
    }
};

// Код для проверки
void testAdvancedManager() {
    AdvancedManager manager;
    
    // Добавление уникальных ресурсов
    manager.addOwnedResource(std::make_unique<ConcreteResource>(10));
    manager.addOwnedResource(std::make_unique<ConcreteResource>(20));
    assert(manager.getOwnedCount() == 2);
    
    // Создание разделяемых ресурсов
    auto shared1 = manager.createSharedResource(100);
    auto shared2 = manager.createSharedResource(200);
    assert(manager.getSharedCount() == 2);
    assert(manager.getActiveObservedCount() == 2);
    
    // Добавление внешнего разделяемого ресурса
    auto external = std::make_shared<ConcreteResource>(300);
    manager.addSharedResource(external);
    assert(manager.getSharedCount() == 3);
    assert(manager.getActiveObservedCount() == 3);
    
    // Освобождение внешнего ресурса
    external.reset();
    assert(manager.getActiveObservedCount() == 2);
    
    // Очистка неактивных
    manager.cleanupObserved();
    assert(manager.getActiveObservedCount() == 2);
    
    std::cout << "AdvancedManager tests passed!\n";
}

int main() {
    testAdvancedManager();
    return 0;
}

