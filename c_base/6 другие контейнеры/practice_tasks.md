# Практические задания: Другие контейнеры

## Задание 1: Система обработки выражений с несколькими типами скобок

### Описание
Создайте систему для проверки корректности расстановки скобок в математических выражениях. Система должна поддерживать круглые `()`, квадратные `[]` и фигурные `{}` скобки, а также вычислять значения простых арифметических выражений.

### Требования
- Используйте `std::stack` для проверки соответствия скобок
- Реализуйте вычисление выражений в постфиксной записи
- Поддержите операции: `+`, `-`, `*`, `/`, `^` (степень)
- Обработайте ошибки: несоответствие скобок, деление на ноль, некорректные символы
- Используйте современные возможности C++17 (auto, structured bindings)

### Интерфейс
```cpp
class ExpressionProcessor {
public:
    struct Result {
        bool is_valid;
        double value;
        std::string error_message;
    };
    
    Result EvaluateExpression(const std::string& expression);
    bool CheckBrackets(const std::string& expression);
    std::string ConvertToPostfix(const std::string& infix);
    double EvaluatePostfix(const std::string& postfix);
};
```

### Тесты
1. Простые выражения: `"(2+3)*4"` → 20
2. Сложные скобки: `"[{(1+2)*3}+4]"` → 13  
3. Ошибка скобок: `"((2+3)"` → false
4. Степень: `"2^3+1"` → 9
5. Деление на ноль: `"5/0"` → error
6. Пустое выражение: `""` → error
7. Вложенные скобки: `"((((1))))"` → 1
8. Смешанные операции: `"2*3+4/2-1"` → 7
9. Отрицательные числа: `"(-5+3)*2"` → -4
10. Десятичные числа: `"1.5*2.5"` → 3.75

---

## Задание 2: Многопоточная система обработки задач с приоритетами

### Описание
Реализуйте систему планировщика задач, которая использует очередь приоритетов для обработки задач разного типа. Система должна поддерживать добавление задач с разными приоритетами и их выполнение в правильном порядке.

### Требования
- Используйте `std::priority_queue` для хранения задач
- Реализуйте разные типы задач (CPU, I/O, Network)
- Поддержите динамическое изменение приоритетов
- Добавьте статистику выполнения задач
- Используйте кастомные компараторы для сложной логики приоритетов

### Интерфейс
```cpp
enum class TaskType { CPU, IO, NETWORK };
enum class Priority { LOW = 1, MEDIUM = 2, HIGH = 3, CRITICAL = 4 };

struct Task {
    std::string id;
    TaskType type;
    Priority priority;
    std::chrono::milliseconds estimated_time;
    std::function<void()> work;
    std::chrono::steady_clock::time_point created_at;
};

class TaskScheduler {
public:
    void AddTask(Task task);
    void ProcessTasks(size_t max_tasks = 0);
    void ChangePriority(const std::string& task_id, Priority new_priority);
    std::vector<std::string> GetPendingTasks() const;
    double GetAverageWaitTime() const;
    size_t GetTaskCount(TaskType type) const;
};
```

### Тесты
1. Добавление задач разных приоритетов
2. Обработка в порядке приоритета
3. Изменение приоритета задачи
4. Статистика времени ожидания
5. Обработка одного типа задач
6. Пустая очередь задач
7. Добавление критических задач
8. Подсчет задач по типам
9. Обработка большого количества задач
10. Задачи с одинаковым приоритетом (FIFO)

---

## Задание 3: Оптимизированная система истории команд с откатом

### Описание
Создайте систему для хранения и отката команд в текстовом редакторе. Используйте `std::deque` для эффективного добавления команд в начало и конец, а также для быстрого доступа к истории.

### Требования
- Используйте `std::deque` для хранения команд
- Реализуйте команды: Insert, Delete, Replace, Move
- Поддержите undo/redo операции
- Ограничьте размер истории (LRU-подобное поведение)
- Добавьте сериализацию истории команд

