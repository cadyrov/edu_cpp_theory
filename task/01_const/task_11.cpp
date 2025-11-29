#include <string>
#include <vector>
#include <iostream>
#include <algorithm>

// Task 11: Константные параметры функций
//
// Реализуй набор функций для обработки данных с правильным использованием
// константных параметров. Пойми, когда использовать const ссылки, const указатели,
// и когда const избыточен (передача по значению).
//
// Требования:
// 1. Функции для чтения данных должны принимать const ссылки
// 2. Функции для модификации должны принимать non-const ссылки
// 3. Функции, работающие с примитивами, могут принимать по значению
// 4. Функции, принимающие указатели, должны использовать const где возможно
// 5. Понимание разницы между передачей по значению, ссылке и указателю

struct UserProfile {
    std::string name;
    int age;
    std::vector<std::string> hobbies;
    
    UserProfile(std::string n, int a) : name(std::move(n)), age(a) {}
};

// TODO: Реализуй функцию для подсчёта среднего возраста
// Должна принимать const ссылку (не модифицирует данные)
double calculateAverageAge(const std::vector<UserProfile>& users) {
    // TODO: реализуй
    return 0.0;
}

// TODO: Реализуй функцию для поиска пользователя по имени
// Должна принимать const ссылку (не модифицирует данные)
// Должна возвращать const указатель или const итератор
const UserProfile* findUserByName(const std::vector<UserProfile>& users, const std::string& name) {
    // TODO: реализуй
    return nullptr;
}

// TODO: Реализуй функцию для обновления возраста пользователя
// Должна принимать non-const ссылку (модифицирует данные)
void updateUserAge(UserProfile& user, int new_age) {
    // TODO: реализуй
}

// TODO: Реализуй функцию для добавления хобби
// Должна принимать non-const ссылку (модифицирует данные)
void addHobby(UserProfile& user, const std::string& hobby) {
    // TODO: реализуй
}

// TODO: Реализуй функцию для проверки валидности данных
// Должна принимать const ссылку (не модифицирует данные)
bool isValidProfile(const UserProfile& user) {
    // TODO: реализуй - проверь, что имя не пустое и возраст > 0
    return false;
}

// TODO: Реализуй функцию для подсчёта количества хобби
// Должна принимать const ссылку
// Вопрос: можно ли принимать по значению? Почему нет?
size_t countHobbies(const UserProfile& user) {
    // TODO: реализуй
    return 0;
}

// TODO: Реализуй функцию для печати информации о пользователе
// Должна принимать const ссылку
void printUser(const UserProfile& user) {
    // TODO: реализуй
}

// TODO: Реализуй функцию для сортировки пользователей по возрасту
// Должна принимать non-const ссылку (модифицирует контейнер)
void sortUsersByAge(std::vector<UserProfile>& users) {
    // TODO: реализуй
}

void testConstParameters() {
    std::vector<UserProfile> users;
    users.emplace_back("Alice", 25);
    users.emplace_back("Bob", 30);
    users.emplace_back("Charlie", 20);
    
    users[0].hobbies = {"reading", "coding"};
    users[1].hobbies = {"gaming"};
    
    // Эти строки должны компилироваться:
    double avg_age = calculateAverageAge(users);        // Const ссылка
    const UserProfile* found = findUserByName(users, "Alice");  // Const ссылка
    printUser(users[0]);                                 // Const ссылка
    bool valid = isValidProfile(users[0]);               // Const ссылка
    size_t hobbies_count = countHobbies(users[0]);       // Const ссылка
    
    updateUserAge(users[0], 26);                        // Non-const ссылка
    addHobby(users[1], "swimming");                      // Non-const ссылка
    sortUsersByAge(users);                               // Non-const ссылка
    
    // Эти строки НЕ должны компилироваться:
    // const std::vector<UserProfile> const_users = users;
    // updateUserAge(const_users[0], 27);                 // Error: cannot modify through const
    // addHobby(const_users[0], "dancing");              // Error: cannot modify through const
    // sortUsersByAge(const_users);                      // Error: cannot modify const container
}

int main() {
    testConstParameters();
    return 0;
}

