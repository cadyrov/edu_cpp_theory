#include <vector>
#include <string>
#include <algorithm>
#include <compare>

struct Book {
    std::string name;
    int idx = 0;
    auto operator<=>(const Book &rhd) const{ return idx <=> rhd.idx; }
};

void Process(std::vector<Book>& books) {
    if (books.empty())
        return;

    auto middle = std::next(books.begin(), books.size() / 2);
    std::nth_element(books.begin(), middle, books.end());

    books.erase(books.begin(), middle);
} 


int main() {
    return 0;
}