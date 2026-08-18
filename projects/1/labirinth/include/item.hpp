#pragma once

#include <optional>
#include <string>
#include <vector>

namespace game {
enum ItemType { HEAL, WEAPON, SIGN_FRAGMENT };

class Item {
  public:
    explicit Item(ItemType type, int id, const std::string& name, int value)
        : type_(type), id_(id), name_(name), value_(value) {}

    ItemType Type() const {
        return type_;
    }

    bool operator==(int id) const {
        return id_ == id;
    }

    int ID() const {
        return id_;
    }

    const std::string& Name() const {
        return name_;
    }

    int Value() const {
        return value_;
    }

  private:
    ItemType type_;
    int id_;
    std::string name_;
    int value_;
};

class Inventory {
  public:
    std::optional<Item> Find(int id) const noexcept;
    void Add(Item);
    std::optional<Item> Pop(int id);

  private:
    std::vector<Item> data_;
};
} // namespace game