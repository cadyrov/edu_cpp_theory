#include <iostream>
#include <cassert>
#include <memory>
#include <map>
#include <string>

// Task 9: Кэш с shared_ptr
//
// Реализуйте класс ResourceCache, который:
// 1. Кэширует ресурсы через shared_ptr
// 2. Разделяет ресурсы между несколькими пользователями
// 3. Автоматически освобождает неиспользуемые ресурсы

class ExpensiveResource {
    std::string name_;
    int* data_;
    
public:
    ExpensiveResource(const std::string& name) : name_(name) {
        data_ = new int[1000];  // Дорогое выделение памяти
        std::cout << "ExpensiveResource " << name_ << " created\n";
    }
    
    ~ExpensiveResource() {
        delete[] data_;
        std::cout << "ExpensiveResource " << name_ << " destroyed\n";
    }
    
    const std::string& getName() const { return name_; }
    
    // Запретить копирование
    ExpensiveResource(const ExpensiveResource&) = delete;
    ExpensiveResource& operator=(const ExpensiveResource&) = delete;
};

class ResourceCache {
    std::map<std::string, std::weak_ptr<ExpensiveResource>> cache_;
    
public:
    // TODO: Получить ресурс из кэша или создать новый
    std::shared_ptr<ExpensiveResource> getResource(const std::string& name) {
        // TODO: проверьте есть ли ресурс в кэше (через weak_ptr.lock())
        // TODO: если ресурс существует, верните shared_ptr
        // TODO: если ресурса нет, создайте новый и добавьте в кэш
        return nullptr;
    }
    
    // TODO: Очистить кэш от неиспользуемых ресурсов
    void cleanup() {
        // TODO: удалите из кэша все expired weak_ptr
    }
    
    // TODO: Получить количество ресурсов в кэше
    size_t getCacheSize() const {
        // TODO: верните размер кэша
        return 0;
    }
};

// Код для проверки
void testResourceCache() {
    ResourceCache cache;
    
    // Получение ресурса (создание нового)
    auto res1 = cache.getResource("resource1");
    assert(res1 != nullptr);
    assert(res1->getName() == "resource1");
    assert(cache.getCacheSize() == 1);
    
    // Получение того же ресурса (из кэша)
    auto res2 = cache.getResource("resource1");
    assert(res2 != nullptr);
    assert(res2->getName() == "resource1");
    assert(res1 == res2);  // Должен быть тот же объект
    assert(res1.use_count() == 2);  // Два shared_ptr указывают на один объект
    
    // Освобождение одного shared_ptr
    res1.reset();
    assert(res2.use_count() == 1);
    
    // Ресурс все еще в кэше
    auto res3 = cache.getResource("resource1");
    assert(res3 == res2);
    
    // Освобождение всех shared_ptr
    res2.reset();
    res3.reset();
    
    // Очистка кэша
    cache.cleanup();
    assert(cache.getCacheSize() == 0);
    
    std::cout << "ResourceCache tests passed!\n";
}

int main() {
    testResourceCache();
    return 0;
}

