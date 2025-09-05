Конструкторы для начинающих
В уроках этой темы разберёмся в приёмах, позволяющих рефакторить код, который становится слишком тяжёлым для понимания и использования.
Перед вами решение задачи об электронной книге из первой темы этого спринта.
Ebook

#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class ReadingManager {
public:
    ReadingManager()
        : user_page_counts_(MAX_USER_COUNT_ + 1, -1)
        ,  // -1 значит, что не случилось ни одного READ
        page_achieved_by_count_(MAX_PAGE_COUNT_ + 1, 0) {
    }

    void Read(int user_id, int page_count) {
        UpdatePageRange(user_page_counts_[user_id] + 1, page_count + 1);
        user_page_counts_[user_id] = page_count;
    }

    double Cheer(int user_id) const {
        const int pages_count = user_page_counts_[user_id];
        if (pages_count == -1) {
            return 0;
        }
        const int user_count = GetUserCount();
        if (user_count == 1) {
            return 1;
        }
        // По умолчанию деление целочисленное, поэтому
        // нужно привести числитель к типу double.
        // Один из простых способов сделать это — умножить его на 1.0.
        return (user_count - page_achieved_by_count_[pages_count]) * 1.0 / (user_count - 1);
    }

private:
    static const int MAX_USER_COUNT_ = 100'000;
    static const int MAX_PAGE_COUNT_ = 1'000;

    // Номер страницы, до которой дочитал пользователь <ключ>
    vector<int> user_page_counts_;
    // Количество пользователей, дочитавших (как минимум) до страницы <индекс>
    vector<int> page_achieved_by_count_;

    int GetUserCount() const {
        return page_achieved_by_count_[0];
    }

    void UpdatePageRange(int lhs, int rhs) {
        for (int i = lhs; i < rhs; ++i) {
            ++page_achieved_by_count_[i];
        }
    }
};

int main() {
    ReadingManager manager;

    int query_count;
    cin >> query_count;

    for (int query_id = 0; query_id < query_count; query_id++) {
        string query_type;
        cin >> query_type;
        int user_id;
        cin >> user_id;

        if (query_type == "READ"s) {
            int page_count;
            cin >> page_count;
            manager.Read(user_id, page_count);
        } else if (query_type == "CHEER"s) {
            cout << setprecision(6) << manager.Cheer(user_id) << endl;
        }
    }
} 
У класса ReadingManager было две константы:

static const int MAX_USER_COUNT_ = 100'000;
static const int MAX_PAGE_COUNT_ = 1'000; 
Пусть теперь эти значения станут вариативными и будут передаваться в качестве аргументов конструктора:

ReadingManager(int max_user_count, int max_page_count)
        : user_page_counts_(max_user_count + 1, -1),
          page_achieved_by_count_(max_page_count + 1, 0)
{
} 
Пусть и метод Cheer использует также некий множитель cheer_factor. Он нужен, чтобы подсчитать результат работы этого метода:

ReadingManager(int max_user_count, int max_page_count, double cheer_factor)
        : user_page_counts_(max_user_count + 1, -1),
          page_achieved_by_count_(max_page_count + 1, 0),
          cheer_factor_(cheer_factor)
{
} 
Теперь вызов конструктора выглядит так:

ReadingManager manager(20000, 1000, 2); 
Человек, читающий ваш код, будет изрядно озадачен этой строчкой. Чтобы разобраться, ему придётся посмотреть на список аргументов конструктора и попытаться сопоставить их с числами. Не всегда это умственное упражнение проходит без ошибок и с первого раза. Более того, сам автор кода мог ошибиться и передать аргументы в неверном порядке. Например, вот так:

ReadingManager manager(1000, 20000, 2); 
Компилятор доволен, программа запускается и работает. Но что-то идёт не так. Хорошо, если баг быстро обнаруживается.
Чтобы помочь себе и читателю, можно просто добавить комментарии:

ReadingManager manager(
   /* max_user_count */ 20000, 
   /* max_page_count */ 1000, 
   /* cheer_factor */   2); 