### Интерфейс
```cpp
enum class CommandType { INSERT, DELETE, REPLACE, MOVE };

struct Command {
    CommandType type;
    size_t position;
    std::string old_text;
    std::string new_text;
    std::chrono::steady_clock::time_point timestamp;
};

class CommandHistory {
public:
    explicit CommandHistory(size_t max_size = 1000);
    
    void ExecuteCommand(const Command& cmd);
    bool Undo();
    bool Redo();
    void ClearHistory();
    std::vector<Command> GetRecentCommands(size_t count) const;
    void SaveToFile(const std::string& filename) const;
    bool LoadFromFile(const std::string& filename);
    size_t GetMemoryUsage() const;
};

class TextEditor {
public:
    void Insert(size_t pos, const std::string& text);
    void Delete(size_t pos, size_t length);
    void Replace(size_t pos, size_t length, const std::string& text);
    std::string GetText() const;
    CommandHistory& GetHistory();
};
```

### Тесты
1. Выполнение простых команд
2. Undo последней команды
3. Redo отмененной команды
4. Переполнение истории
5. Очистка истории
6. Сохранение и загрузка истории
7. Получение последних команд
8. Подсчет используемой памяти
9. Сложная последовательность undo/redo
10. Команды с большими текстами

---

## Задание 4: Высокопроизводительная система поиска в отсортированных данных

### Описание
Реализуйте систему для эффективного поиска в больших отсортированных массивах данных. Используйте различные алгоритмы бинарного поиска и их оптимизации для разных типов запросов.

### Требования
- Реализуйте несколько вариантов бинарного поиска
- Поддержите поиск диапазонов и приблизительный поиск
- Добавьте параллельные алгоритмы поиска (C++17)
- Используйте кастомные компараторы
- Оптимизируйте для разных типов данных

### Интерфейс
```cpp
template<typename T>
class OptimizedSearch {
public:
    explicit OptimizedSearch(std::vector<T> data);
    
    // Основные методы поиска
    std::optional<size_t> BinarySearch(const T& target) const;
    std::pair<size_t, size_t> FindRange(const T& target) const;
    std::optional<size_t> LowerBound(const T& target) const;
    std::optional<size_t> UpperBound(const T& target) const;
    
    // Приблизительный поиск
    std::optional<size_t> FindClosest(const T& target) const;
    std::vector<size_t> FindAllInRange(const T& min_val, const T& max_val) const;
    
    // Параллельные методы
    std::optional<size_t> ParallelSearch(const T& target) const;
    std::vector<size_t> ParallelMultiSearch(const std::vector<T>& targets) const;
    
    // Статистика
    size_t GetComparisonCount() const;
    void ResetStatistics();
};

// Специализация для строк с дополнительными возможностями
template<>
class OptimizedSearch<std::string> {
public:
    std::vector<size_t> FindByPrefix(const std::string& prefix) const;
    std::vector<size_t> FindBySuffix(const std::string& suffix) const;
    std::vector<size_t> FindByPattern(const std::regex& pattern) const;
};
```

### Тесты
1. Поиск в массиве целых чисел
2. Поиск диапазона одинаковых элементов
3. Поиск несуществующего элемента
4. Поиск ближайшего элемента
5. Поиск по диапазону значений
6. Параллельный поиск большого массива
7. Поиск строк по префиксу
8. Кастомный компаратор для сложных объектов
9. Статистика сравнений
10. Поиск в массиве с дубликатами

---

## Задание 5: Система рекурсивного обхода файловой системы с фильтрацией

### Описание
Создайте систему для рекурсивного обхода директорий с возможностью применения различных фильтров и действий. Реализуйте как рекурсивный, так и итеративный подходы.

### Требования
- Используйте рекурсию для обхода директорий
- Реализуйте итеративную альтернативу с использованием `std::stack`
- Поддержите различные фильтры (по размеру, дате, расширению)
- Добавьте параллельную обработку для больших директорий
- Реализуйте ограничение глубины рекурсии

