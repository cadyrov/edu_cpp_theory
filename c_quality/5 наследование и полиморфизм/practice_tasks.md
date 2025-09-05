# Практические задания: Наследование и полиморфизм в C++

## Задание 1: Система управления фигурами

### Описание:
Создайте иерархию классов для представления геометрических фигур. Реализуйте базовый абстрактный класс `Shape` и производные классы `Circle`, `Rectangle`, `Triangle`.

### Требования:
- Базовый класс должен содержать чисто виртуальные методы для вычисления площади и периметра
- Добавьте виртуальный метод `Draw()` 
- Реализуйте все производные классы
- Добавьте поддержку цвета и координат

### Тесты:
```cpp
// Test 1: Создание фигур
Circle c(5.0);
Rectangle r(4.0, 6.0);
Triangle t(3.0, 4.0, 5.0);

// Test 2: Вычисление площади
assert(abs(c.GetArea() - 78.54) < 0.01);
assert(r.GetArea() == 24.0);
assert(abs(t.GetArea() - 6.0) < 0.01);

// Test 3: Полиморфизм
vector<unique_ptr<Shape>> shapes;
shapes.push_back(make_unique<Circle>(3.0));
shapes.push_back(make_unique<Rectangle>(2.0, 4.0));

// Test 4: Виртуальные методы
for(auto& shape : shapes) {
    shape->Draw();
}

// Test 5: Цвета
c.SetColor("red");
assert(c.GetColor() == "red");

// Test 6: Координаты
c.SetPosition(10.0, 20.0);
auto [x, y] = c.GetPosition();
assert(x == 10.0 && y == 20.0);

// Test 7: Периметр окружности
assert(abs(c.GetPerimeter() - 31.42) < 0.01);

// Test 8: Периметр прямоугольника  
assert(r.GetPerimeter() == 20.0);

// Test 9: Копирование
Circle c2 = c;
assert(c2.GetRadius() == c.GetRadius());

// Test 10: Приведение типов
Shape* shape = &c;
Circle* circle = dynamic_cast<Circle*>(shape);
assert(circle != nullptr);
```

---

## Задание 2: Система сотрудников компании

### Описание:
Разработайте иерархию классов для представления сотрудников компании: `Employee` (базовый), `Manager`, `Developer`, `Designer`.

### Требования:
- Базовый класс содержит имя, ID, базовую зарплату
- Каждый тип сотрудника имеет свой способ расчета зарплаты
- Менеджер получает бонус за количество подчиненных
- Разработчик получает бонус за знание языков программирования
- Дизайнер получает бонус за проекты в портфолио

### Тесты:
```cpp
// Test 1: Создание сотрудников
Manager m("John", 1, 5000);
Developer d("Alice", 2, 4000);
Designer des("Bob", 3, 3500);

// Test 2: Базовая зарплата
assert(m.GetBaseSalary() == 5000);
assert(d.GetBaseSalary() == 4000);

// Test 3: Добавление подчиненных менеджеру
m.AddSubordinate(make_unique<Developer>("Dev1", 4, 3000));
m.AddSubordinate(make_unique<Designer>("Des1", 5, 2800));

// Test 4: Расчет зарплаты менеджера с бонусом
assert(m.CalculateSalary() == 5000 + 2 * 500); // бонус 500 за подчиненного

// Test 5: Добавление языков программирования
d.AddProgrammingLanguage("C++");
d.AddProgrammingLanguage("Python");
d.AddProgrammingLanguage("JavaScript");

// Test 6: Расчет зарплаты разработчика
assert(d.CalculateSalary() == 4000 + 3 * 300); // бонус 300 за язык

// Test 7: Добавление проектов в портфолио
des.AddPortfolioProject("Website Design");
des.AddPortfolioProject("Mobile App UI");

// Test 8: Расчет зарплаты дизайнера
assert(des.CalculateSalary() == 3500 + 2 * 200); // бонус 200 за проект

// Test 9: Полиморфное вычисление зарплат
vector<unique_ptr<Employee>> employees;
employees.push_back(make_unique<Manager>("M1", 6, 6000));
employees.push_back(make_unique<Developer>("D1", 7, 4500));

double totalSalary = 0;
for(auto& emp : employees) {
    totalSalary += emp->CalculateSalary();
}

// Test 10: Информация о сотруднике
assert(m.GetName() == "John");
assert(m.GetId() == 1);
```

