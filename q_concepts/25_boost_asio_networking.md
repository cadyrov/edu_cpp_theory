# Boost.ASIO Network Programming

## Определение
Boost.ASIO (Asynchronous I/O) - библиотека для асинхронного ввода-вывода, включая работу с сетевыми сокетами (TCP, UDP), файлами, таймерами. Основан на event loop с концепцией service/handler.

## Зачем это нужно
- Работа с сетевыми протоколами без блокирования потока
- Масштабируемость: один поток может обрабатывать тысячи соединений
- Асинхронные операции с автоматическим управлением ресурсами (RAII)
- Поддержка таймеров, сигналов, файловых дескрипторов

## TCP vs UDP

### TCP (Transmission Control Protocol)
- Надежная доставка: гарантирует порядок и полноту данных
- Соединение ориентированное: требует установления соединения перед передачей
- Медленнее, но безопаснее
- Используется для: веб-приложений, FTP, SSH, базы данных

### UDP (User Datagram Protocol)
- Ненадежная доставка: пакеты могут теряться или приходить в другом порядке
- Без соединения: отправляем данные напрямую
- Быстрее,low оверхед
- Используется для: видеопотоков, онлайн-игр, DNS, VoIP

## Архитектура сервера в ASIO

### I/O Service (Event Loop)
```cpp
boost::asio::io_context io_context;
// io_context.run() блокирует и обрабатывает асинхронные события
```

### Сокет
```cpp
// TCP сокет
boost::asio::ip::tcp::socket sock(io_context);

// UDP сокет
boost::asio::ip::udp::socket sock(io_context);
```

### Acceptor (для сервера)
```cpp
boost::asio::ip::tcp::acceptor acceptor(
    io_context,
    boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), 8080)
);
// Слушает входящие соединения на порту 8080
```

## Примеры

### ✅ Хорошо

#### TCP Сервер
```cpp
class TCPServer {
    boost::asio::io_context io_context_;
    std::unique_ptr<boost::asio::ip::tcp::acceptor> acceptor_;
    
public:
    TCPServer(uint16_t port) {
        acceptor_ = std::make_unique<boost::asio::ip::tcp::acceptor>(
            io_context_,
            boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), port)
        );
        startAccept();
    }
    
    void run() {
        io_context_.run();  // Event loop
    }
    
private:
    void startAccept() {
        auto sock = std::make_shared<boost::asio::ip::tcp::socket>(io_context_);
        
        // Асинхронное принятие соединения
        acceptor_->async_accept(*sock, [this, sock](const boost::system::error_code& ec) {
            if (!ec) {
                handleConnection(sock);
            }
            startAccept();  // Продолжаем слушать
        });
    }
    
    void handleConnection(std::shared_ptr<boost::asio::ip::tcp::socket> sock) {
        auto buffer = std::make_shared<std::array<char, 1024>>();
        
        // Асинхронное чтение данных
        sock->async_read_some(
            boost::asio::buffer(*buffer),
            [this, sock, buffer](const boost::system::error_code& ec, size_t bytes) {
                if (!ec && bytes > 0) {
                    // Обработка данных
                    std::string message(buffer->data(), bytes);
                    
                    // Асинхронная отправка ответа
                    boost::asio::async_write(
                        *sock,
                        boost::asio::buffer("OK"),
                        [](const boost::system::error_code&, size_t) {}
                    );
                }
                // Соединение автоматически закроется при уничтожении sock
            }
        );
    }
};

// Использование
TCPServer server(8080);
server.run();
```

#### TCP Клиент
```cpp
class TCPClient {
    boost::asio::io_context io_context_;
    std::unique_ptr<boost::asio::ip::tcp::socket> socket_;
    
public:
    TCPClient(const std::string& host, uint16_t port) 
        : socket_(std::make_unique<boost::asio::ip::tcp::socket>(io_context_)) {
        
        boost::asio::ip::tcp::resolver resolver(io_context_);
        auto results = resolver.resolve(host, std::to_string(port));
        
        // Асинхронное подключение
        boost::asio::async_connect(
            *socket_,
            results,
            [this](const boost::system::error_code& ec) {
                if (!ec) {
                    sendMessage("Hello Server");
                }
            }
        );
        
        io_context_.run();
    }
    
private:
    void sendMessage(const std::string& msg) {
        boost::asio::async_write(
            *socket_,
            boost::asio::buffer(msg),
            [this](const boost::system::error_code& ec, size_t) {
                if (!ec) {
                    readResponse();
                }
            }
        );
    }
    
    void readResponse() {
        auto buffer = std::make_shared<std::array<char, 1024>>();
        socket_->async_read_some(
            boost::asio::buffer(*buffer),
            [buffer](const boost::system::error_code& ec, size_t bytes) {
                if (!ec) {
                    std::cout << std::string(buffer->data(), bytes);
                }
            }
        );
    }
};

// Использование
TCPClient client("127.0.0.1", 8080);
```

