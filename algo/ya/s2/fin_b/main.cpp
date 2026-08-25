#include <iostream>
#include <string>
#include <vector>
#include <optional>
#include <sstream>

template<typename T>
class Stack {
public:
    Stack() = default;
    Stack(Stack&&)=delete;
    Stack(const Stack&)=delete;
    Stack& operator +(const Stack&) = delete;
    Stack&& operator +(Stack&&) = delete;
    ~Stack(){};

    void Push(T in) {
        if (data_.size() == l_) {
            data_.push_back(in);
        } else {
            data_[l_] = in;
        }

        ++l_;
    }

    std::optional<T> Pop() {
        if (l_ == 0) {
            return std::nullopt;
        }

        T v = data_[l_-1];
        --l_;

        return v;
    }

private:
    size_t l_ = 0;
    std::vector<T> data_{};
};


int count(std::string in) {
        Stack<int> st{};
        
        std::istringstream iss(in);
        std::string word;

        for (;iss >> word;) {
            if (word == "+") {
                 int sec = st.Pop().value();
                 int first = st.Pop().value();
                st.Push(first + sec);
                continue;
            } else if (word == "-") {
                 int sec = st.Pop().value();
                 int first = st.Pop().value();
                st.Push(first - sec);
                continue;
            }else if (word == "*") {
                 int sec = st.Pop().value();
                 int first = st.Pop().value();
                st.Push(first * sec);
                continue;
            }else if (word == "/") {
                int sec = st.Pop().value();
                int first = st.Pop().value();

                if (first * sec < 0 && first % sec != 0) {
                    st.Push(first / sec - 1);
                } else {
                    st.Push(first / sec);
                }

                continue;
            }

            st.Push(std::stoi(word));
        }

    return st.Pop().value();
}

int main() {
    std::string in;

    std::getline(std::cin, in);

    
    
    std::cout << count(in) << std::endl;
    

    return 0;
}