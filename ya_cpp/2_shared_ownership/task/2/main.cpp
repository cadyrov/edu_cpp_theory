#include <memory>
#include <print>
#include <string>
#include <vector>

class Widget {
public:
    Widget(std::string_view name, Widget* parent = nullptr) : name_(name), parent_(parent) {}

    // Метод для создания дочернего виджета
    Widget* CreateChild(std::string_view childName) {
        auto child = std::make_unique<Widget>(childName);
        children_.push_back(std::move(child));
        
        return children_.back().get();  // Возвращаем указатель на созданный дочерний виджет
    }

    // Метод для отображения иерархии виджетов
    void PrintHierarchy(int level = 0) const {
        const std::string indent(level * 2, ' ');

        if (parent_) {
            std::println("{} - {} (Parent: {})", indent, name_, parent_->name_);
        } else {
            std::println("{} - {}", indent, name_);
        }

        for (const auto &child : children_) {
            child->PrintHierarchy(level + 1);
        }
    }

private:
    std::string name_;
    Widget* parent_;                   
    std::vector<std::unique_ptr<Widget>> children_;
};

int main() {
    auto root = std::make_unique<Widget>("Root");  // Главное окно

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