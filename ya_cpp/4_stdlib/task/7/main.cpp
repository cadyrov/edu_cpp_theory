#include <string>
#include <optional>
#include <cassert>
#include <iostream>

struct User {
    std::string name;
};

enum class OrderBy {
    Age = 1,
    Weight = 2,
};

std::string to_string(OrderBy orderBy) {
    switch(orderBy) {
        case OrderBy::Age:
            return "Age";
        case OrderBy::Weight:
            return "Weight";
    }
}

struct Query {
    User user;
    std::optional<OrderBy> orderBy;
};

std::string Serialize(const Query& query) {
    std::string result;
    result.reserve(100);
    
    result += "SELECT * FROM Users WHERE Name == \""+query.user.name+"\"";
    
    if (query.orderBy != std::nullopt) {
        result += " ORDER BY " + to_string(query.orderBy.value());
    }

    return result+= ";";
}


extern "C" void c_log(const char* c_str) {
  printf("%lld | %5d: %s\n", (long long)time(NULL), strlen(c_str), c_str);
}


int main() {
    assert(Serialize({{"Mary"}, {}}) == "SELECT * FROM Users WHERE Name == \"Mary\";");
    assert(Serialize({{"John"}, {OrderBy::Age}}) == "SELECT * FROM Users WHERE Name == \"John\" ORDER BY Age;");


    std::string data;

    for (;std::cin >> data;) {
        c_log(data.c_str());
    }

    return 0;
} 