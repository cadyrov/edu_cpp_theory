#include <string>
#include <map>
#include <memory>

// Task 1: Константные умные указатели
// 
// Реализуйте класс Registry, который:
// 1. Хранит shared_ptr на объекты с их именами
// 2. Позволяет получать константные shared_ptr на объекты
// 3. Предотвращает модификацию объектов через полученные указатели
// 4. Разрешает модификацию только через специальные методы

class Object {
    int value_;
public:
    Object(int v) : value_(v) {}
    void setValue(int v) { value_ = v; }
    int getValue() const { return value_; }
};

class Registry {
    std::map<std::string, std::shared_ptr<Object>> objects_;

public:
    // TODO: Реализуйте:
    // 1. Метод регистрации объекта (register/add)
    // 2. Метод получения константного указателя на объект
    // 3. Метод модификации объекта по имени
    // 4. Метод проверки существования объекта
};

// Код для проверки
void testRegistry() {
    Registry registry;
    
    // Регистрация объектов
    registry.add("obj1", std::make_shared<Object>(42));
    registry.add("obj2", std::make_shared<Object>(123));
    
    // Получение и использование объектов
    auto obj1 = registry.get("obj1");
    std::cout << "obj1 value: " << obj1->getValue() << "\n";
    
    // Модификация через специальный метод
    registry.modify("obj1", 100);
    std::cout << "obj1 new value: " << obj1->getValue() << "\n";
    
    // Эти строки НЕ должны компилироваться:
    // obj1->setValue(200);              // Нельзя модифицировать через полученный указатель
    // registry.get("obj1")->setValue(200); // Нельзя модифицировать через результат get()
}
