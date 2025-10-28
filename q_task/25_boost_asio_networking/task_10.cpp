// Task 10: Asynchronous DNS Resolution
// Create a DNSResolver class that:
// - Asynchronously resolves hostnames (google.com, github.com, etc.)
// - Prints all IP addresses (IPv4 and IPv6)
// - Does not block the event loop
// - Handles resolution errors
//
// Requirements:
// - async_resolve instead of sync resolve
// - Work with tcp::resolver
// - Iterate over results
// - Handle resolution errors

#include <boost/asio.hpp>
#include <iostream>
#include <vector>
#include <string>

class DNSResolver {
public:
    DNSResolver() : resolver_(io_context_) {}
    
    void resolveAsync(const std::string& hostname) {
        // TODO: Implement
        // 1. Create tcp::query with hostname
        // 2. Call resolver_.async_resolve(query, handler)
        // 3. In handler:
        //    - Check error_code
        //    - If OK: iterate through results and print each address
        //    - On error: print error message
    }
    
    void run() {
        // TODO: io_context_.run();
    }
    
    void resolveMultiple(const std::vector<std::string>& hostnames) {
        // TODO: Resolve multiple hostnames in parallel
        // - Each resolveAsync call is independent
        // - All execute "concurrently" in event loop
        for (const auto& hostname : hostnames) {
            resolveAsync(hostname);
        }
    }
    
private:
    boost::asio::io_context io_context_;
    boost::asio::ip::tcp::resolver resolver_;
    
    void printResults(const std::string& hostname, 
                     const boost::asio::ip::tcp::resolver::results_type& results) {
        // TODO: Iterate through results and print
        // - Print hostname
        // - For each result: print protocol (v4/v6) and address
        // Example output:
        //   google.com:
        //     IPv4: 142.251.32.46
        //     IPv6: 2607:f8b0:4004:80b::200e
    }
};

int main() {
    try {
        DNSResolver resolver;
        
        // Resolve single hostname
        std::cout << "Resolving google.com...\n";
        resolver.resolveAsync("google.com");
        
        // Or resolve multiple in parallel
        std::cout << "\nResolving multiple hosts...\n";
        resolver.resolveMultiple({
            "github.com",
            "example.com",
            "stackoverflow.com",
            "nonexistent-host-123456.invalid"  // Will fail
        });
        
        resolver.run();
        
    } catch (std::exception& e) {
        std::cerr << "Error: " << e.what() << "\n";
    }
    return 0;
}