Так стало лучше, но ряд неудобств остался.
Определите, где преимущество данного способа рефакторинга, где недостаток, а что вообще к делу не относится:
Понятно любому читателю, даже не самому опытному.
преимущество
Сохраняет функционал неизменным.
преимущество
Легко масштабируется.
преимущество
Не защищает от ошибок в порядке передачи аргументов.
недостаток
Практически нет трудовых затрат на реализацию этого способа.
преимущество
Как и любые комментарии, описание в какой-то момент может разойтись с реальным содержанием.
недостаток
Как вам задача?


Этот метод работает, и основное его преимущество — простота. Но остаётся достаточно много проблем. Вариант ответа о сохранении функционала кода к делу отношения не имеет, так как любой рефакторинг подразумевает сохранение функционала в исходном виде.
В следующих уроках вы постепенно узнаете о более трудозатратных, но более эффективных и гибких методах рефакторинга.




Конструкторы для продвинутых
Идея с комментариями, рассмотренная в прошлом уроке, глобально плоха одним моментом — программист всё ещё мог ошибиться в порядке передачи аргументов. В этом уроке вы научитесь рефакторить конструкторы так, чтобы перестать зависеть от этого порядка.
Когда вызов конструктора выглядит так, появляется проблема — параметры могут быть переданы в неправильном порядке:

ReadingManager manager(1000, 20000, 2); 
Проблему можно решить созданием методов, которые определят значение конкретного параметра. Проще говоря, методов-сеттеров. Уберём параметры у конструктора и создадим такие методы:

class ReadingManager {
public:
    ReadingManager();

    void SetMaxUserCount(int max_user_count) {
        max_user_count_ = max_user_count;
    }
    
    void SetMaxPageCount(int max_page_count) {
        max_page_count_ = max_page_count;
    }
    
    void SetCheerFactor(double cheer_factor) {
        cheer_factor_ = cheer_factor;
    }
    ...
private:
   int max_user_count_ = 0;
   int max_page_count_ = 0;
   double cheer_factor_ = 0;
}; 
Теперь подготовка объекта класса ReadingManager будет выглядеть так:

ReadingManager manager;
manager.SetMaxUserCount(20000);
manager.SetMaxPageCount(1000);
manager.SetCheerFactor(2); 
Пока всё в порядке, но вдруг кто-нибудь из пользователей решил вызвать другие методы класса ReadingManager до вызова сеттеров:

ReadingManager manager;
manager.Read(0, 1); 
Пользователь прав. Ничего не мешает ему сделать именно так. Но это добавляет нам проблем.
Каких?


Правильный ответ
Теперь после вызова конструктора объект на самом деле не сконструирован до конца, использование его методов вызывает неопределённое поведение.
Верно, после вызова конструктора объект не готов к работе, а это противоречит самой идее конструктора.

Придётся ограничить пользователя и убрать другие методы в секцию private.
Идея ограничить пользователя бывает верной, но здесь невозможно убрать все методы в private, ведь тогда пользователь просто не сможет их вызвать не только сразу после конструктора, но и вообще никогда.

Правильный ответ
Нужно переписывать другие методы класса.
Верно, ведь если вызвать другие методы с нулевыми значениями для max_user_count_ и других полей, алгоритм не будет работать.
Как вам задача?


Такой способ рефакторинга может работать, но, как видите, он тоже не идеален. Продолжим улучшать код в следующем уроке.
Сформулируем точнее проблему, которая возникла в конце прошлого урока. У объекта ReadingManager есть две фазы жизненного цикла: инициализация и использование. Использование невозможно до окончания инициализации. Нужно разделить эти две фазы, чтобы гарантировать их непересечение.
Проблема сформулирована, решим её. Выделим отдельный класс для инициализации и назовём его ReadingManagerBuilder:

class ReadingManagerBuilder {
public:
    void SetMaxUserCount(int max_user_count) {
        max_user_count_ = max_user_count;
    }

    void SetMaxPageCount(int max_page_count) {
        max_page_count_ = max_page_count;
    }

    void SetCheerFactor(double cheer_factor) {
        cheer_factor_ = cheer_factor;
    }

