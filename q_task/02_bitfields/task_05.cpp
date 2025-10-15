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
    uint16_t length_;
    uint8_t service_type_;
    uint8_t header_len_:4;
    uint8_t ver_:4;
    
    // Конструктор с параметрами
    NetworkPacket(uint8_t ver, uint8_t header_len, uint8_t service_type, uint16_t length):
    length_(length),
    service_type_(service_type),
    header_len_(header_len),
    ver_(ver)
    {
        // TODO: реализуйте конструктор
    }
    
    // Методы доступа к полям
    uint8_t getVersion() const {
        // TODO: реализуйте метод
        return ver_;
    }
    
    uint8_t getHeaderLength() const {
        // TODO: реализуйте метод
        return header_len_;
    }
    
    uint8_t getTypeOfService() const {
        // TODO: реализуйте метод
        return service_type_;
    }
    
    uint16_t getTotalLength() const {
        // TODO: реализуйте метод
        return length_;
    }
    
    // Сериализация в массив байт
    void serialize(uint8_t* buffer) const {
        buffer[0] = (ver_ << 4) | header_len_;
        buffer[1] = service_type_;
        buffer[2] = length_ >> 8;
        buffer[3] = length_ & 0xFF;
    }
    
    // Десериализация из массива байт
    static NetworkPacket deserialize(const uint8_t* buffer) {
        // TODO: реализуйте метод
        return NetworkPacket(buffer[0]>>4, buffer[0] & 0x0F, buffer[1], (buffer[2] << 8) | buffer[3]);
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
