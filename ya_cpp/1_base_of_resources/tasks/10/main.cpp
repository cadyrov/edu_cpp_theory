#include <iostream>
#include <print>
#include <random>
#include <stdexcept>
#include <string>

void MaybeThrow() {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    static std::uniform_int_distribution<int> dist(0, 1);

    if (dist(gen) == 0) {
        std::println(std::cerr, "Throw an error");
        throw std::runtime_error("Random failure occurred!");
    }
}

struct FinancialOperation {
    std::string name;
};

struct LocalStorage {
    void PushBack(const FinancialOperation &op) {
        std::println("Local push: {}", op.name);
        MaybeThrow();
    }
    void PopBack() noexcept { std::println("Local pop"); }
} localStorage;

struct Database {
    void PushBack(const FinancialOperation &op) {
        std::println("DB push: {}", op.name);
        MaybeThrow();
    }
    void PopBack() noexcept { std::println("DB pop"); }
} db;

struct WebAPI {
    void UpdateCurrentOp(const FinancialOperation &op) {
        std::println("GUI push: {}", op.name);
        MaybeThrow();
    }
} webApi;

void InsertOperation(const FinancialOperation &op) {
    boost::scope::scope_fail fail_report{[] { std::println("InsertOperation failed!"); }};

    localStorage.PushBack(op);

    BOOST_SCOPE_DEFER[&] {
        std::println(std::cerr, "Revert changes in localStorage");
        localStorage.PopBack();
    };

    db.PushBack(op);
    BOOST_SCOPE_DEFER[&] {
        std::println(std::cerr, "Revert changes in db");
        db.PopBack();
    };

    webApi.UpdateCurrentOp(op);
    std::println("Operation inserted successfully!");
}

int main() {
    for (int i = 0; i < 5; ++i) {
        std::println("===== Start new operation =====");
        try {
            InsertOperation({"Pay rent"});
        } catch (...) {
            std::println("Caught an exception");
        }
    }
}