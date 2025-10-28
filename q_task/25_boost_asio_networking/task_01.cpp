// Task 1: Simple TCP Echo Server
// Create a SimpleEchoServer class that:
// - Listens on port 9000
// - Accepts TCP connections
// - For each client, reads data and sends it back (echo)
// - Asynchronously handles multiple connections
// - Properly closes connections on disconnect
//
// Requirements:
// - Use async operations (async_accept, async_read_some, async_write)
// - Lifetime management with shared_ptr
// - error_code handling

#include <boost/asio.hpp>
#include <iostream>
#include <memory>
#include <array>

class SimpleEchoServer {
public:
    SimpleEchoServer(uint16_t port) {
        // TODO: Implement
        // 1. Create acceptor on the specified port
        // 2. Call startAccept()
    }
    
    void run() {
        // TODO: io_context_.run();
    }
    
private:
    boost::asio::io_context io_context_;
    std::unique_ptr<boost::asio::ip::tcp::acceptor> acceptor_;
    
    void startAccept() {
        // TODO: Implement async_accept
        // - Create new socket with make_shared
        // - Call acceptor_->async_accept with handler
        // - In handler: call handleConnection if no error
        // - Recursively call startAccept to listen for more
    }
    
    void handleConnection(std::shared_ptr<boost::asio::ip::tcp::socket> sock) {
        // TODO: Implement async_read_some
        // - Create buffer with make_shared<std::array<char, 1024>>
        // - Call sock->async_read_some
        // - In handler: if bytes > 0 and no error, write back the data
        // - Use boost::asio::async_write to send response
    }
};

int main() {
    try {
        SimpleEchoServer server(9000);
        std::cout << "Echo server listening on port 9000...\n";
        server.run();
    } catch (std::exception& e) {
        std::cerr << "Error: " << e.what() << "\n";
    }
    return 0;
}
