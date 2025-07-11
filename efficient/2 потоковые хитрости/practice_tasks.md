# Практические задания: Потоковые хитрости и оптимизация I/O

## Задание 1: Оптимизация буферизации
**Описание:** Напишите программу, которая читает текстовый файл и подсчитывает количество слов. Реализуйте две версии - медленную (с побайтовым чтением) и быструю (с буферизованным чтением). Сравните производительность.

**Требования:**
- Версия 1: использовать `file.get()` для чтения каждого символа
- Версия 2: использовать `file.read()` с буфером 8192 байта
- Замерить время выполнения обеих версий
- Протестировать на файле размером минимум 1 МБ

**Тесты:**
1. Файл из 1 миллиона слов "word" - результат: 1000000
2. Файл из слов разной длины - подсчет должен быть точным
3. Файл с множественными пробелами - не считать лишние разделители
4. Пустой файл - результат: 0
5. Файл только из пробелов - результат: 0
6. Файл с одним словом - результат: 1
7. Файл с переводами строк - правильный подсчет
8. Файл с табуляциями - правильный подсчет
9. Бинарный файл (должен корректно обрабатываться)
10. Очень большой файл (>10 МБ) - проверка производительности

## Задание 2: Система логирования с буферизацией
**Описание:** Создайте класс Logger с настраиваемой буферизацией. Логгер должен накапливать сообщения в памяти и сбрасывать их в файл при достижении определенного размера буфера или по истечении времени.

**Требования:**
- Класс Logger с методами log(), flush(), setBufferSize()
- Автоматический сброс при заполнении буфера
- Принудительный сброс в деструкторе
- Потокобезопасность не требуется
- Настраиваемый формат timestamp

**Тесты:**
1. Логирование 100 сообщений с размером буфера 50 - 2 сброса
2. Принудительный flush() - немедленная запись в файл
3. Деструктор сбрасывает незаписанные данные
4. Очень длинные сообщения (больше размера буфера)
5. Пустые сообщения - не должны записываться
6. Специальные символы в сообщениях
7. Unicode символы в сообщениях
8. Быстрое логирование (1000+ сообщений/сек)
9. Изменение размера буфера во время работы
10. Повторное использование логгера после flush()

## Задание 3: Оптимизированный парсер CSV
**Описание:** Напишите быстрый парсер CSV-файлов с настраиваемыми разделителями. Парсер должен эффективно обрабатывать большие файлы (>100 МБ) и поддерживать escape-последовательности.

**Требования:**
- Класс CSVParser с методом parseFile()
- Поддержка кавычек и escape-символов
- Возврат vector<vector<string>> с данными
- Обработка ошибок формата
- Настраиваемый разделитель (по умолчанию ',')

**Тесты:**
1. Простой CSV: "a,b,c\n1,2,3" - правильный разбор
2. Кавычки: "\"hello, world\",test" - одно поле с запятой
3. Escape-символы: "field1,\"quote: \\\"text\\\"\",field3"
4. Пустые поля: "a,,c" - средний элемент пустой
5. Переводы строк в кавычках: "\"line1\nline2\",field2"
6. Другой разделитель (';'): "a;b;c"
7. Только заголовки без данных
8. Большой файл (>1000 строк, >100 полей в строке)
9. Некорректный формат - обработка ошибок
10. Unicode содержимое в полях

## Задание 4: Система кэширования файлов
**Описание:** Реализуйте класс FileCache, который кэширует содержимое файлов в памяти и предоставляет быстрый доступ к данным. Кэш должен иметь ограничение по размеру и использовать LRU-политику вытеснения.

**Требования:**
- Класс FileCache с методами readFile(), setMaxSize()
- LRU-вытеснение при превышении лимита
- Автоматическое обновление при изменении файла
- Поддержка как текстовых, так и бинарных файлов

**Тесты:**
1. Чтение файла первый раз - загрузка в кэш
2. Повторное чтение - возврат из кэша (быстрее)
3. Превышение лимита размера - вытеснение LRU
4. Изменение файла - автоматическое обновление кэша
5. Несуществующий файл - корректная обработка ошибки
6. Множественные файлы в кэше одновременно
7. Очень большой файл (больше лимита кэша)
8. Бинарные файлы с нулевыми байтами
9. Файлы с правами только на чтение
10. Одновременное кэширование текстовых и бинарных файлов

## Задание 5: Продвинутый file копировщик
**Описание:** Создайте утилиту для копирования файлов с прогресс-баром, проверкой целостности и возможностью докачки. Утилита должна быть максимально быстрой и надежной.

**Требования:**
- Копирование с проверкой MD5/SHA256
- Прогресс-бар в консоли
- Возможность продолжить прерванное копирование
- Оптимальный размер буфера для разных типов носителей
- Обработка всех возможных ошибок

**Тесты:**
1. Копирование маленького файла (1 КБ) - успешно
2. Копирование большого файла (>1 ГБ) - с прогресс-баром
3. Прерывание копирования и докачка - корректное восстановление
4. Копирование на заполненный диск - обработка ошибки
5. Копирование файла без прав на чтение - ошибка доступа
6. Целевая папка не существует - создание или ошибка
7. Копирование поверх существующего файла - перезапись или пропуск
8. Проверка целостности скопированного файла
9. Копирование бинарного файла с нулевыми байтами
10. Копирование файла с Unicode именем

