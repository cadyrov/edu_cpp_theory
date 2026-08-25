Представьте, что ваша команда разработала прототип приложения с GUI, который пока проигрывает аналогам конкурентов. Вам доверили доработать и оптимизировать этот прототип. 

Вы тщательно проанализировали код и поняли, что приложение синхронизирует доступ к атомарным переменным внутри std::shared_ptr непозволительно долго. 

Попробуйте упростить структуру программы и не использовать концепцию совместного владения в классе Widget.

Скопируйте код ниже к себе и проведите его рефакторинг: замените std::shared_ptr на std::unique_ptr или сырые указатели.

```cpp
#include <memory>
#include <print>
#include <string>
#include <vector>

class Widget : public std::enable_shared_from_this<Widget> {
public:
    Widget(std::string_view name, std::shared_ptr<Widget> parent = nullptr) : name_(name), parent_(parent) {}

    // Метод для создания дочернего виджета
    std::shared_ptr<Widget> CreateChild(std::string_view childName) {
        auto child = std::make_shared<Widget>(childName, shared_from_this());
        children_.push_back(child);
        return child;
    }

    // Метод для отображения иерархии виджетов
    void PrintHierarchy(int level = 0) const {
        const std::string indent(level * 2, ' ');

        if (std::shared_ptr<Widget> parentSP = parent_.lock()) {
            std::println("{} - {} (Parent: {})", indent, name_, parentSP->name_);
        } else {
            std::println("{} - {}", indent, name_);
        }

        for (const auto &child : children_) {
            child->PrintHierarchy(level + 1);
        }
    }

private:
    std::string name_;
    std::weak_ptr<Widget> parent_;                   // Слабая ссылка на родителя
    std::vector<std::shared_ptr<Widget>> children_;  // Список дочерних виджетов
};

int main() {
    auto root = std::make_shared<Widget>("Root");  // Главное окно

    // Создание дочерних виджетов
    auto child1 = root->CreateChild("Child1");
    auto child2 = root->CreateChild("Child2");

    // Создание дочерних виджетов для Child1
    child1->CreateChild("Grandchild1");
    child1->CreateChild("Grandchild2");

    // Вывод иерархии виджетов
    root->PrintHierarchy();

    return 0;
}
```

- Вспомните, какие элементы бинарного дерева выражали уникальное владение и по отношению к кому.
- Определите, какие элементы иерархии виджетов должны выражать уникальное владение и по отношению к кому.
- Измените типы полей класса, чтобы не использовать концепцию совместного владения.
- Определите, какой тип должен иметь аргумент parent в конструкторе виджета.
- Определите, какой тип должна иметь переменная child в методе CreateChild.
- Удалите дополнительный класс, который применяется для создания std::shared_ptr внутри Widget.