### Интерфейс
```cpp
struct FileInfo {
    std::string path;
    size_t size;
    std::chrono::file_time_type modified_time;
    bool is_directory;
};

using FileFilter = std::function<bool(const FileInfo&)>;
using FileAction = std::function<void(const FileInfo&)>;

class FileSystemWalker {
public:
    explicit FileSystemWalker(size_t max_depth = 100);
    
    // Рекурсивный обход
    void WalkRecursive(const std::string& root_path, 
                      const FileFilter& filter, 
                      const FileAction& action);
    
    // Итеративный обход
    void WalkIterative(const std::string& root_path,
                      const FileFilter& filter,
                      const FileAction& action);
    
    // Параллельный обход
    void WalkParallel(const std::string& root_path,
                     const FileFilter& filter,
                     const FileAction& action);
    
    // Предустановленные фильтры
    static FileFilter CreateSizeFilter(size_t min_size, size_t max_size);
    static FileFilter CreateExtensionFilter(const std::set<std::string>& extensions);
    static FileFilter CreateDateFilter(std::chrono::file_time_type after);
    
    // Статистика
    size_t GetProcessedFiles() const;
    size_t GetMaxDepthReached() const;
    std::chrono::milliseconds GetProcessingTime() const;
};
```

### Тесты
1. Обход простой директории
2. Фильтрация по размеру файлов
3. Фильтрация по расширению
4. Ограничение глубины рекурсии
5. Сравнение рекурсивного и итеративного подходов
6. Обработка больших директорий
7. Параллельный обход
8. Статистика обработки
9. Комбинированные фильтры
10. Обработка символических ссылок

---

## Задание 6: Продвинутая система сортировки с гибридными алгоритмами

### Описание
Реализуйте систему сортировки, которая автоматически выбирает оптимальный алгоритм в зависимости от характеристик данных. Включите рекурсивные и итеративные алгоритмы.

### Требования
- Реализуйте merge sort, quick sort, heap sort
- Добавьте гибридные алгоритмы (например, intro sort)
- Поддержите параллельную сортировку
- Реализуйте сортировку с кастомными компараторами
- Добавьте профилирование производительности

### Интерфейс
```cpp
enum class SortAlgorithm {
    AUTO, MERGE_SORT, QUICK_SORT, HEAP_SORT, 
    INTRO_SORT, RADIX_SORT, COUNTING_SORT
};

template<typename T>
class AdvancedSorter {
public:
    // Основная сортировка
    void Sort(std::vector<T>& data, SortAlgorithm algorithm = SortAlgorithm::AUTO);
    
    // Сортировка с кастомным компаратором
    template<typename Compare>
    void Sort(std::vector<T>& data, Compare comp, SortAlgorithm algorithm = SortAlgorithm::AUTO);
    
    // Параллельная сортировка
    void ParallelSort(std::vector<T>& data, size_t thread_count = 0);
    
    // Стабильная сортировка
    void StableSort(std::vector<T>& data);
    
    // Частичная сортировка
    void PartialSort(std::vector<T>& data, size_t n);
    
    // Статистика
    struct SortStats {
        SortAlgorithm used_algorithm;
        size_t comparisons;
        size_t swaps;
        std::chrono::microseconds duration;
        size_t memory_usage;
    };
    
    SortStats GetLastSortStats() const;
    static SortAlgorithm ChooseOptimalAlgorithm(size_t size, bool is_nearly_sorted);
    
private:
    void MergeSort(std::vector<T>& data, size_t left, size_t right);
    void QuickSort(std::vector<T>& data, size_t left, size_t right);
    void IntroSort(std::vector<T>& data, size_t left, size_t right, size_t depth_limit);
};
```

### Тесты
1. Автоматический выбор алгоритма
2. Сортировка больших массивов
3. Частично отсортированные данные
4. Сортировка с кастомным компаратором
5. Параллельная сортировка
6. Стабильная сортировка одинаковых элементов
7. Частичная сортировка
8. Профилирование производительности
9. Сортировка строк
10. Сортировка структур по нескольким полям

---

## Задание 7: Система умного кэширования с использованием нескольких контейнеров

### Описание
Создайте многоуровневую систему кэширования, которая использует разные контейнеры для разных уровней кэша. Комбинируйте `std::deque`, `std::priority_queue` и ассоциативные контейнеры.

