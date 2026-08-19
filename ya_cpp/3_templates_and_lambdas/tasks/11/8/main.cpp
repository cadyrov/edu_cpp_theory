// 8. Напишите универсальную логирующую обертку, которая сообщает о вызове и передает функцию
// с пакетом аргументов дальше через std::invoke и std::forward.
#include <functional>
#include <utility>

template <typename F, typename... Args> decltype(auto) call(F&& fn, Args&&... args) {
    return std::forward<F>(fn)(std::forward<Args>(args)...);
}