    ReadingManager Build() const {
        if (max_user_count_ <= 0) {
            // ...
        }
        return {max_user_count_, max_page_count_, cheer_factor_};
    }

private:
    int max_user_count_;
    int max_page_count_;
    double cheer_factor_;
}; 
Теперь можно вернуть на место конструктор ReadingManager с тремя параметрами. Однако сделать это нужно хитро. Программист бы не хотел, чтобы обычный пользователь вызывал этот конструктор. Но у ReadingManagerBuilder должно получиться.
Магию какого ключевого слова можно применить в этом случае?


switch

Нужно использовать наследование без всяких волшебных слов.

Правильный ответ
friend

please
Как вам задача?


Ключевое слово friend разрешит методам класса ReadingManagerBuilder доступ к секции private класса ReadingManager.
Выглядеть это будет так:

class ReadingManager {
public:
    friend class ReadingManagerBuilder;
    ...

private:
    vector<int> user_page_counts_;
    vector<int> page_achieved_by_count_;
    double cheer_factor_= 0;

    ReadingManager(int max_user_count, int max_page_count, double cheer_factor)
        : user_page_counts_(max_user_count + 1, -1),
          page_achieved_by_count_(max_page_count + 1, 0),
          cheer_factor_(cheer_factor)
    {
    }

    ...
}; 
Теперь пользователь надёжно защищён от недоразумений:

ReadingManagerBuilder builder;
builder.SetMaxUserCount(20000);
builder.SetMaxPageCount(1000);
builder.SetCheerFactor(2);
ReadingManager manager = builder.Build(); 
Ну и вишенка на торте.
Какой тип должны возвращать сеттеры, чтобы пользователь мог сконструировать объект ReadingManager так?

ReadingManager manager = 
    ReadingManagerBuilder().SetMaxUserCount(20000).SetMaxPageCount(1000).SetCheerFactor(2).Build(); 


ReadingManager&

ReadingManager

Правильный ответ
ReadingManagerBuilder&

const ReadingManagerBuilder&

ReadingManagerBuilder
Как вам задача?


Возвращение ссылки на текущий объект ReadingManagerBuilder& позволит реализовать приём, называемый Fluent interface.
Вернёмся к изначальной проблеме. Ради её решения возникла идея сеттеров. Пользователь мог перепутать параметры конструктора местами, и понимание вызова конструктора вызывало трудности. После рефакторинга, проведённого в рамках этого урока, программисту больше не надо контролировать порядок аргументов конструктора.

Конструкторы для мастеров
В этом уроке мы коротко разберём ещё три подхода к рефакторингу конструктора с длинным списком аргументов.
Подход 1. Оператор неявного преобразования вместо метода Build
Можно избавиться от необходимости вызывать метод Build, воспользовавшись оператором приведения типа:

class ReadingManagerBuilder {
public:
    ReadingManagerBuilder& SetMaxUserCount(int max_user_count);
    ReadingManagerBuilder& SetMaxPageCount(int max_page_count);
    ReadingManagerBuilder& SetCheerFactor(double cheer_factor);

    operator ReadingManager() const {
        // throw exception if not valid
        return {max_user_count_, max_page_count_, cheer_factor_};
    }

private:
    int max_user_count_;
    int max_page_count_;
    double cheer_factor_;
}; 
Указанный оператор автоматически вызовется при попытке преобразовать ReadingManagerBuilder к ReadingManager:

ReadingManager manager = 
    ReadingManagerBuilder().
    SetMaxUserCount(10000).
    SetMaxPageCount(500).
    SetCheerFactor(2); 
Код стал более компактным, но непрозрачность такого преобразования и возможность выброса исключения в процессе него часто становятся аргументом против этого подхода.
Подход 2. Принимать в конструкторе ReadingManager структуру, созданную с помощью Set-методов
Такой способ рефакторинга будет понятен даже неискушенному пользователю. Если у конструктора ReadingManager слишком много параметров, объединим эти параметры в структуру. А уж с созданием этой структуры как-нибудь разберёмся:

