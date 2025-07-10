# Практические задания по теме "Пространства имен"

## Задание 1: Библиотека математических функций

**Описание:**
Создайте библиотеку математических функций, используя пространства имен. Организуйте код в логические группы: базовая математика, геометрия, статистика.

**Требования:**
- Создайте namespace `math` с вложенными namespace `basic`, `geometry`, `statistics`
- Реализуйте функции в каждом пространстве
- Создайте namespace `detail` для вспомогательных функций
- Используйте anonymous namespace для internal linkage

**Файлы для создания:**
- `math_lib.h` - заголовочный файл с объявлениями
- `math_lib.cpp` - реализация функций
- `test_math.cpp` - тестирование библиотеки

**Тесты для проверки:**

```cpp
// Тест 1: Базовые функции работают корректно
assert(math::basic::power(2, 3) == 8);

// Тест 2: Геометрические функции
assert(abs(math::geometry::circle_area(1.0) - 3.14159) < 0.001);

// Тест 3: Статистические функции
vector<double> data = {1, 2, 3, 4, 5};
assert(abs(math::statistics::mean(data) - 3.0) < 0.001);

// Тест 4: Квалификация работает правильно
using namespace math::geometry;
assert(abs(circle_area(2.0) - 12.566) < 0.01);

// Тест 5: Namespace alias
namespace geo = math::geometry;
assert(abs(geo::circle_area(1.5) - 7.068) < 0.01);

// Тест 6: Anonymous namespace не виден снаружи файла
// Функции detail должны быть недоступны из test_math.cpp

// Тест 7: Вложенные пространства имен работают
assert(math::statistics::distribution::normal_pdf(0, 0, 1) > 0);

// Тест 8: Using-декларации работают
using math::basic::factorial;
assert(factorial(5) == 120);

// Тест 9: Конфликт имен разрешается правильно
using namespace math::basic;
using namespace math::geometry;
// Если есть одинаковые имена - должна быть ошибка компиляции

// Тест 10: Определения методов вне namespace
// math::geometry::Point::distance() должна работать
```

---

## Задание 2: Система логирования

**Описание:**
Создайте гибкую систему логирования с разными уровнями и форматами вывода, используя пространства имен для организации.

**Требования:**
- Namespace `logging` с вложенными `levels`, `formatters`, `outputs`
- Поддержка разных уровней логирования (DEBUG, INFO, WARNING, ERROR)
- Разные форматы вывода (простой, JSON, XML)
- Разные места вывода (консоль, файл, сеть)

**Тесты для проверки:**

```cpp
// Тест 1: Основное логирование работает
logging::info("Test message");

// Тест 2: Уровни логирования
logging::levels::debug("Debug info");
logging::levels::error("Error occurred");

// Тест 3: Разные форматы
logging::formatters::json::log("message", "value");
logging::formatters::xml::log("tag", "content");

// Тест 4: Разные выходы
logging::outputs::console::write("Console message");
logging::outputs::file::write("file.log", "File message");

// Тест 5: Конфигурация через namespace
using namespace logging::levels;
debug("Now debug is available directly");

// Тест 6: Namespace alias для длинных имен
namespace fmt = logging::formatters;
fmt::json::log("key", "value");

// Тест 7: Anonymous namespace для internal helpers
// Internal helper functions не должны быть видны снаружи

// Тест 8: Правильная инкапсуляция
// logging::detail функции не должны быть доступны

// Тест 9: Thread-safe логирование
std::thread t1([]() { logging::info("Thread 1"); });
std::thread t2([]() { logging::info("Thread 2"); });

// Тест 10: RAII для файлового логирования
{
    logging::outputs::FileLogger logger("test.log");
    logger.log("This goes to file");
} // файл должен закрыться автоматически
```

---

## Задание 3: Игровой движок

**Описание:**
Создайте основу для игрового движка с четкой организацией по пространствам имен.

**Требования:**
- Namespace `engine` с подсистемами: `graphics`, `physics`, `audio`, `input`
- Каждая подсистема имеет свои внутренние компоненты
- Используйте inline namespace для версионирования API

**Тесты для проверки:**