### Требования
- L1 кэш: быстрый доступ (deque + map)
- L2 кэш: приоритетный (priority_queue)
- L3 кэш: долгосрочное хранение (map)
- Реализуйте различные политики вытеснения (LRU, LFU, TTL)
- Добавьте статистику попаданий/промахов

### Интерфейс
```cpp
enum class EvictionPolicy { LRU, LFU, TTL, RANDOM };

template<typename Key, typename Value>
class MultiLevelCache {
public:
    struct CacheConfig {
        size_t l1_size = 100;
        size_t l2_size = 1000;
        size_t l3_size = 10000;
        EvictionPolicy policy = EvictionPolicy::LRU;
        std::chrono::seconds ttl = std::chrono::seconds(3600);
    };
    
    explicit MultiLevelCache(const CacheConfig& config);
    
    // Основные операции
    std::optional<Value> Get(const Key& key);
    void Put(const Key& key, const Value& value);
    void Remove(const Key& key);
    void Clear();
    
    // Статистика
    struct CacheStats {
        size_t l1_hits, l1_misses;
        size_t l2_hits, l2_misses;
        size_t l3_hits, l3_misses;
        double hit_ratio() const;
        size_t total_requests() const;
    };
    
    CacheStats GetStats() const;
    void ResetStats();
    
    // Управление
    void SetEvictionPolicy(EvictionPolicy policy);
    void Resize(size_t l1_size, size_t l2_size, size_t l3_size);
    size_t GetMemoryUsage() const;
};
```

### Тесты
1. Базовые операции get/put
2. Переполнение L1 кэша
3. Политика LRU вытеснения
4. Политика LFU вытеснения
5. TTL истечение элементов
6. Статистика попаданий
7. Изменение размеров уровней
8. Очистка кэша
9. Большая нагрузка
10. Подсчет используемой памяти

---

## Задание 8: Оптимизированный парсер логов с использованием контейнеров-адаптеров

### Описание
Создайте систему для парсинга и анализа больших файлов логов. Используйте различные контейнеры для оптимальной обработки разных типов запросов.

### Требования
- Используйте `std::queue` для потоковой обработки
- `std::priority_queue` для обработки событий по важности
- `std::stack` для отслеживания вложенных операций
- Поддержите различные форматы логов
- Реализуйте фильтрацию и агрегацию в реальном времени

### Интерфейс
```cpp
enum class LogLevel { DEBUG, INFO, WARNING, ERROR, CRITICAL };

struct LogEntry {
    std::chrono::system_clock::time_point timestamp;
    LogLevel level;
    std::string source;
    std::string message;
    std::unordered_map<std::string, std::string> metadata;
};

class LogParser {
public:
    using LogFilter = std::function<bool(const LogEntry&)>;
    using LogProcessor = std::function<void(const LogEntry&)>;
    
    // Конфигурация парсера
    struct Config {
        std::string format_pattern = R"(\[(\d{4}-\d{2}-\d{2} \d{2}:\d{2}:\d{2})\] (\w+): (.+))";
        size_t buffer_size = 10000;
        size_t max_priority_queue_size = 1000;
        LogLevel min_level = LogLevel::INFO;
    };
    
    explicit LogParser(const Config& config = {});
    
    // Основные методы
    void ParseFile(const std::string& filename);
    void ParseStream(std::istream& stream);
    void AddFilter(const LogFilter& filter);
    void AddProcessor(const LogProcessor& processor);
    
    // Анализ и статистика
    std::vector<LogEntry> GetRecentErrors(size_t count = 10) const;
    std::map<LogLevel, size_t> GetLevelStatistics() const;
    std::vector<std::string> GetTopSources(size_t count = 5) const;
    std::chrono::system_clock::time_point GetLastEntryTime() const;
    
    // Real-time обработка
    void StartRealTimeProcessing(const std::string& filename);
    void StopRealTimeProcessing();
    bool IsProcessing() const;
};

class LogAnalyzer {
public:
    explicit LogAnalyzer(const LogParser& parser);
    
    // Поиск паттернов
    std::vector<LogEntry> FindPattern(const std::regex& pattern) const;
    std::vector<LogEntry> FindTimeRange(
        std::chrono::system_clock::time_point start,
        std::chrono::system_clock::time_point end) const;
    
    // Агрегация
    std::map<std::string, size_t> GetErrorFrequency() const;
    std::vector<LogEntry> GetAnomalies() const;
    double GetErrorRate() const;
};
```

