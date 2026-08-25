Представьте, что вы разрабатываете систему анализа связей между различными объектами, каждый из которых представлен вершиной графа. 

У вершины есть список соседей, с которыми она соединена. Чтобы ваша система была безопасной в части использования памяти, а её объекты могли указывать друг на друга, примените std::shared_ptr и std::weak_ptr — это поможет избежать утечек памяти из-за возможных зависимостей.

Скопируйте код ниже к себе и выполните задания:

Создайте класс GraphNode, который хранит:
- имя вершины;
- список соседей.
- Реализуйте конструктор, принимающий имя вершины.
- Реализуйте метод AddNeighbor, который добавляет соседа.
- Реализуйте метод PrintNeighbors, который выводит имена всех доступных соседей.

```cpp
#include <iostream>
#include <memory>
#include <string>
#include <vector>

class GraphNode {
    // Ваш код здесь
};

int main() {
    auto nodeA = std::make_shared<GraphNode>("A");
    {
        auto nodeB = std::make_shared<GraphNode>("B");
        auto nodeC = std::make_shared<GraphNode>("C");

        //
        // Добавляем связи между узлами
        //
        // A ---> B
        // ^      |
        // |      |
        // C <----|
        //
        nodeA->AddNeighbor(nodeB);
        nodeB->AddNeighbor(nodeC);
        nodeC->AddNeighbor(nodeA);

        nodeA->PrintNeighbors();
    }

    std::println("\nPrint neighbors after deleting several nodes...");
    nodeA->PrintNeighbors();
}
```

- Используйте std::weak_ptr для хранения соседей, чтобы не возникало утечек в циклах.
- В PrintNeighbors обязательно проверяйте weak_ptr.lock() перед использованием.
- Добавьте нескольких соседей и убедитесь, что цикл работает корректно.