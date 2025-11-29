#include <string>
#include <vector>
#include <iostream>

// Task 9: Копирование константных объектов
//
// Реализуй класс Document с правильной обработкой копирования константных объектов.
// Конструктор копирования и оператор присваивания должны работать с const объектами,
// но сам объект должен быть non-const для присваивания.
//
// Требования:
// 1. Конструктор копирования принимает const ссылку
// 2. Оператор присваивания принимает const ссылку
// 3. Можно копировать из const объекта в non-const
// 4. Нельзя присваивать const объекту (сам объект должен быть non-const)
// 5. Правильная обработка mutable полей при копировании

class Document {
    std::string title_;
    std::vector<std::string> content_;
    mutable size_t access_count_ = 0;  // Статистика доступа

public:
    Document(std::string title) : title_(std::move(title)) {}
    
    void addLine(const std::string& line) { 
        content_.push_back(line); 
    }
    
    const std::string& getTitle() const { 
        ++access_count_;  // mutable позволяет изменять в const методе
        return title_; 
    }
    
    const std::vector<std::string>& getContent() const { 
        ++access_count_;
        return content_; 
    }
    
    size_t getAccessCount() const { 
        return access_count_; 
    }
    
    // TODO: Реализуй конструктор копирования
    // Должен принимать const ссылку и корректно копировать все поля
    Document(const Document& other) {
        // TODO: реализуй копирование
        // Вопрос: нужно ли копировать access_count_? Обычно статистику сбрасывают
    }
    
    // TODO: Реализуй оператор присваивания копированием
    // Должен принимать const ссылку, защищён от самоприсваивания
    Document& operator=(const Document& other) {
        // TODO: реализуй с защитой от самоприсваивания
        return *this;
    }
    
    // Деструктор по умолчанию
    ~Document() = default;
};

void testConstCopy() {
    Document doc1("Original");
    doc1.addLine("Line 1");
    doc1.addLine("Line 2");
    
    // Доступ к const объекту увеличивает счётчик
    const Document const_doc("Const");
    const_doc.getContent();  // access_count_ = 1
    
    // Эти строки должны компилироваться:
    Document doc2 = const_doc;              // Копирование из const объекта
    Document doc3(const_doc);               // Копирование из const объекта
    doc1 = const_doc;                       // Присваивание из const объекта
    
    // Проверка, что копирование работает
    std::cout << "Doc2 title: " << doc2.getTitle() << "\n";
    std::cout << "Doc2 access count: " << doc2.getAccessCount() << "\n";
    
    // Эти строки НЕ должны компилироваться:
    // const Document const_doc2("Test");
    // const_doc2 = doc1;                     // Ошибка: нельзя присваивать const объекту
    // const_doc = doc1;                     // Ошибка: нельзя присваивать const объекту
}

int main() {
    testConstCopy();
    return 0;
}
