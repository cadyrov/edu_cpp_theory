Представьте, что ваш стартап разрабатывает софт для планирования движения грузового транспорта. Ваши коллеги по проекту собирают и готовят датасет с крупными логистическими центрами и дорогами между ними. Ваша задача - разработать систему поиска наикратчайшего маршрута между двумя логистическими центрами.

Скопируйте код ниже к себе и разработайте функцию minWeightPath, которая использует std::stack для обхода графа с помощью алгоритма DFS:

Используйте minDist чтобы хранить наименьшее известное на данный момент расстояние от start до minDist[idx]. Пример: minDist[5] == 10 означает, что на текущий момент выполнения алгоритма наикратчайший путь от start до 5 равен 10.

Если по окончанию работы алгоритма minDist[end] == std::numeric_limits<unsigned int>::max(), значит, пути из start в end не существует.

```cpp
#include <limits>
#include <print>
#include <stack>

/*
 * AdjNode - класс, представляющий ребро графа
 *   - target: индекс узла, в который можно попасть перейдя по этой дороге
 *   - weight: "время", требуемое на проезд по дороге. В теории графов обычно называется "весом ребра"
 */
class AdjNode {
private:
    unsigned int target_;
    unsigned int weight_;

public:
    AdjNode(unsigned int target, unsigned int weight) : target_(target), weight_(weight) {}

    unsigned int getTarget() const { return target_; }
    unsigned int getWeight() const { return weight_; }
};

/*
 * Graph - класс, представляющий граф с весами у рёбер
 *   - adjList_[idx]: ребро представляющее маршрут из узла `idx` в узел `adjList_[idx].getTarget`
 */
class Graph {
private:
    std::vector<std::vector<AdjNode>> adjList_;

public:
    Graph(unsigned int numNodes) : adjList_(numNodes + 1) {}  // nodes indexed from 1

    void addEdge(unsigned int from, unsigned int to, unsigned int weight) {
        if (from >= adjList_.size() || from == 0) {
            throw std::out_of_range{"'from' index is out of range"};
        }
        if (to >= adjList_.size() || to == 0) {
            throw std::out_of_range{"'to' index is out of range"};
        }

        adjList_[from].emplace_back(to, weight);
    }

    int minWeightPath(unsigned int start, unsigned int end) const {
        std::vector<unsigned int> minDist(adjList_.size(), std::numeric_limits<unsigned int>::max());
        std::stack<std::pair<int, int>> stack;  // ( idx, accumulatedWeight )

        return -1;
    }

    void printGraph() const {
        for (size_t i = 1; i < adjList_.size(); ++i) {

            std::print("{} -> ", i);
            for (const auto &n : adjList_[i]) {
                std::print("({}, w={}) ", n.getTarget(), n.getWeight());
            }
            std::println();
        }
    }
};

int main() {
    Graph g(6);

    g.addEdge(1, 2, 4);
    g.addEdge(1, 3, 1);
    g.addEdge(3, 2, 2);
    g.addEdge(2, 4, 1);
    g.addEdge(3, 4, 5);
    g.addEdge(4, 5, 3);
    g.addEdge(1, 6, 10);
    g.addEdge(6, 5, 2);

    g.printGraph();

    {
        unsigned int from = 1, to = 5;
        int result = g.minWeightPath(from, to);

        if (result != -1)
            std::print("Fastest path from '{}' to '{}' is: {}\n", from, to, result);
        else
            std::print("No path found.\n");
    }

    {
        unsigned int from = 2, to = 6;
        int result = g.minWeightPath(from, to);

        if (result != -1)
            std::print("Fastest path from '{}' to '{}' is: {}\n", from, to, result);
        else
            std::print("There is no path from '{}' to '{}'.\n", from, to);
    }

    return 0;
} 
```

- Начните инициализацию алгоритма с того, что расстояние от start до start равно 0:

```cpp
  stack.push({start, 0});
  minDist[start] = 0;
```
   
- Функция должна работать до тех пор, пока stack не пуст.
- На каждом шаге проверяйте, что расстояние от stack.top() + newWeight меньше, чем уже записанное в minDist, и если это так - обновляйте результат в minDist.