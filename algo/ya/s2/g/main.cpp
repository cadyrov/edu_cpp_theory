#include <iostream>
#include <vector>
#include <optional>
#include <sstream>

class StackMax {
public:
    StackMax(size_t size){
        data_.resize(size);
    }

    std::optional<int> GetMax() {
        return max_;
    }

    void Push(int num) {
        data_[idx_++] = num;

        if (max_ == std::nullopt || max_ < num) {
            max_ = num;
        }
    }

    std::optional<int> Pop () {
        if (idx_ == 0) {
            return std::nullopt;
        }

        if (data_[idx_-1] == max_.value()) {
            setMax(idx_-1);
        }

        return data_[idx_--];
    }

    std::optional<int> Top() {
        if (idx_ == 0) {
            return std::nullopt;
        }

        return data_[idx_-1];
    }   

private:   
    void setMax(size_t to_idx) {
        if (to_idx == 0) {
            max_ = std::nullopt;
            return;
        }
        max_ = data_[0];
        for (int i = 0; i < to_idx; ++i) {
            if (data_[i] > max_) {
                max_ = data_[i];
            }
        }
    }

   std::vector<int> data_;
   size_t idx_ = 0;
   std::optional<int> max_;
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
                std::cout << *res << '\n';
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