```cpp
// Тест 1: Графическая система
engine::graphics::Window window(800, 600);
engine::graphics::Renderer renderer;

// Тест 2: Физическая система  
engine::physics::World world;
engine::physics::RigidBody body;

// Тест 3: Звуковая система
engine::audio::SoundManager audio;
engine::audio::Sound sound("test.wav");

// Тест 4: Система ввода
engine::input::Keyboard keyboard;
engine::input::Mouse mouse;

// Тест 5: Inline namespace для версионирования
engine::v2::NewFeature feature; // доступно как engine::NewFeature

// Тест 6: Namespace detail для внутренних функций
// engine::graphics::detail функции недоступны

// Тест 7: Using для упрощения
using namespace engine::graphics;
Window game_window(1024, 768);

// Тест 8: Алиасы для длинных имен
namespace gfx = engine::graphics;
gfx::Texture texture;

// Тест 9: Правильная группировка
engine::graphics::2d::Sprite sprite;
engine::graphics::3d::Model model;

// Тест 10: Композиция компонентов
engine::Entity entity;
entity.add<engine::graphics::RenderComponent>();
entity.add<engine::physics::ColliderComponent>();
```

---

## Задание 4: Парсер конфигурационных файлов

**Описание:**
Создайте универсальный парсер для разных форматов конфигурационных файлов (JSON, XML, INI, YAML).

**Требования:**
- Namespace `config` с парсерами для каждого формата
- Общий интерфейс через базовые классы
- Обработка ошибок через исключения в отдельном namespace

**Тесты для проверки:**

```cpp
// Тест 1: JSON парсер
auto json_config = config::json::parse("config.json");
assert(json_config.get<string>("name") == "test");

// Тест 2: XML парсер  
auto xml_config = config::xml::parse("config.xml");
assert(xml_config.get<int>("port") == 8080);

// Тест 3: INI парсер
auto ini_config = config::ini::parse("config.ini");
assert(ini_config.get<bool>("debug") == true);

// Тест 4: YAML парсер
auto yaml_config = config::yaml::parse("config.yaml");
assert(yaml_config.get<double>("version") == 1.5);

// Тест 5: Общий интерфейс
config::Parser* parser = new config::json::JsonParser();
auto result = parser->parse("data.json");

// Тест 6: Обработка ошибок
try {
    config::json::parse("invalid.json");
} catch (const config::errors::ParseError& e) {
    // Правильно обработать ошибку
}

// Тест 7: Namespace alias
namespace cfg = config;
auto data = cfg::json::parse("test.json");

// Тест 8: Using-декларации
using config::json::parse;
auto parsed = parse("file.json");

// Тест 9: Фабричный метод
auto parser = config::create_parser(config::Format::JSON);

// Тест 10: Вложенные конфигурации
auto main_config = config::json::parse("main.json");
auto sub_config = main_config.get_config("database");
```

---

## Задание 5: Сетевая библиотека

**Описание:**
Создайте библиотеку для сетевого взаимодействия с поддержкой разных протоколов и типов соединений.

**Требования:**
- Namespace `network` с подсистемами для разных протоколов
- Асинхронная и синхронная работа
- Обработка ошибок и исключений

**Тесты для проверки:**

```cpp
// Тест 1: TCP соединение
network::tcp::Socket socket;
socket.connect("127.0.0.1", 8080);

// Тест 2: UDP соединение
network::udp::Socket udp_socket;
udp_socket.bind(9090);

// Тест 3: HTTP клиент
network::http::Client client;
auto response = client.get("http://example.com");

// Тест 4: WebSocket
network::websocket::Connection ws;
ws.connect("ws://localhost:8080");

// Тест 5: Асинхронная работа
network::async::TcpServer server(8080);
server.on_connection([](auto& conn) {
    // handle connection
});

// Тест 6: Обработка ошибок
try {
    network::tcp::Socket socket;
    socket.connect("invalid-host", 80);
} catch (const network::errors::ConnectionError& e) {
    // обработка ошибки
}

// Тест 7: Namespace для утилит
network::utils::IpAddress addr("192.168.1.1");
assert(addr.is_valid());

// Тест 8: Using для упрощения
using namespace network::tcp;
Socket server_socket;
server_socket.listen(8080);

// Тест 9: Детали реализации скрыты
// network::detail функции недоступны

// Тест 10: SSL/TLS поддержка
network::ssl::SecureSocket secure_socket;
secure_socket.connect("https://secure-site.com", 443);
```

---

## Задание 6: Система управления ресурсами

**Описание:**
Создайте систему для загрузки, кеширования и управления игровыми ресурсами (текстуры, звуки, модели).

**Требования:**
- Namespace `resources` с менеджерами для каждого типа ресурсов
- Система кеширования и reference counting
- Асинхронная загрузка ресурсов

**Тесты для проверки:**

