#include <iostream>
#include <vector>
#include <optional>
#include <sstream>
#include <cassert>

class Stack {
public:
    Stack() = delete; 
    Stack(const Stack&) = delete;
    Stack(Stack&&) = delete;

    Stack(size_t size){
        data_.resize(size);
    }

    bool IsEmpty() const{
        return num_ == 0;
    }

    void Push(char in) {
        data_[num_++] = in;
    }

    std::optional<char> Pop() {
        if (num_ == 0) {
            return std::nullopt;
        }

        return data_[--num_];
    }

    std::optional<char> Top() const {
        if (num_ == 0) {
            return std::nullopt;
        }

        return data_[num_ - 1];
    }

private:
    size_t num_ = 0;
    std::vector<char> data_;
};

bool checkBracers(const std::string &in) {
    if (in.size() == 0) {
        return true;
    }

    Stack st(in.size());

    for (int i = 0; i < in.size(); ++i) {
        if (in[i] == '(' || in[i] == '{' || in[i] == '[') {
            st.Push(in[i]);
        } else if (in[i] == ')' || in[i] == ']' || in[i] == '}') {
            if (st.IsEmpty()) {
                return false;
            }

            if ((in[i] == ')'  && st.Top().value() == '(') ||
                (in[i] == ']'  && st.Top().value() == '[') ||
                (in[i] == '}'  && st.Top().value() == '{') ) {
                st.Pop();
            }  else {
                return false;
            }
        } else {
            return false;
        }
    }

    return st.IsEmpty();
}



int main() {
    assert(checkBracers("()"));
    assert(checkBracers("[]"));
    assert(checkBracers("{{{}}}"));
    assert(checkBracers("(({{[[]]}}))"));
    assert(!checkBracers("((({[[]]}}))"));

    std::string brac;

    getline(std::cin, brac);

    if (checkBracers(brac)) {
        std::cout << "True";
    } else {
        std::cout << "False";
    }

    return 0;
}
