#pragma once

#include <experimental/propagate_const>
#include <memory>

class Counter {
  public:
    Counter();
    ~Counter();

    Counter(const Counter&) = delete;
    Counter& operator=(const Counter&) = delete;
    Counter(Counter&&) = delete;
    Counter& operator=(Counter&&) = delete;

    void increment();
    void reset();
    int value() const;

  private:
    struct Impl;
    std::experimental::propagate_const<std::unique_ptr<Impl>> impl_;
};