#include <array>
#include <string>
#include <charconv>
#include <sstream>

struct IPv4 {
    std::array<uint8_t, 4> data = {};
};

bool TryFromString(const std::string_view buf, IPv4* ipv4) {
    if (!ipv4) {
        return false;
    }

    for (size_t idx = 0, l = 0; idx < 4; ++idx) {
        size_t r = (idx == 3) ? buf.size() : buf.find('.', l);

        if (r == std::string_view::npos || l == r) {
            return false;
        }

        unsigned int value;
        auto [ptr, ec] = std::from_chars(
            buf.data() + l,
            buf.data() + r,
            value
        );

        if (ec != std::errc{} || ptr != buf.data() + r || value > 255) {
            return false;
        }

        ipv4->data[idx] = static_cast<uint8_t>(value);
        l = r + 1;
    }

    return true;
}

std::string ToString(const IPv4& ipv4) {
    std::ostringstream dst;
   
    dst << static_cast<int>(ipv4.data[0]) <<"."<< static_cast<int>(ipv4.data[1]) <<"."<< static_cast<int>(ipv4.data[2]) <<"."<< static_cast<int>(ipv4.data[3]);

    return dst.str();
} 

int main() {




    return 0;
}