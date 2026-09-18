#include "file_writer.h"

#include <cstdio>
#include <memory>
#include <stdexcept>
#include <string>
#include <utility>

struct FileWriter::Impl {
    Impl() = default;
    ~Impl() {
        try {
            close();
        } catch (...) {
        }
    };

    void open(const std::string& path) {
        if (is_open()) {
            throw std::runtime_error("уже открыт");
        }

        res = fopen(path.c_str(), "a");

        if (!res) {
            throw std::runtime_error("Ошибка открытия файла");
        }
    };
    void close() {
        if (!res) {
            return;
        }

        FILE* file = std::exchange(res, nullptr);
        if (std::fclose(file) != 0) {
            throw std::runtime_error("Ошибка закрытия файла");
        }
    };
    bool is_open() const {
        return res != nullptr;
    };
    // не дописывает переносов
    void append(const std::string& in) {
        if (!is_open()) {
            throw std::runtime_error("не открыт");
        }

        if (std::fwrite(in.data(), 1, in.size(), res) != in.size()) {
            throw std::runtime_error("Ошибка записи");
        }
    };

    FILE* res = nullptr;
};

FileWriter::FileWriter() : impl_(std::make_unique<Impl>()) {};
FileWriter::~FileWriter() = default;

FileWriter::FileWriter(FileWriter&& other) noexcept {
    impl_ = std::move(other.impl_);
};

FileWriter& FileWriter::operator=(FileWriter&& other) noexcept {
    if (this == &other) {
        return *this;
    }

    impl_ = std::move(other.impl_);

    return *this;
}

void FileWriter::open(const std::string& path) {
    if (impl_ == nullptr) {
        throw std::runtime_error("empty resourse");
    }

    impl_.get()->open(path);
}

void FileWriter::close() {
    if (impl_ == nullptr) {
        throw std::runtime_error("empty resourse");
    }

    impl_.get()->close();
}

bool FileWriter::is_open() const {
    if (impl_ == nullptr) {
        throw std::runtime_error("empty resourse");
    }

    return impl_.get()->is_open();
}

void FileWriter::append(const std::string& data) {
    if (impl_ == nullptr) {
        throw std::runtime_error("empty resourse");
    }

    impl_.get()->append(data);
}