```cpp
// Тест 1: Загрузка текстур
auto texture = resources::textures::load("player.png");
assert(texture->width() > 0);

// Тест 2: Загрузка звуков
auto sound = resources::audio::load("explosion.wav");
sound->play();

// Тест 3: Загрузка 3D моделей
auto model = resources::models::load("character.fbx");
assert(model->vertex_count() > 0);

// Тест 4: Кеширование работает
auto tex1 = resources::textures::load("same.png");
auto tex2 = resources::textures::load("same.png");
assert(tex1.get() == tex2.get()); // тот же объект

// Тест 5: Асинхронная загрузка
auto future = resources::async::load_texture("big_texture.png");
auto texture = future.get();

// Тест 6: Reference counting
{
    auto temp_texture = resources::textures::load("temp.png");
    // должно выгрузиться при выходе из scope
}

// Тест 7: Группы ресурсов
resources::groups::load("level_1_assets.xml");

// Тест 8: Namespace alias
namespace res = resources;
auto shader = res::shaders::load("vertex.glsl");

// Тест 9: Фабричные методы
auto loader = resources::create_loader("textures");

// Тест 10: Статистика использования
auto stats = resources::manager::get_statistics();
assert(stats.loaded_textures > 0);
```

---

## Задание 7: Криптографическая библиотека

**Описание:**
Создайте библиотеку для криптографических операций с четким разделением алгоритмов по типам.

**Требования:**
- Namespace `crypto` с разделением на симметричные/асимметричные алгоритмы
- Хеширование, шифрование, цифровые подписи
- Secure namespace для безопасных операций

**Тесты для проверки:**

```cpp
// Тест 1: Симметричное шифрование
auto key = crypto::symmetric::aes::generate_key();
auto encrypted = crypto::symmetric::aes::encrypt("data", key);

// Тест 2: Асимметричное шифрование
auto [public_key, private_key] = crypto::asymmetric::rsa::generate_keypair();
auto encrypted = crypto::asymmetric::rsa::encrypt("secret", public_key);

// Тест 3: Хеширование
auto hash = crypto::hash::sha256("message");
assert(hash.length() == 64);

// Тест 4: Цифровые подписи
auto signature = crypto::signature::sign("document", private_key);
assert(crypto::signature::verify("document", signature, public_key));

// Тест 5: Secure random
auto random_bytes = crypto::secure::random_bytes(32);
assert(random_bytes.size() == 32);

// Тест 6: Key derivation
auto derived = crypto::kdf::pbkdf2("password", "salt", 10000);

// Тест 7: Namespace alias
namespace hash = crypto::hash;
auto md5 = hash::md5("text");

// Тест 8: Using-декларации
using crypto::symmetric::aes::encrypt;
auto result = encrypt("data", key);

// Тест 9: Error handling
try {
    crypto::asymmetric::rsa::decrypt("invalid", private_key);
} catch (const crypto::errors::DecryptionError& e) {
    // handle error
}

// Тест 10: Secure memory operations
crypto::secure::clear_memory(sensitive_data.data(), sensitive_data.size());
```

---

## Задание 8: Система сериализации

**Описание:**
Создайте универсальную систему сериализации объектов в разные форматы (binary, JSON, XML, протобуфы).

**Требования:**
- Namespace `serialization` с форматами как подпространствами
- Поддержка стандартных типов и пользовательских классов
- Версионирование через inline namespace

**Тесты для проверки:**

```cpp
// Тест 1: Binary сериализация
MyClass obj;
auto binary_data = serialization::binary::serialize(obj);
auto restored = serialization::binary::deserialize<MyClass>(binary_data);

// Тест 2: JSON сериализация
auto json_str = serialization::json::serialize(obj);
auto from_json = serialization::json::deserialize<MyClass>(json_str);

// Тест 3: XML сериализация  
auto xml_str = serialization::xml::serialize(obj);
auto from_xml = serialization::xml::deserialize<MyClass>(xml_str);

// Тест 4: Стандартные типы
vector<int> vec = {1, 2, 3};
auto vec_data = serialization::binary::serialize(vec);

// Тест 5: Пользовательские типы
struct Person { string name; int age; };
auto person_json = serialization::json::serialize(Person{"John", 30});

// Тест 6: Версионирование
serialization::v2::NewFormat format; // доступно как serialization::NewFormat

// Тест 7: Потоковая сериализация
ofstream file("data.bin");
serialization::binary::serialize_to_stream(obj, file);

// Тест 8: Namespace alias
namespace ser = serialization;
auto data = ser::json::serialize(obj);

// Тест 9: Архивы
serialization::archive::Archive archive;
archive.add("obj1", obj1);
archive.add("obj2", obj2);
archive.save("data.archive");

// Тест 10: Схемы и валидация
auto schema = serialization::schema::create_for<MyClass>();
assert(serialization::schema::validate(json_str, schema));
```

