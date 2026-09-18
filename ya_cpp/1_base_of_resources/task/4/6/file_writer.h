#pragma once

#include <experimental/propagate_const>
#include <memory>
#include <string>

class FileWriter {
  public:
    FileWriter();
    ~FileWriter();

    FileWriter(const FileWriter&) = delete;
    FileWriter& operator=(const FileWriter&) = delete;

    FileWriter(FileWriter&&) noexcept;
    FileWriter& operator=(FileWriter&&) noexcept;

    void open(const std::string& path);
    void close();
    bool is_open() const;
    // не дописывает переносов
    void append(const std::string&);

  private:
    struct Impl;
    std::experimental::propagate_const<std::unique_ptr<Impl>> impl_;
};