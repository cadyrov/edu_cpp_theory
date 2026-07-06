#include <iostream>
#include <memory>
#include <string>
#include <vector>

class GraphNode {
    public:
        explicit GraphNode(const std::string& name):name_(name){}

        void AddNeighbor(const std::shared_ptr<GraphNode>& nb) {
            neighbours_.push_back(nb);
        }

        void PrintNeighbors() const {
            std::cout << "Neighbors of " << name_ <<"\n";

            for (const auto& weakNb : neighbours_ ) {
                if (auto nb = weakNb.lock()) {
                    std::cout << "\t" << nb->name_;
                }
            }

        }
    private:
        std::string name_;
        std::vector<std::weak_ptr<GraphNode>> neighbours_;

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