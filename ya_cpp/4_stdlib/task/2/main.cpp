#include <string>
#include <unordered_map>
#include <print>

int main() {
    std::unordered_map<int, std::string> players{
        {1, "John"},
        {2, "Michael"},
        {3, "Todd"},
        {4, "Chris"}
    };
   
    for (const auto& [id, name] : players) {
        std::println("id={}, name={}", id, name);
    } 

    return 0;
}