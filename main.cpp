#include <iostream>                                                                                                 // 1
#include <memory>                                                                                                   // 2
#include <print>                                                                                                    // 3
#include <sstream>                                                                                                  // 4
#include <string>                                                                                                   // 5
                                                                                                                    // 6
// FactoryPolicy                                                                                                    // 7
template <typename Derived>                                                                                         // 8
struct FactoryPolicy {                                                                                              // 9
    template <typename... Args>                                                                                     // 10
    static std::unique_ptr<Derived> create(Args &&args) {                                                           // 11
        std::println("Create object");                                                                              // 12
        return std::make_unique<Derived>(std::move<Args>(args)...);                                                 // 13
    }                                                                                                               // 14
                                                                                                                    // 15
    static void destroy(std::unique_ptr<Derived> &&ptr) { std::println("Delete object"); }                          // 16
};                                                                                                                  // 17
                                                                                                                    // 18
// LoggingPolicy                                                                                                    // 19
template <class Derived>                                                                                            // 20
struct LoggingPolicy {                                                                                              // 21
    void log(std::string message) const { std::println("Log: {}", message); }                                       // 22
};                                                                                                                  // 23
                                                                                                                    // 24
// Widget class                                                                                                     // 25
template <typename T, typename... Policies>                                                                         // 26
class Widget : public Policies<Widget<T, Policies...>> {                                                            // 27
    T value_;                                                                                                       // 28
                                                                                                                    // 29
public:                                                                                                             // 30
    explicit Widget(T value) : value_(value) {}                                                                     // 31
                                                                                                                    // 32
    T get() const { return value_; }                                                                                // 33
};                                                                                                                  // 34
                                                                                                                    // 35
// Usage examples                                                                                                   // 36
int main() {                                                                                                        // 37
    using WidgetWithLogging = Widget<int, LoggingPolicy>;                                                           // 38
    using WidgetWithFactoryAndLogging = Widget<int, FactoryPolicy, LoggingPolicy>;                                  // 39
                                                                                                                    // 40
    // Example with Logging                                                                                         // 41
    WidgetWithLogging widget1(100);                                                                                 // 42
    widget1.log("Widget1 created with value 100");                                                                  // 43
                                                                                                                    // 44
    // Example with Factory and Stringify                                                                           // 45
    auto widget2 = WidgetWithFactoryAndLogging::create(42);                                                         // 46
    std::println("Widget2 value: {}", widget2->get());                                                              // 47
    WidgetWithFactoryAndLogging::destroy(std::move(widget2));                                                       // 48
    if (!widget2) {                                                                                                 // 49
        std::println("Hooray!");                                                                                    // 50
    }                                                                                                               // 51
    return 0;                                                                                                       // 52
}                                                                                                                   // 53