---

## Задание 3: Медиаплеер с поддержкой разных форматов

### Описание:
Создайте систему медиаплеера, который может воспроизводить файлы разных форматов: MP3, WAV, FLAC.

### Требования:
- Базовый класс `MediaFile` с виртуальными методами
- Производные классы для каждого формата
- Разные алгоритмы декодирования и качества
- Поддержка метаданных (название, исполнитель, длительность)

### Тесты:
```cpp
// Test 1: Создание файлов
MP3File mp3("song.mp3", "Artist", "Title", 180);
WAVFile wav("song.wav", "Artist", "Title", 180);
FLACFile flac("song.flac", "Artist", "Title", 180);

// Test 2: Метаданные
assert(mp3.GetTitle() == "Title");
assert(mp3.GetArtist() == "Artist");
assert(mp3.GetDuration() == 180);

// Test 3: Размер файла (разные алгоритмы сжатия)
assert(mp3.GetFileSize() < wav.GetFileSize());
assert(flac.GetFileSize() < wav.GetFileSize());
assert(flac.GetFileSize() > mp3.GetFileSize());

// Test 4: Качество звука
assert(wav.GetQuality() == AudioQuality::Lossless);
assert(flac.GetQuality() == AudioQuality::Lossless);
assert(mp3.GetQuality() == AudioQuality::Lossy);

// Test 5: Воспроизведение
mp3.Play();
wav.Play();
flac.Play();

// Test 6: Пауза и остановка
mp3.Pause();
assert(mp3.GetState() == PlaybackState::Paused);
mp3.Stop();
assert(mp3.GetState() == PlaybackState::Stopped);

// Test 7: Полиморфная коллекция
vector<unique_ptr<MediaFile>> playlist;
playlist.push_back(make_unique<MP3File>("1.mp3", "A1", "T1", 120));
playlist.push_back(make_unique<WAVFile>("2.wav", "A2", "T2", 200));

// Test 8: Общая длительность плейлиста
int totalDuration = 0;
for(auto& file : playlist) {
    totalDuration += file->GetDuration();
}
assert(totalDuration == 320);

// Test 9: Поиск по исполнителю
auto found = find_if(playlist.begin(), playlist.end(),
    [](const auto& file) { return file->GetArtist() == "A1"; });
assert(found != playlist.end());

// Test 10: Битрейт (специфично для форматов)
MP3File* mp3Ptr = dynamic_cast<MP3File*>(playlist[0].get());
assert(mp3Ptr != nullptr);
assert(mp3Ptr->GetBitrate() == 320); // kbps
```

---

## Задание 4: Система уведомлений

### Описание:
Реализуйте систему уведомлений, которая может отправлять сообщения через разные каналы: Email, SMS, Push-уведомления.

### Требования:
- Абстрактный класс `NotificationSender`
- Производные классы для каждого типа уведомлений
- Разные способы форматирования сообщений
- Обработка ошибок отправки

