#include <iostream>
#include <cstdint>

// Task 5: Сетевой пакет
// 
// Реализуйте структуру NetworkPacket, которая представляет заголовок сетевого пакета:
// 1. version: 4 бита (версия протокола 0-15)
// 2. ihl: 4 бита (длина заголовка 0-15)
// 3. tos: 8 бит (тип сервиса)
// 4. total_length: 16 бит (общая длина)
//
// Структура должна:
// - Корректно работать на big-endian и little-endian системах
// - Иметь методы для доступа к полям
// - Поддерживать сериализацию в массив байт

struct NetworkPacket {
    // TODO: реализуйте структуру
    
    // Конструктор с параметрами
    NetworkPacket(uint8_t ver, uint8_t header_len, uint8_t service_type, uint16_t length) {
        // TODO: реализуйте конструктор
    }
    
    // Методы доступа к полям
    uint8_t getVersion() const {
        // TODO: реализуйте метод
        return 0;
    }
    
    uint8_t getHeaderLength() const {
        // TODO: реализуйте метод
        return 0;
    }
    
    uint8_t getTypeOfService() const {
        // TODO: реализуйте метод
        return 0;
    }
    
    uint16_t getTotalLength() const {
        // TODO: реализуйте метод
        return 0;
    }
    
    // Сериализация в массив байт
    void serialize(uint8_t* buffer) const {
        // TODO: реализуйте метод
    }
    
    // Десериализация из массива байт
    static NetworkPacket deserialize(const uint8_t* buffer) {
        // TODO: реализуйте метод
        return NetworkPacket(0, 0, 0, 0);
    }
};

// Код для проверки
void testNetworkPacket() {
    // Создание пакета
    NetworkPacket packet(4, 5, 0x0C, 1500);
    
    // Проверка значений
    assert(packet.getVersion() == 4);
    assert(packet.getHeaderLength() == 5);
    assert(packet.getTypeOfService() == 0x0C);
    assert(packet.getTotalLength() == 1500);
    
    // Тест сериализации
    uint8_t buffer[4];
    packet.serialize(buffer);
    
    // Тест десериализации
    NetworkPacket restored = NetworkPacket::deserialize(buffer);
    assert(restored.getVersion() == packet.getVersion());
    assert(restored.getHeaderLength() == packet.getHeaderLength());
    assert(restored.getTypeOfService() == packet.getTypeOfService());
    assert(restored.getTotalLength() == packet.getTotalLength());
    
    std::cout << "NetworkPacket tests passed!\n";
}

int main() {
    testNetworkPacket();
    return 0;
}
