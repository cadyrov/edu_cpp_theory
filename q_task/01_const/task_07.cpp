#include <string>
#include <vector>
#include <utility>

// Task 7: Константные параметры функций
// 
// Реализуйте набор функций для обработки данных, которые:
// 1. Правильно используют константные параметры
// 2. Обеспечивают максимальную производительность
// 3. Защищают от случайной модификации
// 4. Следуют best practices передачи параметров

struct UserData {
    std::string name;
    std::vector<int> scores;
    
    UserData(std::string n) : name(std::move(n)) {}
};

// TODO: Реализуйте следующие функции:

// 1. Функция для подсчета среднего балла
// - Не должна модифицировать данные
// - Должна быть эффективной
double calculateAverage(const UserData& user){
    int result =0;

    for (const auto x : user.scores) {
        result += x;
    }

    return static_cast<double>(result)/user.scores.size();
}

// 2. Функция для обновления имени
// - Должна модифицировать имя
// - Должна быть эффективной при передаче нового имени
void updateName(UserData& ud, std::string name) {
    ud.name = std::move(name);
}

// 3. Функция для добавления нового счета
// - Должна модифицировать список счетов
// - Не должна позволять модифицировать существующие счета
void addScore(UserData& ud, int score) {
    ud.scores.push_back(score);
}

// 4. Функция для проверки валидности данных
// - Не должна модифицировать данные
// - Должна быть максимально эффективной
bool isValid(const UserData& ud) {
    return ud.name.empty() == false && ud.scores.empty() == false;
}

// Код для проверки
void testConstParameters() {
    UserData user("Alice");
    user.scores = {80, 90, 85};
    const UserData const_user("Bob");
    
    // Эти строки должны компилироваться:
    double avg = calculateAverage(user);        // Для обычного объекта
    double const_avg = calculateAverage(const_user); // Для константного объекта
    updateName(user, "Alicia");                 // Обновление имени
    addScore(user, 95);                         // Добавление счета
    bool valid = isValid(user);                 // Проверка обычного объекта
    bool const_valid = isValid(const_user);     // Проверка константного объекта
    
    // Эти строки НЕ должны компилироваться:
    // updateName(const_user, "Bobby");    // Нельзя модифицировать константный объект
    // addScore(const_user, 100);          // Нельзя модифицировать константный объект
    // calculateAverage(user).modify();     // Нет модификации через результат
}
