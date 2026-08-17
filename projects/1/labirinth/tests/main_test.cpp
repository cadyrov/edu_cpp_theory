#include <gtest/gtest.h>
#include <game.hpp>

TEST(GameTest, GameName) {
    ASSERT_EQ(game::game_name(), "labirinth");
}