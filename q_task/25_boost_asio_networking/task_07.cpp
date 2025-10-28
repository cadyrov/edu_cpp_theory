// Task 7: Graceful Shutdown
// Create a ServerWithShutdown class that:
// - Runs as server (listen on port 9002)
// - Can be properly terminated (graceful shutdown)
// - On shutdown:
//   - Stop accepting new connections
//   - Close all active connections
//   - Wait for current operations to complete
//   - Stop event loop
//
// Requirements:
// - shutdown() method to initiate shutdown
// - waitUntilShutdown() method to wait for completion
// - Use flags/variables to control state

#include <boost/asio.hpp>
#include <iostream>
#include <memory>
#include <array>
#include <set>
#include <atomic>
#include <thread>
#include <mutex>

class ServerWithShutdown {
private:
    struct Connection : std::enable_shared_from_this<Connection> {
        boost::asio::ip::tcp::socket socket;
        std::array<char, 1024> buffer;
        
        Connection(boost::asio::io_context& io) : socket(io) {}
        
        static std::shared_ptr<Connection> create(boost::asio::io_context& io) {
            return std::make_shared<Connection>(io);
        }
        
        void start() {
            // TODO: Start async read
        }
    };
    
public:
    ServerWithShutdown(uint16_t port) 
        : acceptor_(io_context_,
                    boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), port)) {
        // TODO: Call startAccept()
    }
    
    void run() {
        // TODO: io_context_.run();
    }
    
    void shutdown() {
        // TODO: Implement graceful shutdown
        // 1. Set shutting_down_ = true
        // 2. Stop accepting new connections (acceptor_.close())
        // 3. Close all active connections (connections_.clear())
        // 4. Stop event loop (io_context_.stop())
    }
    
    void waitUntilShutdown() {
        // TODO: Wait for shutdown to complete
        // Could use a future, condition_variable, or polling loop
    }
    
private:
    boost::asio::io_context io_context_;
    boost::asio::ip::tcp::acceptor acceptor_;
    std::set<std::shared_ptr<Connection>> connections_;
    std::atomic<bool> shutting_down_{false};
    std::mutex connections_mutex_;
    
    void startAccept() {
        // TODO: Implement async_accept
        // - Check if shutting_down_ before accepting new
        // - Create connection
        // - Add to connections_ set (with lock)
        // - Call connection->start()
        // - Recursively call startAccept()
    }
    
    void removeConnection(std::shared_ptr<Connection> conn) {
        // TODO: Remove connection from set when it closes
        // Use lock_guard for thread safety
    }
};

int main() {
    try {
        ServerWithShutdown server(9002);
        std::cout << "Server with graceful shutdown listening on port 9002...\n";
        
        // Run server in separate thread
        std::thread server_thread([&server] { server.run(); });
        
        // Simulate some work, then shutdown
        std::this_thread::sleep_for(std::chrono::seconds(10));
        
        std::cout << "Initiating shutdown...\n";
        server.shutdown();
        server.waitUntilShutdown();
        
        server_thread.join();
        std::cout << "Server stopped.\n";
        
    } catch (std::exception& e) {
        std::cerr << "Error: " << e.what() << "\n";
    }
    return 0;
}