### Тесты
1. Парсинг простого лог-файла
2. Фильтрация по уровню логирования
3. Обработка ошибок в реальном времени
4. Получение топ источников ошибок
5. Поиск по временному диапазону
6. Агрегация статистики
7. Обработка больших файлов
8. Поиск аномалий
9. Real-time мониторинг
10. Кастомные фильтры и процессоры

---

## Задание 9: Продвинутая система балансировки нагрузки с очередями

### Описание
Реализуйте систему балансировки нагрузки для веб-сервера, которая использует различные типы очередей для оптимального распределения запросов между серверами.

### Требования
- Используйте `std::queue` для FIFO обработки
- `std::priority_queue` для приоритетных запросов
- `std::deque` для гибкого управления очередью
- Реализуйте различные алгоритмы балансировки
- Добавьте мониторинг производительности серверов

### Интерфейс
```cpp
enum class BalancingAlgorithm {
    ROUND_ROBIN, LEAST_CONNECTIONS, WEIGHTED_ROUND_ROBIN,
    LEAST_RESPONSE_TIME, PRIORITY_BASED
};

struct Request {
    std::string id;
    std::chrono::steady_clock::time_point arrival_time;
    int priority = 0;
    size_t estimated_processing_time_ms = 100;
    std::string client_ip;
    std::unordered_map<std::string, std::string> headers;
};

struct Server {
    std::string id;
    std::string address;
    int weight = 1;
    size_t current_connections = 0;
    std::chrono::milliseconds avg_response_time{0};
    bool is_healthy = true;
    double cpu_usage = 0.0;
    double memory_usage = 0.0;
};

class LoadBalancer {
public:
    explicit LoadBalancer(BalancingAlgorithm algorithm = BalancingAlgorithm::ROUND_ROBIN);
    
    // Управление серверами
    void AddServer(const Server& server);
    void RemoveServer(const std::string& server_id);
    void UpdateServerStats(const std::string& server_id, 
                          std::chrono::milliseconds response_time,
                          double cpu_usage, double memory_usage);
    void MarkServerUnhealthy(const std::string& server_id);
    
    // Обработка запросов
    void EnqueueRequest(const Request& request);
    std::optional<std::pair<Request, std::string>> GetNextRequest();
    void CompleteRequest(const std::string& request_id, const std::string& server_id);
    
    // Конфигурация
    void SetBalancingAlgorithm(BalancingAlgorithm algorithm);
    void SetMaxQueueSize(size_t size);
    void EnablePriorityQueue(bool enable);
    
    // Статистика
    struct LoadBalancerStats {
        size_t total_requests = 0;
        size_t completed_requests = 0;
        size_t dropped_requests = 0;
        std::chrono::milliseconds avg_wait_time{0};
        std::map<std::string, size_t> requests_per_server;
        size_t current_queue_size = 0;
    };
    
    LoadBalancerStats GetStats() const;
    std::vector<Server> GetServers() const;
    size_t GetQueueSize() const;
};
```

### Тесты
1. Добавление и удаление серверов
2. Round-robin балансировка
3. Приоритетная обработка запросов
4. Обработка недоступного сервера
5. Взвешенная балансировка
6. Переполнение очереди
7. Статистика обработки
8. Динамическое изменение алгоритма
9. Мониторинг производительности
10. Обработка высокой нагрузки

---

## Задание 10: Система оптимизации алгоритмов с бенчмаркингом

### Описание
Создайте фреймворк для тестирования и сравнения производительности различных алгоритмов и контейнеров. Включите автоматическое профилирование и генерацию отчетов.

