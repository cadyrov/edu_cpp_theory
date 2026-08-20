//   Напишите обработку списка заказов через `sort`, `find_if` и `count_if` с разными лямбдами.

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

struct Order {
    int id;
    std::string name;
    double price;

    friend std::ostream& operator<<(std::ostream& os, const Order& od) {
        os << "{id: " << od.id << "name: " << od.name << "price: " << od.price << "}";

        return os;
    }
};

int main() {
    std::vector<Order> data{
        {1, "dd", 33.3},
        {3, "ddcds", 35.3},
        {2, "ddc", 366.3},
        {4, "ddcd", 37.3},
    };

    auto it = std::find_if(data.begin(), data.end(), [](const Order& a) { return a.id == 3; });
    if (it != data.end()) {
        std::cout << "3 order: " << *it << "\n";
    }

    std::cout << "count over 35 : " << std::count_if(data.begin(), data.end(), [](const Order& a) {
        return a.price > 35.;
    }) << "\n";

    std::sort(data.begin(), data.end(), [](const Order& a, const Order& b) { return a.id < b.id; });

    for (const auto& o : data) {
        std::cout << o << "\n";
    }

    return 0;
}