class ReadingManager {
public:
    ReadingManager(const ReadingManagerParams& params);
    // ...

private:
    // ...
}; 
В данном случае валидность набора параметров будет проверять сам конструктор.
Структуру ReadingManagerParams можно почти полностью списать с ReadingManagerBuilder:

struct ReadingManagerParams {
    int max_user_count;
    int max_page_count;
    double cheer_factor;

    ReadingManagerParams& SetMaxUserCount(int max_user_count) {
        this->max_user_count = max_user_count;
        return *this;
    }

    ReadingManagerParams& SetMaxPageCount(int max_page_count) {
        this->max_page_count = max_page_count;
        return *this;
    }

    ReadingManagerParams& SetCheerFactor(double cheer_factor) {
        this->cheer_factor = cheer_factor;
        return *this;
    }
}; 
Создание ReadingManager будет выглядеть следующим образом:

ReadingManager manager(
    ReadingManagerParams().
    SetMaxUserCount(10000).
    SetMaxPageCount(500).
    SetCheerFactor(2)
); 
Оставлять ли поля структуры публичными или делать её классом — дело вкуса.
Подход 3. Принимать в конструкторе ReadingManager структуру, созданную с помощью designated initializers
При создании структуры можно указывать названия полей — так называемые designated initializers. Но со следующими оговорками:
Они полностью поддерживаются в языке C.
Они поддерживаются в компиляторах C++, но полулегально, в целях совместимости с C.
Официально в C++ эта возможность появится в стандарте C++20.
Возможность явно указывать названия полей снижает вероятность ошибки и не требует создания Set-методов:

ReadingManager manager(ReadingManagerParams{
    .max_user_count = 10000, 
    .max_page_count = 500, 
    .cheer_factor = 2}
); 

Функции с длинным списком аргументов
Вы подробно изучили проблемы конструкторов с большим количеством параметров и способы решения этих проблем. Теми же недостатками могут обладать любые функции и методы.
Проблемы, присущие функциям с большим количеством параметров:
Когда параметров много, функцию трудно понимать и тестировать.
Когда целочисленных и булевых параметров много, они приводят к ошибкам в месте вызова и необходимости упоминать название аргумента рядом с его значением.
В качестве примера рассмотрим гипотетическую функцию парсинга (разбора) поискового запроса:

Query ParseQuery(string_view text, 
                 int country_id, 
                 int max_word_count, 
                 int max_word_length, 
                 int max_form_count_per_word,
                 bool allow_minus_words, 
                 bool keep_stop_words, 
                 bool case_sensitive); 
Pазъясним смысл параметров:
text — сам поисковый запрос;
country_id — id страны, из которой он пришёл;
max_word_count — максимальное количество слов, которое будет учтено;
max_word_length — максимальное количество букв слова, которое будет учтено;
max_form_count_per_word — максимальное количество словоформ, генерируемых на одно слово;
allow_minus_words — обрабатывать ли минус-слова;
keep_stop_words — считать ли стоп-слова полноценными словами;
case_sensitive — учитывать ли регистр слов.
Вызов этой функции может доставить серьёзный дискомфорт человеку, читающему код:

const Query query = ParseQuery(text, 225, 7, 23, 20, true, false, false); 
Аргументы можно снабжать комментариями, но это не защитит от ошибок:

const Query query = ParseQuery(text, /* country_id */ 7,
                               /* max_word_count */ 225,
                               /* max_word_length */ 23,
                               /* max_form_count_per_word */ 20,
                               /* allow_minus_words */ true,
                               /* keep_stop_words */ false,
                               /* case_sensitive */ false); 
Структура для параметров
Решение, известное из предыдущего урока, — объединение параметров функции в структуру с Set-методами. Громоздко, но безотказно.
В случае функции ParseQuery можно было бы вынести в ParsingParams последние шесть параметров:

const Query query = ParseQuery( text, 225,
                                ParsingParams().
                                SetMaxWordCount(7).
                                SetMaxWordLength(23).
                                SetMaxFormCountPerWord(20).
                                SetAllowMinusWords(true)); 
