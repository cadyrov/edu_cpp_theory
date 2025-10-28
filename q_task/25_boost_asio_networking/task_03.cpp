// Task 3: UDP Server (Receiver)
// Create a UDPReceiver class that:
// - Listens on port 9001 via UDP
// - Receives datagrams from clients
// - Sends response back to sender's address
// - Asynchronously handles multiple senders
//
// Requirements:
// - async_receive_from to receive
// - async_send_to to send response
// - Remember sender's address
// - Correct buffer lifetime

#include <boost/asio.hpp>
#include <iostream>
#include <memory>
#include <array>

class UDPReceiver {
public:
    UDPReceiver(uint16_t port) 
        : socket_(io_context_,
                  boost::asio::ip::udp::endpoint(boost::asio::ip::udp::v4(), port)) {
        // TODO: Call startReceive()
    }
    
    void run() {
        // TODO: io_context_.run();
    }
    
private:
    boost::asio::io_context io_context_;
    boost::asio::ip::udp::socket socket_;
    
    void startReceive() {
        // TODO: Implement async_receive_from
        // - Create buffer with make_shared<std::array<char, 1024>>
        // - Create remote_endpoint
        // - Call socket_.async_receive_from
        // - In handler: 
        //   - Send response back using async_send_to
        //   - Recursively call startReceive() to listen for more
    }
};

int main() {
    try {
        UDPReceiver receiver(9001);
        std::cout << "UDP receiver listening on port 9001...\n";
        receiver.run();
    } catch (std::exception& e) {
        std::cerr << "Error: " << e.what() << "\n";
    }
    return 0;
}
