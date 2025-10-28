// Task 6: Multi-Client Server
// Extend SimpleEchoServer to:
// - Support up to 100 concurrent connections
// - For each client, read lines (newline-separated)
// - Send back "ECHO: " + received line
// - On disconnect, remove client from list
//
// Requirements:
// - Manage multiple Connection objects
// - Correct lifetime with shared_ptr
// - Handle EOF on disconnect

#include <boost/asio.hpp>
#include <iostream>
#include <memory>
#include <array>
#include <set>

class MultiClientServer {
private:
    struct Connection : std::enable_shared_from_this<Connection> {
        boost::asio::ip::tcp::socket socket;
        std::array<char, 1024> buffer;
        std::string line_buffer;
        
        Connection(boost::asio::io_context& io) : socket(io) {}
        
        static std::shared_ptr<Connection> create(boost::asio::io_context& io) {
            return std::make_shared<Connection>(io);
        }
        
        void start() {
            // TODO: Call readLine()
        }
        
    private:
        void readLine() {
            // TODO: Implement async_read_some
            // - Read data into buffer
            // - Parse lines (split by \n)
            // - For complete lines: call processLine()
            // - Continue reading until EOF or error
        }
        
        void processLine(const std::string& line) {
            // TODO: Implement async_write
            // - Send "ECHO: " + line + "\n"
            // - Continue reading after write
        }
    };
    
public:
    MultiClientServer(uint16_t port) 
        : acceptor_(io_context_,
                    boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), port)) {
        // TODO: Call startAccept()
    }
    
    void run() {
        // TODO: io_context_.run();
    }
    
private:
    boost::asio::io_context io_context_;
    boost::asio::ip::tcp::acceptor acceptor_;
    std::set<std::shared_ptr<Connection>> connections_;
    static constexpr size_t MAX_CONNECTIONS = 100;
    
    void startAccept() {
        // TODO: Implement async_accept
        // - Accept new connection if < MAX_CONNECTIONS
        // - Create Connection with shared_ptr
        // - Add to connections_ set
        // - Call connection->start()
        // - Recursively call startAccept()
    }
};

int main() {
    try {
        MultiClientServer server(9000);
        std::cout << "Multi-client echo server listening on port 9000...\n";
        server.run();
    } catch (std::exception& e) {
        std::cerr << "Error: " << e.what() << "\n";
    }
    return 0;
}
