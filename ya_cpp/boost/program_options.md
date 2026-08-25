# Boost.Program_options

Источник: https://www.boost.org/doc/libs/1_63_0/doc/html/program_options.html

## Суть

`Boost.Program_options` помогает описывать и читать параметры программы:

- из командной строки;
- из конфиг-файлов;
- из переменных окружения;
- с автоматическим `--help`;
- с приведением значений к нужным C++-типам.

Вместо ручного разбора `argv` ты описываешь допустимые опции, парсишь вход и читаешь результат из `variables_map`.

## Минимальный пример

```cpp
#include <boost/program_options.hpp>
#include <iostream>

namespace po = boost::program_options;

int main(int argc, char* argv[]) {
    po::options_description desc("Allowed options");

    desc.add_options()
        ("help,h", "show help")
        ("compression,c", po::value<int>(), "compression level");

    po::variables_map vm;
    po::store(po::parse_command_line(argc, argv, desc), vm);
    po::notify(vm);

    if (vm.count("help")) {
        std::cout << desc << '\n';
        return 0;
    }

    if (vm.count("compression")) {
        std::cout << "compression = "
                  << vm["compression"].as<int>() << '\n';
    }
}
```

Запуск:

```bash
./app --help
./app --compression 5
./app -c 5
```

## Значения по умолчанию

```cpp
int threads = 4;

po::options_description desc("Options");
desc.add_options()
    ("threads,t", po::value<int>(&threads)->default_value(4), "thread count");

// после po::notify(vm) переменная threads уже заполнена
```

Если пользователь не передал `--threads`, будет `4`.

## Несколько значений

```cpp
desc.add_options()
    ("include,I", po::value<std::vector<std::string>>(), "include path");

if (vm.count("include")) {
    auto paths = vm["include"].as<std::vector<std::string>>();
}
```

Запуск:

```bash
./compiler -I src -I include -I third_party
```

## Позиционные аргументы

Чтобы `./compiler main.cpp lib.cpp` читалось как список файлов:

```cpp
desc.add_options()
    ("input-file", po::value<std::vector<std::string>>(), "input files");

po::positional_options_description pos;
pos.add("input-file", -1); // все позиционные аргументы

po::variables_map vm;
po::store(
    po::command_line_parser(argc, argv)
        .options(desc)
        .positional(pos)
        .run(),
    vm
);
po::notify(vm);
```

## Конфиг-файл

```cpp
#include <fstream>

po::options_description config("Config");
config.add_options()
    ("optimization", po::value<int>()->default_value(2), "optimization level")
    ("include", po::value<std::vector<std::string>>()->composing(), "include path");

po::variables_map vm;

po::store(po::parse_command_line(argc, argv, config), vm);

std::ifstream file("app.cfg");
if (file) {
    po::store(po::parse_config_file(file, config), vm);
}

po::notify(vm);
```

Пример `app.cfg`:

```ini
optimization = 3
include = src
include = include
```

`composing()` нужен, чтобы значения из разных источников не заменялись, а складывались.

## Переменные окружения

`parse_environment()` читает переменные окружения и сопоставляет их с именами опций через функцию-маппер.

```cpp
po::options_description desc("Options");
desc.add_options()
    ("host", po::value<std::string>()->default_value("localhost"), "server host")
    ("port", po::value<int>()->default_value(8080), "server port");

auto mapper = [](const std::string& env) -> std::string {
    if (env == "APP_HOST") {
        return "host";
    }
    if (env == "APP_PORT") {
        return "port";
    }
    return "";
};

po::variables_map vm;
po::store(po::parse_environment(desc, mapper), vm);
po::notify(vm);

std::string host = vm["host"].as<std::string>();
int port = vm["port"].as<int>();
```

Запуск:

```bash
APP_HOST=127.0.0.1 APP_PORT=9000 ./app
```

## Типичный шаблон

```cpp
try {
    po::options_description desc("Options");
    desc.add_options()
        ("help,h", "show help")
        ("port,p", po::value<int>()->default_value(8080), "server port");

    po::variables_map vm;
    po::store(po::parse_command_line(argc, argv, desc), vm);
    po::notify(vm);

    if (vm.count("help")) {
        std::cout << desc << '\n';
        return 0;
    }

    int port = vm["port"].as<int>();
} catch (const po::error& e) {
    std::cerr << "options error: " << e.what() << '\n';
    return 1;
}
```

## Сборка

`program_options` обычно требует линковки с библиотекой:

```bash
g++ main.cpp -lboost_program_options -o app
```

## Коротко

- `options_description` - описание допустимых опций.
- `add_options()` - добавление опций.
- `parse_command_line()` - парсинг `argc/argv`.
- `command_line_parser()` - расширенный парсер: позиционные аргументы, неизвестные опции и т.д.
- `variables_map` - хранилище результатов.
- `store()` - положить распарсенные значения в `variables_map`.
- `notify()` - применить значения, проверить ошибки, заполнить связанные переменные.
- `as<T>()` - получить значение нужного типа.