### Тесты:
```cpp
// Test 1: Создание отправителей
EmailSender email("smtp.gmail.com", 587);
SMSSender sms("api.sms.com", "api_key_123");
PushSender push("firebase.com", "app_token");

// Test 2: Отправка уведомлений
assert(email.Send("user@example.com", "Subject", "Message"));
assert(sms.Send("+1234567890", "", "SMS Message"));
assert(push.Send("device_token", "Title", "Push message"));

// Test 3: Форматирование сообщений
string emailMsg = email.FormatMessage("Subject", "Body text");
assert(emailMsg.find("Subject:") != string::npos);

string smsMsg = sms.FormatMessage("", "Short message");
assert(smsMsg.length() <= 160); // SMS limit

// Test 4: Проверка доставки
assert(email.GetDeliveryStatus() == DeliveryStatus::Delivered);

// Test 5: Обработка ошибок
SMSSender invalidSms("", "");
assert(!invalidSms.Send("+1234567890", "", "Test"));
assert(invalidSms.GetLastError() == "Invalid API configuration");

// Test 6: Полиморфная отправка
vector<unique_ptr<NotificationSender>> senders;
senders.push_back(make_unique<EmailSender>("host", 25));
senders.push_back(make_unique<SMSSender>("api", "key"));

Notification notification{"receiver", "title", "message"};
for(auto& sender : senders) {
    sender->Send(notification.receiver, notification.title, notification.message);
}

// Test 7: Статистика отправки
assert(email.GetSentCount() > 0);
assert(email.GetFailedCount() == 0);

// Test 8: Максимальная длина сообщения
assert(email.GetMaxMessageLength() > sms.GetMaxMessageLength());

// Test 9: Настройки отправителя
email.SetTimeout(30);
assert(email.GetTimeout() == 30);

// Test 10: Валидация получателей
assert(email.ValidateRecipient("test@example.com"));
assert(!email.ValidateRecipient("invalid-email"));
assert(sms.ValidateRecipient("+1234567890"));
assert(!sms.ValidateRecipient("invalid-phone"));
```

---

## Задание 5: Игровые персонажи с системой навыков

### Описание:
Создайте иерархию игровых персонажей: `Character` (базовый), `Warrior`, `Mage`, `Archer`. Каждый класс имеет уникальные способности и систему прокачки.

### Требования:
- Базовые характеристики: здоровье, мана, уровень
- Виртуальные методы для атаки и использования способностей
- Система прокачки навыков
- Инвентарь и экипировка

### Тесты:
```cpp
// Test 1: Создание персонажей
Warrior warrior("Conan", 1);
Mage mage("Gandalf", 1);
Archer archer("Legolas", 1);

// Test 2: Базовые характеристики
assert(warrior.GetHealth() == 120);
assert(warrior.GetMana() == 30);
assert(mage.GetHealth() == 80);
assert(mage.GetMana() == 100);

// Test 3: Атака
int damage = warrior.Attack();
assert(damage >= 15 && damage <= 25); // случайный урон в диапазоне

// Test 4: Способности
mage.CastSpell("Fireball");
assert(mage.GetMana() < 100); // потратил ману

warrior.UseSpecialAbility("Charge");
archer.UseSpecialAbility("MultiShot");

// Test 5: Получение урона
int initialHealth = archer.GetHealth();
archer.TakeDamage(20);
assert(archer.GetHealth() == initialHealth - 20);

// Test 6: Повышение уровня
warrior.GainExperience(1000);
assert(warrior.GetLevel() == 2);
assert(warrior.GetHealth() > 120); // здоровье увеличилось

// Test 7: Изучение навыков
mage.LearnSkill("Lightning Bolt");
assert(mage.HasSkill("Lightning Bolt"));

// Test 8: Экипировка
Weapon sword("Iron Sword", 10);
warrior.EquipWeapon(sword);
assert(warrior.GetWeaponDamage() == 10);

// Test 9: Смерть и воскрешение
archer.TakeDamage(1000);
assert(!archer.IsAlive());
archer.Resurrect();
assert(archer.IsAlive());

// Test 10: Бой между персонажами
while(warrior.IsAlive() && mage.IsAlive()) {
    int warriorDamage = warrior.Attack();
    mage.TakeDamage(warriorDamage);
    
    if(mage.IsAlive()) {
        int mageDamage = mage.Attack();
        warrior.TakeDamage(mageDamage);
    }
}
// Один из персонажей должен быть мертв
assert(!warrior.IsAlive() || !mage.IsAlive());
```

---

## Задание 6: Файловая система

### Описание:
Смоделируйте файловую систему с помощью паттерна Composite. Создайте классы для файлов и папок.

### Требования:
- Абстрактный класс `FileSystemNode`
- Классы `File` и `Directory`
- Возможность вычисления общего размера
- Поиск файлов и папок

