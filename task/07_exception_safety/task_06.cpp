#include <iostream>
#include <cassert>
#include <vector>
#include <stdexcept>

// Task 6: Транзакционное поведение
//
// Реализуйте функцию transaction, которая:
// 1. Выполняет операцию с возможностью отката
// 2. Сохраняет состояние до выполнения
// 3. Откатывает изменения при исключении

class TransactionalState {
    std::vector<int> data_;
    
public:
    void addValue(int value) {
        data_.push_back(value);
    }
    
    void setData(const std::vector<int>& data) {
        data_ = data;
    }
    
    const std::vector<int>& getData() const {
        return data_;
    }
    
    size_t size() const {
        return data_.size();
    }
};

// TODO: Функция транзакции с откатом
template<typename Func>
void transaction(TransactionalState& state, Func&& func) {
    // TODO: сохраните текущее состояние (backup)
    // TODO: выполните функцию func
    // TODO: если произошло исключение, восстановите состояние из backup
    // TODO: перебросьте исключение после отката
}

// Код для проверки
void testTransactionalBehavior() {
    TransactionalState state;
    state.addValue(1);
    state.addValue(2);
    state.addValue(3);
    
    std::vector<int> original_data = state.getData();
    
    // Успешная транзакция
    transaction(state, [&state]() {
        state.addValue(4);
        state.addValue(5);
    });
    assert(state.size() == 5);
    
    // Транзакция с исключением - состояние должно откатиться
    try {
        transaction(state, [&state]() {
            state.addValue(6);
            throw std::runtime_error("Transaction failed");
        });
        assert(false);  // Не должно дойти сюда
    } catch (const std::runtime_error& e) {
        // Состояние должно быть откачено
        assert(state.size() == 5);  // Вернулось к состоянию до транзакции
    }
    
    // Еще одна проверка отката
    std::vector<int> before_transaction = state.getData();
    try {
        transaction(state, [&state]() {
            state.addValue(100);
            state.addValue(200);
            throw std::logic_error("Error");
        });
    } catch (...) {
        // Состояние должно быть идентично состоянию до транзакции
        assert(state.getData() == before_transaction);
    }
    
    std::cout << "Transactional behavior tests passed!\n";
}

int main() {
    testTransactionalBehavior();
    return 0;
}