#### UDP Сокет (Sender/Receiver)
```cpp
class UDPServer {
    boost::asio::io_context io_context_;
    boost::asio::ip::udp::socket socket_;
    
public:
    UDPServer(uint16_t port) 
        : socket_(io_context_,
                  boost::asio::ip::udp::endpoint(boost::asio::ip::udp::v4(), port)) {
        startReceive();
    }
    
    void run() { io_context_.run(); }
    
private:
    void startReceive() {
        auto buffer = std::make_shared<std::array<char, 1024>>();
        boost::asio::ip::udp::endpoint remote_endpoint;
        
        socket_.async_receive_from(
            boost::asio::buffer(*buffer),
            remote_endpoint,
            [this, buffer, remote_endpoint](const boost::system::error_code& ec, size_t bytes) mutable {
                if (!ec && bytes > 0) {
                    // Отправка ответа обратно
                    socket_.async_send_to(
                        boost::asio::buffer("ACK"),
                        remote_endpoint,
                        [](const boost::system::error_code&, size_t) {}
                    );
                }
                startReceive();  // Продолжаем слушать
            }
        );
    }
};
```

#### Работа с таймерами (для timeout-ов)
```cpp
class TimedConnection {
    boost::asio::io_context io_context_;
    boost::asio::ip::tcp::socket socket_;
    boost::asio::deadline_timer timer_;
    
public:
    TimedConnection() 
        : socket_(io_context_),
          timer_(io_context_) {
        connectWithTimeout();
    }
    
    void run() { io_context_.run(); }
    
private:
    void connectWithTimeout() {
        // Таймер на 5 секунд
        timer_.expires_from_now(boost::posix_time::seconds(5));
        timer_.async_wait([this](const boost::system::error_code& ec) {
            if (!ec) {
                socket_.cancel();  // Отменяем соединение при timeout
            }
        });
        
        boost::asio::ip::tcp::resolver resolver(io_context_);
        auto results = resolver.resolve("example.com", "80");
        
        boost::asio::async_connect(*socket_, results, 
            [this](const boost::system::error_code& ec) {
                timer_.cancel();  // Отменяем таймер если соединилось
                if (!ec) {
                    // OK, соединение установлено
                }
            }
        );
    }
};
```

#### Правильное управление lifetime'ом
```cpp
class ConnectionManager {
    struct Connection : std::enable_shared_from_this<Connection> {
        boost::asio::ip::tcp::socket socket;
        std::array<char, 1024> buffer;
        
        Connection(boost::asio::io_context& io) : socket(io) {}
        
        static std::shared_ptr<Connection> create(boost::asio::io_context& io) {
            return std::make_shared<Connection>(io);
        }
        
        void start() {
            auto self = shared_from_this();
            socket.async_read_some(
                boost::asio::buffer(buffer),
                [self](const boost::system::error_code& ec, size_t bytes) {
                    // self гарантирует что Connection жива во время callback
                }
            );
        }
    };
};
```

### ❌ Плохо

#### Блокирующий ввод-вывод (медленно)
```cpp
// Плохо: блокирует поток
boost::asio::ip::tcp::socket socket(io_context);
socket.connect(endpoint);  // Блокирует
socket.write_some(buffer);  // Блокирует
socket.read_some(buffer);   // Блокирует
```

#### Неправильное управление памятью
```cpp
// Плохо: утечка памяти
class BadServer {
    void handleConnection(boost::asio::ip::tcp::socket* sock) {
        sock->async_read_some(buffer, [sock](auto ec, auto) {
            delete sock;  // Может быть дублирующие delete
        });
    }
};
```

#### Забытое управление lifetime'ом
```cpp
// Плохо: use-after-free
class Dangerous {
    void connect() {
        boost::asio::ip::tcp::socket sock(io_context);  // Local variable
        sock.async_read_some(buffer, [](auto, auto) {
            // sock может быть уже уничтожена!
        });
    }  // sock уничтожается здесь
};
```

#### Синхронный код в асинхронном контексте
```cpp
// Плохо: блокирует event loop
acceptor_.async_accept(socket, [](auto ec) {
    std::this_thread::sleep_for(std::chrono::seconds(5));  // БЛОКИРУЕТ!
    // Никакие другие события не будут обработаны
});
```

#### Неправильная обработка ошибок
```cpp
// Плохо: игнорируем ошибки
socket.async_read_some(buffer, [](auto ec, auto bytes) {
    if (bytes > 0) {  // Но что если ec != 0?
        process(buffer);
    }
});
```

## Нюансы использования