### Тесты:
```cpp
// Test 1: Создание файлов и папок
auto root = make_unique<Directory>("root");
auto documents = make_unique<Directory>("documents");
auto file1 = make_unique<File>("file1.txt", 1024);
auto file2 = make_unique<File>("file2.doc", 2048);

// Test 2: Добавление элементов
documents->Add(move(file1));
documents->Add(move(file2));
root->Add(move(documents));

// Test 3: Размер файлов
assert(root->GetSize() == 3072); // 1024 + 2048

// Test 4: Количество элементов
assert(root->GetChildCount() == 1); // только documents
auto documentsPtr = dynamic_cast<Directory*>(root->GetChild("documents"));
assert(documentsPtr->GetChildCount() == 2); // file1 + file2

// Test 5: Поиск файлов
auto found = root->Find("file1.txt");
assert(found != nullptr);
assert(found->GetName() == "file1.txt");

// Test 6: Путь к файлу
assert(found->GetPath() == "/root/documents/file1.txt");

// Test 7: Удаление файлов
assert(documentsPtr->Remove("file2.doc"));
assert(root->GetSize() == 1024);

// Test 8: Копирование
auto rootCopy = root->Clone();
assert(rootCopy->GetSize() == root->GetSize());

// Test 9: Перемещение файлов
auto pics = make_unique<Directory>("pictures");
root->Add(move(pics));
auto picsPtr = dynamic_cast<Directory*>(root->GetChild("pictures"));

auto file3 = make_unique<File>("photo.jpg", 5000);
picsPtr->Add(move(file3));

// Test 10: Итерация по содержимому
int totalFiles = 0;
root->ForEach([&totalFiles](FileSystemNode* node) {
    if(dynamic_cast<File*>(node)) {
        totalFiles++;
    }
});
assert(totalFiles == 2); // file1.txt + photo.jpg
```

---

## Задание 7: Транспортная система

### Описание:
Создайте иерархию транспортных средств с разными способами передвижения и характеристиками.

### Требования:
- Базовый класс `Vehicle`
- Производные классы: `Car`, `Bicycle`, `Airplane`, `Ship`
- Интерфейсы для разных способностей: `Flyable`, `Swimmable`
- Расчет времени и стоимости поездки

### Тесты:
```cpp
// Test 1: Создание транспорта
Car car("Toyota", 120, 8.5); // модель, скорость, расход
Bicycle bike("Mountain Bike", 25, 0);
Airplane plane("Boeing 747", 900, 3000);
Ship ship("Titanic", 45, 500);

// Test 2: Базовые характеристики
assert(car.GetMaxSpeed() == 120);
assert(bike.GetFuelConsumption() == 0);

// Test 3: Движение
car.StartEngine();
assert(car.IsEngineRunning());

bike.StartMoving();
assert(bike.IsMoving());

// Test 4: Расчет времени поездки
double timeByCarr = car.CalculateTravelTime(240); // 240 км
assert(abs(time - 2.0) < 0.1); // 240/120 = 2 часа

// Test 5: Расчет стоимости топлива
double fuelCost = car.CalculateFuelCost(100, 1.5); // 100км, 1.5$/л
assert(abs(fuelCost - 12.75) < 0.1); // 100*8.5/100*1.5

// Test 6: Способности к полету
auto flyable = dynamic_cast<Flyable*>(&plane);
assert(flyable != nullptr);
flyable->TakeOff();
assert(flyable->IsFlying());

// Test 7: Способности к плаванию
auto swimmable = dynamic_cast<Swimmable*>(&ship);
assert(swimmable != nullptr);
swimmable->SetSail();
assert(swimmable->IsSailing());

// Test 8: Универсальная функция движения
vector<unique_ptr<Vehicle>> fleet;
fleet.push_back(make_unique<Car>("BMW", 150, 9.0));
fleet.push_back(make_unique<Bicycle>("Road Bike", 30, 0));

for(auto& vehicle : fleet) {
    vehicle->StartMoving();
    assert(vehicle->IsMoving());
}

// Test 9: Сравнение эффективности
assert(bike.IsEcoFriendly()); // расход = 0
assert(!car.IsEcoFriendly()); // расход > 0

// Test 10: Техобслуживание
car.AddMileage(10000);
assert(car.NeedsMaintenance()); // пробег > лимита
car.PerformMaintenance();
assert(!car.NeedsMaintenance());
```

