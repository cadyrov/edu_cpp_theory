#include <iostream>
#include <vector>
#include <optional>
#include <sstream>

struct Position {
    int value;
    int max;
    Position() = default;
    Position(int val) : value(val), max(val) {}
};

class StackMax {
public:
    StackMax(size_t size){
        data_.resize(size);
    }

    std::optional<int> GetMax() {
        auto res = Top();
        if (res == std::nullopt) {
            return std::nullopt;
        }

        return res.value().max;
    }

    void Push(int num) {
       Position ps(num);

        if (idx_ > 0 && ps.max < data_[idx_-1].max) {
            ps.max =  data_[idx_-1].max;
        }

        data_[idx_++] = ps;
    }

    std::optional<Position> Pop () {
        if (idx_ == 0) {
            return std::nullopt;
        }

        return data_[idx_--];
    }

    std::optional<Position> Top() {
        if (idx_ == 0) {
            return std::nullopt;
        }

        return data_[idx_-1];
    }   

private:   
   std::vector<Position> data_;
   size_t idx_ = 0;
};




int main() {
    int cnt = 0;
    int num = 0;
    std::string line;
    std::string command;

    
    getline(std::cin, line);
    std::istringstream iss(line);

    iss >> cnt;

    StackMax stack(cnt);

    for (int i = 0; i < cnt;++i) {
        getline(std::cin, line);
        std::istringstream iss(line);

        iss>>command;
        
        if (command == "push") {
            iss >> num;
            stack.Push(num);
        } else if (command == "top") {
            auto res = stack.Top();
            if (res == std::nullopt) {
                std::cout << "error\n";
            } else {
                std::cout << res.value().value << '\n';
            }    
        } else if (command == "pop") {
            auto res = stack.Pop();
            if (res == std::nullopt) {
                std::cout << "error\n";
            }
        } else if (command == "get_max") {
            auto res = stack.GetMax();
            if (res == std::nullopt) {
                std::cout << "None\n";
            } else {
                std::cout << *res << '\n';
            }
        }
    }   

    return 0;
}
