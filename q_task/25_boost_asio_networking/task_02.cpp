// Task 2: TCP Client with Connection
// Create a SimpleTCPClient class that:
// - Connects to server (localhost:9000)
// - Sends message "Hello"
// - Receives response and prints it
// - Closes connection
//
// Requirements:
// - Async connect (async_connect)
// - Async write (async_write)
// - Async read (async_read_some)
// - Handle all error_codes

#include <boost/asio.hpp>
#include <iostream>
#include <memory>
#include <array>

class SimpleTCPClient {
public:
    SimpleTCPClient(const std::string& host, uint16_t port) {
        // TODO: Implement
        // 1. Create socket
        // 2. Create resolver
        // 3. Call async_resolve to get endpoints
        // 4. Call async_connect with endpoints
        // 5. In handler: call sendMessage("Hello")
        // 6. Call io_context_.run()
    }
    
private:
    boost::asio::io_context io_context_;
    std::unique_ptr<boost::asio::ip::tcp::socket> socket_;
    
    void sendMessage(const std::string& msg) {
        // TODO: Implement async_write
        // - Call socket_->async_write with buffer containing msg
        // - In handler: check error_code
        // - If OK: call readResponse()
    }
    
    void readResponse() {
        // TODO: Implement async_read_some
        // - Create buffer with make_shared<std::array<char, 1024>>
        // - Call socket_->async_read_some
        // - In handler: print received data
        // - Close socket after reading
    }
};

int main() {
    try {
        SimpleTCPClient client("127.0.0.1", 9000);
    } catch (std::exception& e) {
        std::cerr << "Error: " << e.what() << "\n";
    }
    return 0;
}
