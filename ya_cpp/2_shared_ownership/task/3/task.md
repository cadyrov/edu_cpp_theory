Вы разработали отличную систему, которая динамически обновляет параметры конфигурации приложения, но оказалось, что она работает медленнее, чем нужно. 

Анализ производительности программы показал, что ваша система слишком часто вызывает копирующие операции. Попытайтесь оптимизировать класс, чтобы он работал быстрее.
- Скопируйте код ниже к себе и выполните задания:
- Проанализируйте класс ConfigManager и найдите три фрагмента в коде, где объекты используются в последний раз.
- С помощью std::move переместите состояния объектов, которые они имеют в момент последнего использования.

```cpp
class ConfigData {
public:
    ConfigData(uint32_t logLevel) : logLevel_(logLevel) {}

    uint32_t logLevel() const { return logLevel_; }

private:
    uint32_t logLevel_;
};

class Config {
public:
    Config(const std::atomic<std::shared_ptr<const ConfigData>> &configData) : configData_{configData} {}

    uint32_t logLevel() const { return configData_.load()->logLevel(); }

private:
    const std::atomic<std::shared_ptr<const ConfigData>> configData_;
};

class ConfigManager {
public:
    ConfigManager(std::string_view configPath, std::chrono::milliseconds reloadInterval)
        : configPath_{configPath}, reloadInterval_{reloadInterval} {

        currentConfigRaw_ = Read();
        auto [configData, _] = Parse(currentConfigRaw_);

        configData_ = std::make_shared<const ConfigData>(configData);

        isActive_ = true;
        mainRoutine_ = std::jthread([&] { MainRoutine(); });
    }

    ~ConfigManager() { isActive_ = false; }

    // Запрещаем копирование и перемещение
    ConfigManager(const ConfigManager &) = delete;
    ConfigManager &operator=(const ConfigManager &) = delete;
    ConfigManager(ConfigManager &&) = delete;
    ConfigManager &operator=(ConfigManager &&) = delete;

    Config get() const { return Config{configData_}; }

private:
    void MainRoutine() {
        while (isActive_) {
            auto newConfigRaw = Read();
            if (newConfigRaw != currentConfigRaw_) {
                currentConfigRaw_ = newConfigRaw;

                auto [configData, err] = Parse(currentConfigRaw_);
                if (err != std::errc()) {
                    std::println(std::cerr, "\n\t> Error: failed to update configuration due to file parsing error");
                    continue;
                }
                std::println("\n\t> Configuration will be Updated");

                configData_ = std::make_shared<const ConfigData>(configData);
            }
            std::this_thread::sleep_for(reloadInterval_);
        }
    }

    std::string Read() const {
        auto file = std::ifstream{configPath_};
        return !file.is_open() ? ""
                               : std::string{std::istreambuf_iterator<std::string::value_type>(file),
                                             std::istreambuf_iterator<std::string::value_type>()};
    }

    std::tuple<ConfigData, std::errc> Parse(std::string_view str) const {
        uint32_t value = 0;
        auto [ptr, ec] = std::from_chars(str.data(), str.data() + str.size(), value);

        if (ec != std::errc()) {
            std::println(std::cerr, "\tConversion from str '{}' to uint32_t failed", str);
        }
        return std::make_tuple(ConfigData{value}, ec);
    }

private:
    const std::string configPath_;
    const std::chrono::milliseconds reloadInterval_;

    std::atomic<std::shared_ptr<const ConfigData>> configData_;
    std::string currentConfigRaw_;

    std::atomic_bool isActive_ = true;
    std::jthread mainRoutine_;
};
```

- Проанализируйте данные, которые возвращают функции Read() и Parse().
- Вспомните, как работает RVO-оптимизация компилятора.


## Чтобы протестировать эту программу:

- Создайте файл config.txt.
- Запишите в этот файл любое число.
- Запустите программу.
- После запуска программы (пока она ещё работает), измените число в файле и сохраните его.
- Вот как может выглядеть результат работы программы:
```
logLevel: 4
    > Configuration will be Updated
logLevel: 2 
```