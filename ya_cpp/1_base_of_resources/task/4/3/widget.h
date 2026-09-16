#pragma once

#include <iostream>
#include <memory>
#include <string>
#include <string_view>

class Widget {
  public:
    Widget();
    ~Widget();

    Widget(const Widget&);
    Widget(Widget&&) noexcept;
    Widget& operator=(const Widget&);
    Widget& operator=(Widget&&) noexcept;

    void SetTitle(std::string_view title);
    std::string Title() const;
    void Print(std::ostream& os = std::cout) const;
    bool empty() const;

  private:
    struct Impl;
    std::unique_ptr<Impl> impl_;
};