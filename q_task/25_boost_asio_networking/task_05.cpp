// Task 5: TCP Connect with Timeout
// Create a ConnectWithTimeout class that:
// - Attempts to connect to server
// - Has 3 second timeout
// - If connection fails within timeout - cancel the operation
// - Print result (success or timeout)
//
// Requirements:
// - Use deadline_timer or steady_timer
// - Cancel operation on timeout using cancel()
// - Synchronization between timer and connect

#include <boost/asio.hpp>
#include <iostream>
#include <memory>
#include <atomic>

class ConnectWithTimeout {
public:
    ConnectWithTimeout(const std::string& host, uint16_t port) {
        // TODO: Implement
        // 1. Create socket and timer
        // 2. Set timer expiration to 3 seconds
        // 3. Set async_wait on timer to cancel socket on timeout
        // 4. Create resolver
        // 5. Call async_resolve
        // 6. Call async_connect with timeout check
        // 7. In connect handler: cancel timer if success
        // 8. In timer handler: cancel socket if timeout
    }
    
    void run() {
        // TODO: io_context_.run();
    }
    
    bool isConnected() const {
        // TODO: Return true if connected successfully
        return false;
    }
    
private:
    boost::asio::io_context io_context_;
    std::unique_ptr<boost::asio::ip::tcp::socket> socket_;
    boost::asio::deadline_timer timer_{io_context_};
    std::atomic<bool> connected_{false};
    
    void onConnectSuccess() {
        // TODO: Cancel timer and set connected_ = true
    }
    
    void onTimeout() {
        // TODO: Cancel socket operation
    }
};

int main() {
    try {
        ConnectWithTimeout client("127.0.0.1", 9000);
        client.run();
        
        if (client.isConnected()) {
            std::cout << "Connected successfully!\n";
        } else {
            std::cout << "Connection timeout!\n";
        }
    } catch (std::exception& e) {
        std::cerr << "Error: " << e.what() << "\n";
    }
    return 0;
}
