#include <string>
#include <utility>
#include <vector>

class Bag {
    std::vector<std::string> data_;

public:
    void add(std::string&& s) {
        data_.push_back(std::move(s));
    }

    template <typename T>
    void add_any(T&& s) {
        data_.push_back(std::forward<T>(s));
    }

    std::string take_last() {
        std::string result = data_.back();
        data_.pop_back();
        return result;
    }
};