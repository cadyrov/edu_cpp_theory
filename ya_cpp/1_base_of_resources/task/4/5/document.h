#pragma once

#include <cstddef>
#include <experimental/propagate_const>
#include <iostream>
#include <memory>
#include <string>

class Document {
  public:
    Document();
    ~Document();

    Document(const Document&);
    Document& operator=(const Document&);

    Document(Document&&);
    Document& operator=(Document&&);

    void AddLine(const std::string&);
    const std::string& operator[](size_t n) const;
    size_t size() const;
    friend std::ostream& operator<<(std::ostream& os, const Document& doc);

  private:
    struct Impl;
    std::experimental::propagate_const<std::unique_ptr<Impl>> impl_;
};