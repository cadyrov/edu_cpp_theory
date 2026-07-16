template <typename F, typename G>
class Compose {
    // здесь определите поля структуры
public:
    template <typename F1, typename G1>
    Compose(F1 &&f, G1 &&g) {
        // здесь ваш код
    }

    // определите operator(), который принимает один шаблонный аргумент и вычисляет композицию функций
};

template <typename F, typename G>
Compose<F, G> compose(F &&f, G &&g) {
    // здесь ваш код
} 