//6. Напишите класс `CallbackHolder<Callback>`, который вызывает функцию `Callback`.

template<void (*Callback)()>
class CallbackHolder{
    public:
        void call() {
            Callback();
        }
};

int main() {
    auto fun = [](){};

    CallbackHolder<fun> a;

    a.call();

    return 0;
}