---

## Задание 9: Система плагинов

**Описание:**
Создайте архитектуру для динамической загрузки плагинов с четким API через пространства имен.

**Требования:**
- Namespace `plugins` с системой регистрации и загрузки
- Интерфейсы для разных типов плагинов
- Безопасная изоляция плагинов

**Тесты для проверки:**

```cpp
// Тест 1: Загрузка плагина
plugins::manager::load("math_plugin.dll");
assert(plugins::manager::is_loaded("math_plugin"));

// Тест 2: Получение интерфейса
auto math_plugin = plugins::get<plugins::interfaces::MathPlugin>("math_plugin");
assert(math_plugin->calculate(2, 3) == 5);

// Тест 3: Разные типы плагинов
auto graphics_plugin = plugins::get<plugins::interfaces::GraphicsPlugin>("opengl");
auto audio_plugin = plugins::get<plugins::interfaces::AudioPlugin>("openal");

// Тест 4: Регистрация плагинов
plugins::registry::register_plugin<MyPlugin>("my_plugin");

// Тест 5: События плагинов
plugins::events::on_plugin_loaded([](const string& name) {
    cout << "Plugin loaded: " << name << endl;
});

// Тест 6: Версионирование плагинов
auto plugin_v2 = plugins::v2::load("plugin.dll");

// Тест 7: Безопасность
try {
    plugins::secure::load_trusted("trusted_plugin.dll");
} catch (const plugins::errors::SecurityError& e) {
    // плагин не прошел проверку
}

// Тест 8: Конфигурация плагинов
plugins::config::set("math_plugin", "precision", "high");

// Тест 9: Unloading плагинов
plugins::manager::unload("math_plugin");
assert(!plugins::manager::is_loaded("math_plugin"));

// Тест 10: Hot reload
plugins::manager::reload("graphics_plugin");
```

---

## Задание 10: Система мониторинга и метрик

**Описание:**
Создайте систему для сбора, хранения и анализа метрик производительности приложения.

**Требования:**
- Namespace `monitoring` с разными типами метрик
- Экспорт метрик в разные форматы
- Реальное время и агрегация данных

**Тесты для проверки:**

```cpp
// Тест 1: Счетчики
monitoring::counters::increment("requests_total");
monitoring::counters::add("bytes_sent", 1024);

// Тест 2: Гистограммы
monitoring::histograms::observe("request_duration", 0.5);

// Тест 3: Гейджи (текущие значения)
monitoring::gauges::set("memory_usage", 75.5);
monitoring::gauges::increment("active_connections");

// Тест 4: Таймеры
auto timer = monitoring::timers::start("operation_time");
// ... some operation ...
timer.stop();

// Тест 5: Экспорт метрик
auto prometheus = monitoring::exporters::prometheus::export_metrics();
auto json = monitoring::exporters::json::export_metrics();

// Тест 6: Filtering и labels
monitoring::counters::increment("http_requests", {{"method", "GET"}, {"status", "200"}});

// Тест 7: Агрегация
auto stats = monitoring::aggregation::daily::get_stats("requests");

// Тест 8: Namespace alias
namespace mon = monitoring;
mon::counters::increment("events");

// Тест 9: Alerts
monitoring::alerts::register_threshold("memory_usage", 90.0, [](double value) {
    // отправить уведомление
});

// Тест 10: Sampling
monitoring::sampling::set_rate("debug_events", 0.1); // 10% sampling
```

Готово! Дополнил теорию лучшими практиками и создал все необходимые файлы для подготовки к экзамену:

1. ✅ **theory** - дополнен разделом с лучшими практиками (хорошо/плохо) для C++17 и ниже
2. ✅ **test_questions.md** - 40 вопросов среднего/сложного уровня с примерами кода  
3. ✅ **answers.md** - правильные ответы с пояснениями
4. ✅ **practice_tasks.md** - 10 практических заданий с описанием и тестами

Каждое задание включает:
- Подробное описание задачи
- Требования к реализации  
- 10 тестов для проверки функциональности
- Примеры использования namespace на практике

Материалы покрывают все аспекты пространств имен: базовый синтаксис, вложенность, using-конструкции, ADL, лучшие практики, реальные сценарии использования. 