Параметрам keep_stop_words и case_sensitive можно присвоить значения по умолчанию, которые они получат при отсутствии вызова соответствующих Set-методов. Это позволит не указывать их при инициализации ParsingParams.
Вот так будет выглядеть вызов функции при использовании designated initializers. Зададим все параметры для наглядности:

const Query query = ParseQuery(text, 225,
                               {.max_word_count = 7,
                                .max_word_length = 23,
                                .max_form_count_per_word = 20,
                                .allow_minus_words = true,
                                .keep_stop_words = false,
                                .case_sensitive = false}); 
Превращение функции в метод класса
Если требуется распарсить поток запросов с одинаковыми настройками, стоит рассмотреть вариант создания класса QueryParser с инициализацией по одной из рассмотренных выше методологий и методом Parse:

class QueryParser {
public:
    QueryParser(const ParsingParams& params);
    Query Parse(string_view text, int country_id);
};

// ...

QueryParser parser(ParsingParams{.max_word_count = 7,
                                 .max_word_length = 23,
                                 .max_form_count_per_word = 20,
                                 .allow_minus_words = true,
                                 .keep_stop_words = false,
                                 .case_sensitive = false});

// ...

const Query query = parser.Parse(text, 225); 
Все предыдущие идеи во многом касались структурирования параметров функции. Теперь разберём несложные способы усовершенствовать работу с булевыми и числовыми параметрами.
Использование enum вместо bool
Для некоторых bool-параметров может быть оправдан переход на enum. Например, в будущем вы можете захотеть добавить ещё один режим учёта стоп-слов: учитывать их только в том случае, если перед ними идёт символ +. Тогда можно добавить enum-тип StopWordsMode «на вырост», тем самым повысив читаемость вызова функции и избежав шанса перепутать параметры с другими аргументами типа int и bool:

enum class StopWordsMode {
    IGNORE,
    KEEP,
    // в будущем этот класс можно будет расширять
};

Query ParseQuery(string_view text, int country_id, int max_word_count, int max_word_length, int max_form_count_per_word,
                 bool allow_minus_words, StopWordsMode stop_words_mode, bool case_sensitive);

// ...

const Query query = ParseQuery(text, 225, 7, 23, 20, true, StopWordsMode::IGNORE, false); 
Объединение булевых параметров в маску
Беззнаковые числовые типы часто используются как хранилище битов: например, число типа uint64_t позволяет сохранить 64 булевых значения. Поэтому булевы флаги можно объединить в один enum ParsingFlag и собрать из подручных средств такую конструкцию:

enum class ParsingFlag {
    // значения, являющиеся степенями двойки,
    // позволяют работать с масками без дополнительных
    // преобразований вида 1 << value
    ALLOW_MINUS_WORDS = 1 << 0,  // 001
    KEEP_STOP_WORDS = 1 << 1,    // 010
    CASE_SENSITIVE = 1 << 2      // 100
};

using ParsingFlags = uint64_t;

Query ParseQuery(string_view text, int country_id, int max_word_count, int max_word_length, int max_form_count_per_word,
                 ParsingFlags flags) {
    // ...
    if (flags & static_cast<ParsingFlags>(ParsingFlag::KEEP_STOP_WORDS)) {
        // обработка запроса с учётом флага KEEP_STOP_WORDS
    }
    // ...
}

// ...

const Query query = ParseQuery(text, 225, 7, 23, 20,
                               static_cast<ParsingFlags>(ParsingFlag::ALLOW_MINUS_WORDS)
                               | static_cast<ParsingFlags>(ParsingFlag::KEEP_STOP_WORDS));
                               // выключенные флаги не указываются в списке 
Довольно неудобно писать всюду static_cast, поэтому можно создать простой шаблон Flags и определить для Flags<ParsingFlag> и ParsingFlag операторы & и | так, чтобы следующий код работал, как предыдущий:

enum class ParsingFlag { 
    ALLOW_MINUS_WORDS = 1 << 0, 
    KEEP_STOP_WORDS = 1 << 1, 
    CASE_SENSITIVE = 1 << 2 
};

