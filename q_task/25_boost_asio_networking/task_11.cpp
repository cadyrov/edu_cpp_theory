// Task 11: Data Pipeline
// Create an application where:
// - TCP client sends 10 numbers in sequence
// - TCP server receives numbers (may arrive in multiple packets)
// - Server sums all numbers
// - Server sends sum back
//
// Requirements:
// - Data arrives in separate packets (not all at once)
// - Need to accumulate data until all received
// - Use buffer to collect complete message

#include <boost/asio.hpp>
#include <iostream>
#include <memory>
#include <array>
#include <vector>
#include <sstream>

class PipelineServer {
private:
    struct Connection : std::enable_shared_from_this<Connection> {
        boost::asio::ip::tcp::socket socket;
        std::string buffer;
        std::vector<int> numbers;
        static constexpr size_t EXPECTED_NUMBERS = 10;
        
        Connection(boost::asio::io_context& io) : socket(io) {}
        
        static std::shared_ptr<Connection> create(boost::asio::io_context& io) {
            return std::make_shared<Connection>(io);
        }
        
        void start() {
            // TODO: Call readNumbers()
        }
        
    private:
        void readNumbers() {
            // TODO: Implement async_read_some
            // - Read data into temporary buffer
            // - Append to buffer
            // - Parse numbers from buffer (split by space or newline)
            // - When EXPECTED_NUMBERS received, call sendSum()
            // - Continue reading until all numbers received or EOF
        }
        
        void sendSum() {
            // TODO: Calculate sum of all numbers
            // - Sum all numbers in vector
            // - Convert to string
            // - Send using async_write
        }
    };
    
public:
    PipelineServer(uint16_t port) 
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
    
    void startAccept() {
        // TODO: Implement async_accept and connection start
    }
};

class PipelineClient {
public:
    PipelineClient(const std::string& host, uint16_t port) {
        // TODO: Implement
        // 1. Create socket and resolver
        // 2. async_resolve and async_connect
        // 3. Send 10 numbers: "1 2 3 4 5 6 7 8 9 10"
        // 4. Receive sum result
        // 5. Print result
    }
    
    void run() {
        // TODO: io_context_.run();
    }
    
private:
    boost::asio::io_context io_context_;
    std::unique_ptr<boost::asio::ip::tcp::socket> socket_;
    
    void sendNumbers() {
        // TODO: Send 10 numbers
        // Format: space-separated or newline-separated
        // Example: "1 2 3 4 5 6 7 8 9 10\n"
    }
    
    void receiveSum() {
        // TODO: Receive and print sum
    }
};

int main() {
    try {
        std::cout << "Starting server...\n";
        PipelineServer server(9000);
        
        // In real scenario, run server in separate thread
        // For now, we just show the structure
        
        std::cout << "Would send 10 numbers and receive sum.\n";
        
    } catch (std::exception& e) {
        std::cerr << "Error: " << e.what() << "\n";
    }
    return 0;
}
