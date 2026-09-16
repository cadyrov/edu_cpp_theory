#pragma once

#include <iostream>
#include <memory>
#include <string>
#include <string_view>

class Widget {
  public:
    Widget();
    ~Widget();

    Widget(const Widget&) = delete;
    Widget(Widget&&) = delete;
    Widget& operator=(const Widget&) = delete;
    Widget& operator=(Widget&&) = delete;

    void SetTitle(std::string_view title);
    std::string Title() const;
    void Print(std::ostream& os = std::cout) const;

  private:
    struct Impl;
    std::unique_ptr<Impl> impl_;
};