#include <string>
#include <vector>
#include <utility>

// Task 9: Копирование константных объектов
// 
// Реализуйте класс Document, который:
// 1. Правильно обрабатывает копирование константных объектов
// 2. Предоставляет корректную семантику присваивания
// 3. Защищает внутренние данные от модификации
// 4. Позволяет эффективное перемещение

class Document {
    std::string title_;
    std::vector<std::string> content_;
    mutable size_t access_count_ = 0;

public:
    // Базовый конструктор
    Document(std::string title) : title_(std::move(title)) {}
    
    // TODO: Реализуйте:
    
    // 1. Конструктор копирования
    Document(const Document& other) {
        // TODO: реализуйте
        // - Должен работать с константными объектами
        // - Должен корректно копировать все поля
        // - Должен обеспечивать strong exception guarantee
    }
    
    // 2. Оператор присваивания копированием
    Document& operator=(const Document& other) {
        // TODO: реализуйте
        // - Должен работать с константными объектами
        // - Должен быть защищен от самоприсваивания
        // - Должен обеспечивать strong exception guarantee
        return *this;
    }
    
    // 3. Конструктор перемещения
    Document(Document&& other) {
        // TODO: реализуйте
        // - Должен работать только с неконстантными объектами
        // - Должен корректно перемещать ресурсы
        // - Должен оставлять источник в валидном состоянии
    }
    
    // 4. Оператор присваивания перемещением
    Document& operator=(Document&& other) {
        // TODO: реализуйте
        // - Должен работать только с неконстантными объектами
        // - Должен быть защищен от самоприсваивания
        // - Должен корректно перемещать ресурсы
        return *this;
    }
    
    ~Document() = default;

    // Вспомогательные методы
    void addLine(const std::string& line) { content_.push_back(line); }
    const std::string& getTitle() const { return title_; }
    const std::vector<std::string>& getContent() const { return content_; }
    size_t getAccessCount() const { return access_count_; }
};

// Код для проверки
void testConstCopy() {
    Document doc1("Original");
    doc1.addLine("Line 1");
    doc1.addLine("Line 2");
    
    const Document const_doc("Const");
    const_doc.getContent(); // Увеличивает access_count
    
    // Эти строки должны компилироваться:
    Document doc2 = const_doc;              // Копирование константного объекта
    Document doc3(const_doc);               // Копирование константного объекта
    doc1 = const_doc;                       // Присваивание константного объекта
    Document doc4 = std::move(doc1);        // Перемещение неконстантного объекта
    doc2 = std::move(doc3);                 // Перемещение неконстантного объекта
    
    // Эти строки НЕ должны компилироваться:
    // Document doc5 = std::move(const_doc);  // Нельзя перемещать константный объект
    // doc4 = std::move(const_doc);           // Нельзя перемещать константный объект
}

int main() {
    testConstCopy();
    return 0;
}