## Задание 6: Анализатор производительности I/O
**Описание:** Напишите программу-бенчмарк для тестирования производительности различных методов ввода-вывода. Программа должна тестировать разные размеры буферов, методы чтения/записи и выдавать рекомендации по оптимизации.

**Требования:**
- Тестирование get() vs read() с разными размерами буферов
- Измерение влияния endl vs \n
- Тестирование с sync_with_stdio и без
- Автоматические рекомендации по оптимизации
- Графики производительности (ASCII-арт)

**Тесты:**
1. Чтение файла размером 1 МБ разными методами
2. Запись 100000 строк с endl и с \n
3. Тестирование буферов от 1 байта до 1 МБ
4. Влияние cin.tie(nullptr) на производительность
5. Сравнение ifstream и fopen/fread
6. Тестирование на SSD vs HDD (если доступно)
7. Влияние размера файла на оптимальный размер буфера
8. Тестирование с включенной/отключенной синхронизацией
9. Измерение накладных расходов на различные операции
10. Создание отчета с рекомендациями

## Задание 7: Система мониторинга файловой системы
**Описание:** Используя std::filesystem, создайте программу для мониторинга изменений в директории. Программа должна отслеживать создание, изменение и удаление файлов, выводя статистику в реальном времени.

**Требования:**
- Рекурсивный мониторинг поддиректорий  
- Вывод статистики: размер файлов, количество, типы
- Фильтрация по расширениям файлов
- Детектирование дубликатов файлов (по содержимому)
- Экспорт отчетов в CSV/JSON

**Тесты:**
1. Создание нового файла - детектирование и учет
2. Изменение существующего файла - обновление статистики
3. Удаление файла - корректное удаление из статистики
4. Создание и удаление поддиректории
5. Массовое создание файлов (>1000 файлов)
6. Фильтрация по расширению (.txt, .cpp, etc.)
7. Поиск дубликатов - файлы с одинаковым содержимым
8. Обработка символических ссылок
9. Работа с файлами без прав доступа
10. Мониторинг очень большой директории (>10000 файлов)

## Задание 8: Система архивации с компрессией
**Описание:** Создайте простую систему архивации файлов с базовой компрессией. Архиватор должен упаковывать несколько файлов в один архив с возможностью их извлечения.

**Требования:**
- Собственный формат архива с заголовками
- Простая компрессия (RLE или LZ77)
- Поддержка директорий и поддиректорий
- Проверка целостности архива
- Возможность добавления файлов в существующий архив

**Тесты:**
1. Архивирование одного файла - создание и извлечение
2. Архивирование директории с файлами
3. Архивирование пустой директории
4. Файлы с одинаковыми именами в разных папках
5. Очень большие файлы (>100 МБ)
6. Множество маленьких файлов
7. Бинарные файлы и изображения
8. Файлы с Unicode именами
9. Поврежденный архив - обработка ошибок
10. Добавление файлов в существующий архив

## Задание 9: Парсер логов с паттерн-матчингом
**Описание:** Используя regex и raw literals, создайте анализатор лог-файлов веб-сервера. Программа должна парсить различные форматы логов и выдавать статистику по IP, URL, кодам ответов и т.д.

**Требования:**
- Поддержка Apache Common Log Format и NGINX
- Использование raw literals для regex
- Статистика: топ IP, топ URL, коды ошибок
- Временные диапазоны и фильтрация
- Экспорт результатов в разных форматах

**Тесты:**
1. Парсинг строки Apache формата - извлечение всех полей
2. Парсинг NGINX формата с дополнительными полями
3. Некорректная строка лога - пропуск или ошибка
4. Большой лог-файл (>1 млн строк)
5. Фильтрация по временному диапазону
6. Поиск конкретных IP адресов
7. Статистика по кодам HTTP ответов
8. Самые популярные URL-ы
9. Детектирование подозрительной активности
10. Обработка сжатых лог-файлов (.gz)

## Задание 10: Система синхронизации файлов
**Описание:** Создайте программу для синхронизации содержимого двух директорий. Программа должна определять различия между директориями и предлагать действия для синхронизации.

**Требования:**
- Сравнение файлов по содержимому и времени изменения
- Обработка конфликтов (файл изменен в обеих директориях)
- Поддержка исключений файлов/папок
- Dry-run режим (показать действия без выполнения)
- Двунаправленная синхронизация

**Тесты:**
1. Новый файл в source - копирование в target
2. Удаленный файл из source - удаление из target
3. Измененный файл - обновление в target
4. Конфликт - файл изменен в обеих директориях
5. Исключение файлов по маске (*.tmp, *.log)
6. Синхронизация поддиректорий
7. Файлы с одинаковыми именами но разным содержимым
8. Dry-run режим - только показ действий
9. Большое количество файлов (>10000)
10. Файлы с правами только на чтение 