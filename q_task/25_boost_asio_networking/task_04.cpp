// Task 4: UDP Client (Sender)
// Create a UDPSender class that:
// - Sends a datagram to localhost:9001
// - Receives response
// - Prints result
//
// Requirements:
// - Connection-less operation (no connect needed)
// - Correct recipient address specification

#include <boost/asio.hpp>
#include <iostream>
#include <memory>
#include <array>

class UDPSender {
public:
    UDPSender(const std::string& host, uint16_t port) {
        // TODO: Implement
        // 1. Create socket
        // 2. Create resolver if needed (or use direct IP)
        // 3. Send datagram using async_send_to
        // 4. In handler: receive response using async_receive_from
        // 5. Print received data
    }
    
    void run() {
        // TODO: io_context_.run();
    }
    
private:
    boost::asio::io_context io_context_;
    boost::asio::ip::udp::socket socket_{io_context_};
    
    void sendMessage(const std::string& msg, const boost::asio::ip::udp::endpoint& endpoint) {
        // TODO: Implement async_send_to
        // - Send msg to endpoint
        // - In handler: call receiveResponse()
    }
    
    void receiveResponse() {
        // TODO: Implement async_receive_from
        // - Create buffer
        // - Create remote_endpoint
        // - Call async_receive_from
        // - Print received data
    }
};

int main() {
    try {
        UDPSender sender("127.0.0.1", 9001);
        sender.run();
    } catch (std::exception& e) {
        std::cerr << "Error: " << e.what() << "\n";
    }
    return 0;
}
