#pragma once

#include "item.hpp"

#include <memory>
#include <string>
#include <string_view>
#include <utility>
#include <vector>

namespace game {
enum Direction { UNKNOWN, NORTH, SOUTH, WEST, EAST };

inline Direction StringToDirection(std::string_view value) {
    if (value == "north") {
        return NORTH;
    } else if (value == "south") {
        return SOUTH;
    } else if (value == "west") {
        return WEST;
    } else if (value == "east") {
        return EAST;
    } else {
        return UNKNOWN;
    }
}

class Exit {
  public:
    Direction direction;
    int room_id;
};

using Exits = std::vector<Exit>;
// идентификатор, название, описание, предметы и выходы.
class Room {
    friend class World;

  public:
    explicit Room(int id, std::string name, std::string description)
        : id_(id), name_(std::move(name)), description_(std::move(description)) {}

    int ID() const {
        return id_;
    }

    const std::string& Name() const {
        return name_;
    }

    const std::string& Description() const {
        return description_;
    }

    void AddItem(Item item);
    const Items& GetItems() const;
    Items& GetItems();
    const Exits& GetExits() const;

  private:
    int id_;
    std::string name_;
    std::string description_;
    Items items_;
    Exits exits_;
    void AddExit(Direction, int);
};

using Rooms = std::vector<std::unique_ptr<Room>>;

class World {
  public:
    void AddRoom(Room&& room);
    Room* FindRoom(int id) noexcept;
    const Room* FindRoom(int id) const noexcept;
    void ConnectRooms(Direction direction, int from, int to);

  private:
    Rooms rooms_;
};

} // namespace game