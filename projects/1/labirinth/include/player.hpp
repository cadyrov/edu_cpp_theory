#pragma once

#include "item.hpp"
#include "utils.hpp"

#include <stdexcept>
#include <string>

namespace game {
class Player {
  public:
    explicit Player(std::string_view name) {
        name_ = utils::ltrim(utils::rtrim(name));

        if (name_.empty()) {
            throw std::invalid_argument("Ошибка: имя пустое или содержит только пробелы!");
        }
    }

    void Damage(int val) {
        if (val < 0) {
            return;
        }

        hp_ -= val;

        if (hp_ < 0) {
            hp_ = 0;
        }
    }

    void Heal(int val) {
        if (val < 0) {
            return;
        }

        hp_ += val;
        if (hp_ > max_hp_) {
            hp_ = max_hp_;
        }
    }

    const std::string& GetName() const {
        return name_;
    }

    int GetHP() const {
        return hp_;
    }

    int GetMaxHP() const {
        return max_hp_;
    }

    int GetAttackPower() const {
        return atk_pwr_;
    }

    Inventory& GetInventory() noexcept {
        return inventory_;
    }

    const Inventory& GetInventory() const noexcept {
        return inventory_;
    }

  private:
    std::string name_;
    int hp_ = 10;
    int max_hp_ = 10;
    int atk_pwr_ = 1;
    Inventory inventory_;
};
} // namespace game