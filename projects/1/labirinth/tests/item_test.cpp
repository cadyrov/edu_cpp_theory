#include "item.hpp"

#include <gtest/gtest.h>

TEST(ItemTest, AddFindInventory) {
    game::Inventory inventory;
    game::Item item(game::ItemType::HEAL, 123, "potion", 10);

    inventory.Add(item);

    auto found = inventory.Find(123);
    ASSERT_TRUE(found.has_value());
    EXPECT_EQ(found->ID(), item.ID());
}

TEST(ItemTest, POPInventory) {
    game::Inventory inventory;
    game::Item item(game::ItemType::HEAL, 123, "potion", 10);

    inventory.Add(item);

    auto pop = inventory.Pop(123);
    ASSERT_TRUE(pop.has_value());

    pop = inventory.Pop(123);
    ASSERT_TRUE(!pop.has_value());
}

TEST(ItemTest, DuplicateInventory) {
    game::Inventory inventory;
    game::Item item(game::ItemType::HEAL, 123, "potion", 10);

    inventory.Add(item);
    EXPECT_THROW(inventory.Add(item), std::runtime_error);
}