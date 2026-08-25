#include <iostream>
#include <list>
#include <vector>
#include <print>
#include <iterator>
#include <algorithm>

class Object {
public:
  explicit Object(size_t count)
    : v(count, 0)
  { }
  size_t getCount() const {
    return v.size();
  }
private:
  std::vector<int> v;
};


template <std::forward_iterator Iterator>
void rotate_prefix(Iterator begin, size_t n) {
  auto end = std::next(begin, n + 1);
  auto distance = std::distance(begin, end);
  auto half = std::next(begin, distance / 2);
   
  std::rotate(begin, half, end);
} 


template <std::random_access_iterator Iterator>
Iterator pivot
  (Iterator begin,
  Iterator end)
{
  auto d = std::distance(begin, end);
  return begin + rand(0, d);
} 

int main() {
    std::list<Object> l = {Object{100}, Object{1024}, Object{1024 * 1024}}; 

    for (auto& ob :l) {
        std::println("{}", ob.getCount());
    }

    return 0;
}

