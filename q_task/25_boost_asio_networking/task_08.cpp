// Task 8: Robust Error Handling
// Create a RobustServer class that:
// - Listens on port 9003
// - Handles all error types:
//   - error::eof - client closed connection
//   - error::operation_aborted - connection was cancelled
//   - error::connection_reset - connection was reset
//   - Other errors
// - For each error, log message and properly close connection
//
// Requirements:
// - Check error_code in every callback
// - Use ec.message() to output error
// - Proper recovery or termination on error

#include <boost/asio.hpp>
#include <iostream>
#include <memory>
#include <array>
#include <iomanip>
#include <chrono>

class RobustServer {
private:
    struct Connection : std::enable_shared_from_this<Connection> {
        boost::asio::ip::tcp::socket socket;
        std::array<char, 1024> buffer;
        uint32_t id;
        
        Connection(boost::asio::io_context& io, uint32_t conn_id) 
            : socket(io), id(conn_id) {}
        
        static std::shared_ptr<Connection> create(boost::asio::io_context& io, uint32_t id) {
            return std::make_shared<Connection>(io, id);
        }
        
        void start() {
            // TODO: Call startRead()
        }
        
    private:
        void startRead() {
            // TODO: Implement async_read_some with error handling
            // - Use auto self = shared_from_this()
            // - Check all error codes:
            //   - eof: print "Connection closed by client"
            //   - operation_aborted: print "Operation cancelled"
            //   - connection_reset: print "Connection reset by peer"
            //   - other errors: print ec.message()
            // - On any error: properly close socket and exit
        }
    };
    
public:
    RobustServer(uint16_t port) 
        : acceptor_(io_context_,
                    boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), port)),
          next_connection_id_(0) {
        // TODO: Call startAccept()
    }
    
    void run() {
        // TODO: io_context_.run();
    }
    
private:
    boost::asio::io_context io_context_;
    boost::asio::ip::tcp::acceptor acceptor_;
    uint32_t next_connection_id_;
    
    void startAccept() {
        // TODO: Implement async_accept with error handling
        // - Create connection with next_connection_id_++
        // - Print "Connection accepted: [id]"
        // - Call connection->start()
        // - Handle accept errors (print to stderr)
        // - Recursively call startAccept() to listen for more
    }
    
    void logError(uint32_t conn_id, const std::string& context, const boost::system::error_code& ec) {
        // Helper function to log errors with timestamp
        auto now = std::chrono::system_clock::now();
        auto time = std::chrono::system_clock::to_time_t(now);
        std::cerr << "[" << std::put_time(std::localtime(&time), "%H:%M:%S") << "] "
                  << "Connection " << conn_id << " - " << context << ": "
                  << ec.message() << "\n";
    }
};

int main() {
    try {
        RobustServer server(9003);
        std::cout << "Robust server with error handling listening on port 9003...\n";
        std::cout << "Test connections and errors will be logged.\n";
        server.run();
    } catch (std::exception& e) {
        std::cerr << "Fatal error: " << e.what() << "\n";
    }
    return 0;
}