### 1. Event Loop и потоки
```cpp
// Один поток - один io_context
boost::asio::io_context io_context;
// io_context.run() - блокирует в текущем потоке

// Многопоточность
std::vector<std::thread> threads;
for (int i = 0; i < 4; ++i) {
    threads.emplace_back([&io_context] { io_context.run(); });
}
// Несколько потоков обрабатывают события из одного io_context
// Колбеки могут вызваться из разных потоков!
```

### 2. Жизненный цикл асинхронной операции
```cpp
// Этапы:
// 1. Операция инициирована (async_read, async_write, async_accept и т.д.)
// 2. Ресурс жива пока операция в очереди
// 3. Когда событие готово, вызывается handler в event loop
// 4. После handler - ресурс может быть удален

// Поэтому используй shared_ptr для данных жизненного цикла!
```

### 3. Resolver и DNS
```cpp
// Резолвер может быть долгой операцией
boost::asio::ip::tcp::resolver resolver(io_context);

// Асинхронный resolve (хорошо)
resolver.async_resolve(query, [](auto ec, auto results) {
    // Может быть вызвано через 1 сек+ из-за DNS запроса
});

// Синхронный resolve (плохо - блокирует event loop)
auto results = resolver.resolve(query);
```

### 4. Connection pooling (для производства)
```cpp
class ConnectionPool {
    std::queue<std::shared_ptr<Connection>> available_;
    std::set<std::shared_ptr<Connection>> in_use_;
    size_t max_size_;
    
public:
    std::shared_ptr<Connection> acquire() {
        if (!available_.empty()) {
            auto conn = available_.front();
            available_.pop();
            in_use_.insert(conn);
            return conn;
        }
        // Создай новое если есть место
        if (in_use_.size() < max_size_) {
            auto conn = createConnection();
            in_use_.insert(conn);
            return conn;
        }
        return nullptr;  // Жди свободное
    }
    
    void release(std::shared_ptr<Connection> conn) {
        in_use_.erase(conn);
        available_.push(conn);
    }
};
```

### 5. Error handling
```cpp
// Всегда проверяй error_code
socket.async_read_some(buffer, 
    [](const boost::system::error_code& ec, size_t bytes) {
        if (ec == boost::asio::error::eof) {
            // Клиент закрыл соединение
        } else if (ec == boost::asio::error::operation_aborted) {
            // Операция была отменена (socket закрыт)
        } else if (ec) {
            // Другая ошибка
            std::cerr << "Error: " << ec.message();
        } else {
            // OK
        }
    }
);
```

### 6. Graceful shutdown
```cpp
class Server {
    void shutdown() {
        // Не принимаем новые соединения
        acceptor_.close();
        
        // Закрываем все активные соединения
        // (их деструкторы вызовут socket.close())
        connections_.clear();
        
        // Даем время на завершение текущих операций
        // Затем вызываем io_context.stop()
    }
};
```

### 7. Buffering
```cpp
// Плохо: заново выделяешь буфер каждый раз
socket.async_read_some(boost::asio::buffer(std::vector<char>(1024)), ...);

// Хорошо: переиспользуй буфер
auto buffer = std::make_shared<std::array<char, 1024>>();
socket.async_read_some(boost::asio::buffer(*buffer), ...);
```

### 8. SSL/TLS поддержка
```cpp
// ASIO поддерживает SSL через OpenSSL
boost::asio::ssl::context ctx(boost::asio::ssl::context::sslv23);
ctx.set_options(
    boost::asio::ssl::context::default_workarounds |
    boost::asio::ssl::context::no_sslv2 |
    boost::asio::ssl::context::single_dh_use
);
ctx.use_certificate_chain_file("server.pem");
ctx.use_private_key_file("key.pem", boost::asio::ssl::context::pem);

// Используй ssl::stream вместо обычного socket
boost::asio::ssl::stream<boost::asio::ip::tcp::socket> 
    secure_socket(io_context, ctx);
```

### 9. Performance: strand для синхронизации
```cpp
// Без strand - handler может вызваться из разных потоков
socket.async_read_some(buffer, handler);

// С strand - handler всегда вызывается в том же потоке
boost::asio::strand<boost::asio::io_context::executor_type> strand(io_context.get_executor());
socket.async_read_some(buffer, strand.wrap(handler));

// Или упрощенно:
socket.async_read_some(buffer, 
    [this](auto...) { strand_.post([this] { /* handler code */ }); }
);
```

### 10. Типичные ошибки с таймерами
```cpp
// Плохо: deadline_timer требует постоянного update
boost::asio::deadline_timer timer(io_context);
timer.expires_from_now(boost::posix_time::seconds(10));

// Хорошо: используй steady_timer для wall clock времени
boost::asio::steady_timer steady_timer(io_context);
steady_timer.expires_from_now(std::chrono::seconds(10));
```
