#include <utility>

template <typename F, typename G>
class Compose {
    F f_;
    G g_;
public:
    template <typename F1, typename G1>
    Compose(F1 &&f, G1 &&g):f_(std::forward<F1>(f)),g_(std::forward<G1>(g)) {}

    template<typename O>
    decltype(auto) operator() (O&& in){
        return f_(g_(std::forward<O>(in)));
    }
};

template <typename F, typename G>
Compose<F, G> compose(F &&f, G &&g) {
    return Compose<F, G>(std::forward<F>(f),std::forward<G>(g));
} 