---

## Задание 8: Банковская система

### Описание:
Реализуйте систему банковских счетов с разными типами: сберегательный, текущий, депозитный.

### Требования:
- Базовый класс `BankAccount`
- Разные правила начисления процентов
- Ограничения на операции
- История транзакций

### Тесты:
```cpp
// Test 1: Создание счетов
SavingsAccount savings("SA001", "John Doe", 1000.0, 0.05);
CheckingAccount checking("CA001", "Jane Smith", 500.0);
DepositAccount deposit("DA001", "Bob Johnson", 5000.0, 0.08, 365);

// Test 2: Пополнение счета
savings.Deposit(200.0);
assert(savings.GetBalance() == 1200.0);

// Test 3: Снятие средств
assert(checking.Withdraw(100.0));
assert(checking.GetBalance() == 400.0);

// Test 4: Недостаток средств
assert(!checking.Withdraw(500.0));
assert(checking.GetBalance() == 400.0);

// Test 5: Начисление процентов
double initialBalance = savings.GetBalance();
savings.CalculateInterest();
assert(savings.GetBalance() > initialBalance);

// Test 6: Ограничения депозита
assert(!deposit.Withdraw(100.0)); // нельзя снимать до окончания срока
deposit.MaturityReached();
assert(deposit.Withdraw(100.0)); // теперь можно

// Test 7: История транзакций
checking.Deposit(50.0);
checking.Withdraw(25.0);
auto history = checking.GetTransactionHistory();
assert(history.size() >= 2);

// Test 8: Перевод между счетами
assert(savings.Transfer(checking, 100.0));
assert(savings.GetBalance() == 1100.0);
assert(checking.GetBalance() == 525.0);

// Test 9: Заморозка счета
checking.Freeze();
assert(!checking.Deposit(10.0));
assert(!checking.Withdraw(10.0));
checking.Unfreeze();
assert(checking.Deposit(10.0));

// Test 10: Полиморфная обработка
vector<unique_ptr<BankAccount>> accounts;
accounts.push_back(make_unique<SavingsAccount>("SA002", "User1", 1000, 0.03));
accounts.push_back(make_unique<CheckingAccount>("CA002", "User2", 800));

double totalBalance = 0;
for(auto& account : accounts) {
    totalBalance += account->GetBalance();
}
assert(totalBalance == 1800.0);
```

---

## Задание 9: Графический редактор

### Описание:
Создайте систему графических элементов для простого редактора с поддержкой группировки объектов.

### Требования:
- Абстрактный класс `GraphicElement`
- Примитивы: `Line`, `Rectangle`, `Circle`, `Text`
- Класс `Group` для группировки элементов
- Операции трансформации (перемещение, масштабирование, поворот)

### Тесты:
```cpp
// Test 1: Создание примитивов
auto line = make_unique<Line>(Point{0,0}, Point{10,10});
auto rect = make_unique<Rectangle>(Point{5,5}, 20, 15);
auto circle = make_unique<Circle>(Point{25,25}, 8);
auto text = make_unique<Text>(Point{30,30}, "Hello", "Arial", 12);

// Test 2: Получение границ
auto bounds = rect->GetBounds();
assert(bounds.x == 5 && bounds.y == 5);
assert(bounds.width == 20 && bounds.height == 15);

// Test 3: Перемещение
circle->Move(5, 5);
auto newCenter = circle->GetCenter();
assert(newCenter.x == 30 && newCenter.y == 30);

// Test 4: Масштабирование
rect->Scale(2.0);
auto newBounds = rect->GetBounds();
assert(newBounds.width == 40 && newBounds.height == 30);

// Test 5: Поворот
line->Rotate(45); // градусы
auto angle = line->GetAngle();
assert(abs(angle - 45) < 0.1);

// Test 6: Создание группы
auto group = make_unique<Group>();
group->Add(move(line));
group->Add(move(rect));
group->Add(move(circle));

// Test 7: Операции с группой
group->Move(10, 10); // перемещает все элементы
auto groupBounds = group->GetBounds();
assert(groupBounds.width > 0 && groupBounds.height > 0);

// Test 8: Разгруппировка
auto elements = group->Ungroup();
assert(elements.size() == 3);

// Test 9: Поиск элементов
group->Add(move(text));
auto found = group->FindElementAt(Point{32, 32});
assert(found != nullptr);

// Test 10: Сериализация
string xml = group->ToXML();
assert(xml.find("<group>") != string::npos);
assert(xml.find("<text>") != string::npos);

auto loadedGroup = Group::FromXML(xml);
assert(loadedGroup->GetElementCount() == group->GetElementCount());
```

