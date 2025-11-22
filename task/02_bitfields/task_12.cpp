#include <cstdint>
#include <cassert>
#include <iostream>

// Task 12: Работа с флагами разрешений
//
// Реализуйте класс Permissions для работы с правами доступа.
// Нужно хранить и управлять правами: read(R), write(W), execute(X)
//
// Методы:
// - grant(Permission) - выдать право
// - revoke(Permission) - забрать право
// - check(Permission) - проверить наличие права
// - checkAll(Permissions) - проверить наличие всех прав
// - checkAny(Permissions) - проверить наличие хотя бы одного права

enum Permission : uint8_t {
    READ = 1,      // 0b001
    WRITE = 2,     // 0b010
    EXECUTE = 4    // 0b100
};

class Permissions {
    uint8_t flags_;
public:
    Permissions() : flags_(0) {}
    
    // Выдать право доступа
    void grant(Permission p) {
        // TODO: реализуйте метод
    }
    
    // Отозвать право доступа
    void revoke(Permission p) {
        // TODO: реализуйте метод
    }
    
    // Проверить наличие права
    bool check(Permission p) const {
        // TODO: реализуйте метод
        return false;
    }
    
    // Проверить наличие всех указанных прав
    bool checkAll(uint8_t permissions) const {
        // TODO: реализуйте метод
        return false;
    }
    
    // Проверить наличие хотя бы одного из указанных прав
    bool checkAny(uint8_t permissions) const {
        // TODO: реализуйте метод
        return false;
    }
};

// Код для проверки
void testPermissions() {
    Permissions perm;
    
    // Тест базовых операций
    perm.grant(READ);
    assert(perm.check(READ));
    assert(!perm.check(WRITE));
    
    perm.grant(WRITE);
    assert(perm.check(WRITE));
    
    perm.revoke(READ);
    assert(!perm.check(READ));
    assert(perm.check(WRITE));
    
    // Тест комбинаций прав
    perm.grant(READ);
    perm.grant(EXECUTE);
    
    assert(perm.checkAll(READ | WRITE));  // Есть оба права
    assert(perm.checkAll(READ | WRITE | EXECUTE));  // Нет всех прав
    
    assert(perm.checkAny(READ | EXECUTE));  // Есть хотя бы одно право
    assert(!perm.checkAny(Permission(8)));  // Нет ни одного права из запрошенных
    
    std::cout << "Permissions tests passed!\n";
}

int main() {
    testPermissions();
    return 0;
}
