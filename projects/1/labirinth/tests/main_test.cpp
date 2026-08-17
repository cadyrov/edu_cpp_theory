#include "game.hpp"

#include <gtest/gtest.h>

TEST(GameTest, GameName) {
    ASSERT_EQ(game::game_name(), "labirinth");
}