### Требования
- Тестирование различных контейнеров и алгоритмов
- Автоматическое генерирование тестовых данных
- Измерение времени, памяти, количества операций
- Сравнение рекурсивных и итеративных подходов
- Генерация подробных отчетов

### Интерфейс
```cpp
template<typename T>
struct BenchmarkResult {
    std::string algorithm_name;
    std::chrono::nanoseconds execution_time;
    size_t memory_usage;
    size_t operations_count;
    bool successful;
    std::string error_message;
    
    double operations_per_second() const;
    double memory_efficiency() const;
};

template<typename ContainerType>
class ContainerBenchmark {
public:
    using TestDataGenerator = std::function<std::vector<typename ContainerType::value_type>(size_t)>;
    using ContainerTest = std::function<void(ContainerType&)>;
    
    // Настройка тестов
    void AddTest(const std::string& name, const ContainerTest& test);
    void SetDataGenerator(const TestDataGenerator& generator);
    void SetTestSizes(const std::vector<size_t>& sizes);
    
    // Выполнение тестов
    std::vector<BenchmarkResult<typename ContainerType::value_type>> RunAllTests();
    BenchmarkResult<typename ContainerType::value_type> RunSingleTest(
        const std::string& test_name, size_t size);
    
    // Сравнение контейнеров
    template<typename OtherContainer>
    void CompareContainers(const std::string& test_name, size_t size);
    
    // Отчеты
    void GenerateReport(const std::string& filename) const;
    void PrintSummary() const;
};

class AlgorithmBenchmark {
public:
    // Тестирование сортировки
    template<typename T>
    void BenchmarkSortAlgorithms(const std::vector<T>& data);
    
    // Тестирование поиска
    template<typename T>
    void BenchmarkSearchAlgorithms(const std::vector<T>& data, const T& target);
    
    // Сравнение рекурсии vs итерации
    template<typename T>
    void CompareRecursiveVsIterative(const std::string& algorithm_name, 
                                   const std::vector<T>& data);
    
    // Профилирование памяти
    template<typename Function>
    size_t ProfileMemoryUsage(Function&& func);
    
    // Статистические тесты
    struct StatisticalResult {
        double mean;
        double std_deviation;
        double min_value;
        double max_value;
        size_t sample_size;
    };
    
    StatisticalResult RunStatisticalAnalysis(const std::string& test_name, 
                                           size_t iterations = 100);
};

// Предустановленные генераторы данных
class DataGenerators {
public:
    template<typename T>
    static std::vector<T> RandomData(size_t size);
    
    template<typename T>
    static std::vector<T> SortedData(size_t size);
    
    template<typename T>
    static std::vector<T> ReverseSortedData(size_t size);
    
    template<typename T>
    static std::vector<T> NearlySortedData(size_t size, double disorder_ratio = 0.1);
    
    static std::vector<std::string> RandomStrings(size_t count, size_t max_length = 20);
};
```

### Тесты
1. Сравнение vector vs deque vs list
2. Производительность различных алгоритмов сортировки
3. Рекурсивные vs итеративные алгоритмы
4. Профилирование использования памяти
5. Статистический анализ производительности
6. Сравнение поисковых алгоритмов
7. Тестирование на разных размерах данных
8. Генерация отчетов
9. Тестирование контейнеров-адаптеров
10. Сравнение параллельных и последовательных алгоритмов

---

## Критерии оценки

### Базовый уровень (60-70%)
- Корректная реализация основных операций с контейнерами
- Правильное использование stack, queue, deque
- Базовые алгоритмы поиска и сортировки
- Простая рекурсия

### Продвинутый уровень (70-85%)
- Эффективные алгоритмы и оптимизации
- Кастомные компараторы и функции
- Обработка ошибок и граничных случаев
- Статистика и профилирование
- Использование возможностей C++17

### Экспертный уровень (85-100%)
- Параллельные алгоритмы и многопоточность
- Гибридные подходы и автоматическая оптимизация
- Комплексная система с несколькими контейнерами
- Подробная документация и тестирование
- Инновационные решения и архитектурные паттерны 