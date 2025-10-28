// Task 12: Bulk Data Transfer
// Create a BulkDataServer that:
// - Receives file over TCP (first size in bytes, then data)
// - Writes to disk
// - Shows progress (bytes received)
// - Verifies checksum (simple CRC32 or XOR)
//
// Requirements:
// - Async read in multiple stages
// - Correct buffer management
// - Progress tracking
// - Checksum calculation (CRC32 or simple XOR)

#include <boost/asio.hpp>
#include <iostream>
#include <memory>
#include <array>
#include <fstream>
#include <iomanip>

class BulkDataServer {
private:
    struct Connection : std::enable_shared_from_this<Connection> {
        boost::asio::ip::tcp::socket socket;
        std::array<char, 1024> buffer;
        
        // File transfer state
        enum State {
            WAITING_FOR_SIZE,
            READING_DATA,
            COMPLETE
        } state = WAITING_FOR_SIZE;
        
        uint64_t file_size = 0;
        uint64_t bytes_received = 0;
        uint32_t checksum = 0;
        std::ofstream output_file;
        uint32_t connection_id;
        
        Connection(boost::asio::io_context& io, uint32_t id) 
            : socket(io), connection_id(id) {}
        
        static std::shared_ptr<Connection> create(boost::asio::io_context& io, uint32_t id) {
            return std::make_shared<Connection>(io, id);
        }
        
        void start() {
            // TODO: Call readSize()
        }
        
    private:
        void readSize() {
            // TODO: Implement async_read for file size (8 bytes, uint64_t)
            // - Read size in network byte order (big-endian)
            // - Store in file_size
            // - Update state to READING_DATA
            // - Call readData()
        }
        
        void readData() {
            // TODO: Implement async_read_some for file data
            // - Read available data
            // - Append to file
            // - Update checksum
            // - Track bytes_received
            // - Print progress (every 10%)
            // - When bytes_received == file_size: call complete()
        }
        
        void complete() {
            // TODO: Handle completion
            // - Print final status
            // - Send checksum back to client (optional)
            // - Close file and socket
        }
        
        void updateChecksum(const char* data, size_t size) {
            // Simple XOR checksum
            for (size_t i = 0; i < size; ++i) {
                checksum ^= static_cast<uint32_t>(data[i]);
            }
        }
        
        void printProgress() {
            double percent = (file_size > 0) ? (100.0 * bytes_received / file_size) : 0.0;
            std::cout << "Connection " << connection_id << ": "
                      << bytes_received << " / " << file_size << " bytes ("
                      << std::fixed << std::setprecision(1) << percent << "%)\n";
        }
    };
    
public:
    BulkDataServer(uint16_t port) 
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
        // TODO: Implement async_accept
        // - Create connection with next_connection_id_++
        // - Call connection->start()
        // - Recursively call startAccept()
    }
};

// Client would send:
// 1. File size as 8-byte uint64_t (network byte order)
// 2. File data as bytes

int main() {
    try {
        BulkDataServer server(9004);
        std::cout << "Bulk data server listening on port 9004...\n";
        std::cout << "Waiting for file transfers...\n";
        std::cout << "Format: [8-byte size][file data]\n";
        
        // server.run();  // Uncomment to run
        
    } catch (std::exception& e) {
        std::cerr << "Error: " << e.what() << "\n";
    }
    return 0;
}