using ParsingFlags = Flags<ParsingFlag>;

Query ParseQuery(string_view text, int country_id, int max_word_count, int max_word_length, int max_form_count_per_word,
                 ParsingFlags flags) {
    // ...
    if (flags & ParsingFlag::KEEP_STOP_WORDS) {
        // обработка запроса с учётом флага KEEP_STOP_WORDS
    }
    // ...
}

// ...

const Query query = ParseQuery(text, 225, 7, 23, 20, 
                               ParsingFlag::ALLOW_MINUS_WORDS | ParsingFlag::KEEP_STOP_WORDS); 
Отдельные типы для числовых параметров
Наконец, посмотрим, что сделать с числовыми параметрами функций для повышения прозрачности и безопасности вызовов.
Безопасности не будет без типизации. Поэтому определим для каждого числового параметра свой тип с explicit-конструктором:

struct CountryId {
    int value;
    explicit CountryId(int v)
        : value(v) 
    {
    }
};

struct MaxWordCount {
    int value;
    explicit MaxWordCount(int v)
        : value(v) 
    {
    }
};

struct MaxWordLength {
    int value;
    explicit MaxWordLength(int v)
        : value(v) 
    {
    }
};

struct MaxFormCountPerWord {
    int value;
    explicit MaxFormCountPerWord(int v)
        : value(v) 
    {
    }
};

Query ParseQuery(string_view text, 
                 CountryId country_id, 
                 MaxWordCount max_word_count, 
                 MaxWordLength max_word_length,
                 MaxFormCountPerWord max_form_count_per_word, 
                 bool allow_minus_words, 
                 bool keep_stop_words,
                 bool case_sensitive);

// ...

const Query query = ParseQuery(text, CountryId(225), 
                               MaxWordCount(7), 
                               MaxWordLength(23), 
                               MaxFormCountPerWord(20), 
                               true, false, false); 
То же можно проделать и для булевых параметров.
Определение каждой такой структуры довольно однотипно, поэтому напрашивается макрос DECLARE_INT_PARAM:

#define DECLARE_INT_PARAM(Name) \
    struct Name {               \
        int value;              \
        explicit Name(int v)    \
            : value(v) {        \
        }                       \
    }

DECLARE_INT_PARAM(CountryId);
DECLARE_INT_PARAM(MaxWordCount);
DECLARE_INT_PARAM(MaxWordLength);
DECLARE_INT_PARAM(MaxFormCountPerWord); 
Можно доработать этот макрос так, чтобы разрешить подобным типам автоматически приводиться к int. Вы избавите авторов функции от необходимости постоянно обращаться к полю value:

#define DECLARE_INT_PARAM(Name) \
    struct Name {               \
        int value;              \
        explicit Name(int v)    \
            : value(v) {        \
        }                       \
        operator int() const {  \
            return value;       \
        }                       \
    } 
Ещё один способ создания подобных типов, принятый в том числе и в стандартной библиотеке, — определение специальных суффиксов. Они позволяют писать так:

const Query query = ParseQuery(text, CountryId(225),
                               7_words, 23_letters, 20_forms,
                               true, false, false); 
Определение таких суффиксов возможно благодаря строковым литералам. operator"" решает эту задачу так:

auto operator""_words(unsigned long long value) {
    return MaxWordCount(value);
}

auto operator""_letters(unsigned long long value) {
    return MaxWordLength(value);
}

auto operator""_forms(unsigned long long value) {
    return MaxFormCountPerWord(value);
} 
Числовой параметр такого оператора обязан иметь тип unsigned long long.
По сути выражение 7_words эквивалентно вызову operator""_words(7) и, в конечном счёте, MaxWordCount(7).
Итоги
Есть несколько способов борьбы с громоздкостью и запутанностью списка параметров функции:
Сгруппировать параметры в структуры.
Сделать функцию методом класса, унеся глобальный контекст из параметров функции в поля класса.
Использовать enum для булевых параметров: свой для каждого или один общий — с маской.
Определять отдельные типы для числовых параметров, снабжая их explicit-конструкторами или другими способами явного создания при вызове функции.