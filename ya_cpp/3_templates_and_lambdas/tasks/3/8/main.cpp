#include <print>

template<typename T>
class Counter{
public:
   Counter(){++count_;}
   ~Counter(){--count_;}

   static int count() {
      return count_;
   }
private:
   static inline int count_ = 0;
};


int main() {
   Counter<int>a, b;
   Counter<double> c;

   std::println("int {}", a.count());
   {
      Counter<int> d;

      std::println("int {}", a.count());
   }
   std::println("int {}", a.count());
   std::println("dbl {}", c.count());

}