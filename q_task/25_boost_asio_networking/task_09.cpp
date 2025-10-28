// Task 9: Connection Pooling
// Create a ConnectionPool class that:
// - Manages cache of reusable TCP connections
// - acquire() method - get free connection or create new one
// - release() method - return connection to pool
// - Max 10 connections
// - Reuse existing before creating new
//
// Requirements:
// - Track free and in-use connections
// - FIFO order for free connections
// - Thread safety (if used from multiple threads)

#include <boost/asio.hpp>
#include <iostream>
#include <memory>
#include <queue>
#include <set>
#include <mutex>
#include <condition_variable>

class Connection {
public:
    Connection(boost::asio::io_context& io) : socket_(io) {}
    
    boost::asio::ip::tcp::socket& getSocket() { return socket_; }
    const boost::asio::ip::tcp::socket& getSocket() const { return socket_; }
    
    bool isConnected() const { return socket_.is_open(); }
    
private:
    boost::asio::ip::tcp::socket socket_;
};

class ConnectionPool {
public:
    ConnectionPool(boost::asio::io_context& io, size_t max_size = 10)
        : io_context_(io), max_size_(max_size) {}
    
    std::shared_ptr<Connection> acquire() {
        // TODO: Implement
        // 1. Lock mutex
        // 2. If available queue not empty:
        //    - Pop from available
        //    - Add to in_use set
        //    - Return
        // 3. If in_use size < max_size:
        //    - Create new connection
        //    - Add to in_use
        //    - Return
        // 4. Otherwise: return nullptr (or wait/throw)
        return nullptr;
    }
    
    void release(std::shared_ptr<Connection> conn) {
        // TODO: Implement
        // 1. Lock mutex
        // 2. Remove from in_use set
        // 3. Add to available queue
        // 4. Notify waiting threads (if any)
    }
    
    size_t availableCount() const {
        std::lock_guard<std::mutex> lock(mutex_);
        return available_.size();
    }
    
    size_t inUseCount() const {
        std::lock_guard<std::mutex> lock(mutex_);
        return in_use_.size();
    }
    
    size_t totalCount() const {
        return availableCount() + inUseCount();
    }
    
private:
    boost::asio::io_context& io_context_;
    size_t max_size_;
    mutable std::mutex mutex_;
    std::condition_variable cv_;
    
    std::queue<std::shared_ptr<Connection>> available_;
    std::set<std::shared_ptr<Connection>> in_use_;
};

// Example usage
int main() {
    try {
        boost::asio::io_context io_context;
        
        // Run io_context in separate thread
        std::thread io_thread([&io_context] { io_context.run(); });
        
        ConnectionPool pool(io_context, 5);  // Max 5 connections
        
        std::vector<std::shared_ptr<Connection>> conns;
        
        // Acquire some connections
        std::cout << "Acquiring 3 connections...\n";
        for (int i = 0; i < 3; ++i) {
            auto conn = pool.acquire();
            if (conn) {
                conns.push_back(conn);
                std::cout << "Acquired connection " << (i + 1) 
                          << ". Pool: " << pool.inUseCount() << " in use, "
                          << pool.availableCount() << " available\n";
            }
        }
        
        // Release one
        std::cout << "\nReleasing 1 connection...\n";
        conns.pop_back();
        std::cout << "Released. Pool: " << pool.inUseCount() << " in use, "
                  << pool.availableCount() << " available\n";
        
        // Reacquire
        std::cout << "\nReacquiring connection...\n";
        auto conn = pool.acquire();
        if (conn) {
            conns.push_back(conn);
            std::cout << "Reacquired. Pool: " << pool.inUseCount() << " in use, "
                      << pool.availableCount() << " available\n";
        }
        
        io_context.stop();
        io_thread.join();
        
    } catch (std::exception& e) {
        std::cerr << "Error: " << e.what() << "\n";
    }
    return 0;
}
