#include "item.hpp"

#include <algorithm>
#include <optional>
#include <stdexcept>
#include <string>
#include <utility>

namespace game {

std::optional<game::Item> game::Inventory::Find(int id) const noexcept {
    auto it = std::find(data_.begin(), data_.end(), id);
    if (it == data_.end()) {
        return std::nullopt;
    }

    return *it;
};

void game::Inventory::Add(game::Item item) {
    auto it = std::find(data_.begin(), data_.end(), item.ID());
    if (it != data_.end()) {
        throw std::runtime_error("try to create duplicate");
    }

    data_.push_back(std::move(item));
};

std::optional<game::Item> game::Inventory::Pop(int id) {
    auto it = std::find(data_.begin(), data_.end(), id);
    if (it == data_.end()) {
        return std::nullopt;
    }

    game::Item result = std::move(*it);

    data_.erase(it);

    return result;
}

} // namespace game