---

## Задание 10: Система логирования

### Описание:
Реализуйте гибкую систему логирования с разными типами логгеров и уровнями важности сообщений.

### Требования:
- Абстрактный класс `Logger`
- Конкретные логгеры: `ConsoleLogger`, `FileLogger`, `NetworkLogger`
- Уровни логирования: DEBUG, INFO, WARNING, ERROR, CRITICAL
- Фильтрация по уровням и форматирование сообщений

### Тесты:
```cpp
// Test 1: Создание логгеров
ConsoleLogger console(LogLevel::INFO);
FileLogger file("app.log", LogLevel::WARNING);
NetworkLogger network("192.168.1.100", 514, LogLevel::ERROR);

// Test 2: Базовое логирование
console.Log(LogLevel::INFO, "Application started");
file.Log(LogLevel::WARNING, "Low memory warning");
network.Log(LogLevel::ERROR, "Database connection failed");

// Test 3: Фильтрация по уровню
console.Log(LogLevel::DEBUG, "Debug message"); // не должно выводиться
assert(console.GetLoggedMessageCount() == 1); // только INFO

// Test 4: Форматирование сообщений
string formatted = console.FormatMessage(LogLevel::ERROR, "Test message");
assert(formatted.find("[ERROR]") != string::npos);
assert(formatted.find("Test message") != string::npos);

// Test 5: Макросы для удобства
LOG_INFO(console, "Info message");
LOG_ERROR(file, "Error occurred");
LOG_DEBUG(console, "Debug info"); // отфильтруется

// Test 6: Составной логгер
CompositeLogger composite;
composite.AddLogger(make_unique<ConsoleLogger>(LogLevel::DEBUG));
composite.AddLogger(make_unique<FileLogger>("debug.log", LogLevel::DEBUG));

composite.Log(LogLevel::INFO, "Message to all loggers");

// Test 7: Асинхронное логирование
AsyncLogger async(make_unique<FileLogger>("async.log", LogLevel::INFO));
async.Log(LogLevel::INFO, "Async message 1");
async.Log(LogLevel::INFO, "Async message 2");
async.Flush(); // ждем записи всех сообщений

// Test 8: Ротация логов
RotatingFileLogger rotating("rotating.log", 1024, 5); // 1KB, 5 файлов
for(int i = 0; i < 1000; ++i) {
    rotating.Log(LogLevel::INFO, "Message " + to_string(i));
}
assert(rotating.GetCurrentFileNumber() > 1);

// Test 9: Фильтрация по содержимому
FilteringLogger filtering(make_unique<ConsoleLogger>(LogLevel::DEBUG));
filtering.AddFilter([](LogLevel level, const string& msg) {
    return msg.find("sensitive") == string::npos;
});

filtering.Log(LogLevel::INFO, "Normal message"); // пройдет
filtering.Log(LogLevel::INFO, "Contains sensitive data"); // отфильтруется

// Test 10: Статистика логирования
assert(console.GetMessageCount(LogLevel::INFO) > 0);
assert(console.GetMessageCount(LogLevel::ERROR) > 0);
assert(file.GetTotalBytesWritten() > 0);

auto stats = composite.GetStatistics();
assert(stats.totalMessages > 0);
assert(stats.messagesPerLevel[LogLevel::INFO] > 0);
```

---

## Примечания по выполнению:
1. Используйте современные возможности C++17
2. Следуйте принципам SOLID
3. Добавляйте необходимые include-файлы
4. Используйте умные указатели для управления памятью
5. Обрабатывайте исключительные ситуации
6. Пишите чистый, читаемый код с комментариями 