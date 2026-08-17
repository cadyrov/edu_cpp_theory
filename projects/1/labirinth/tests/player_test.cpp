#include "player.hpp"

#include <gtest/gtest.h>

TEST(PlayerTest, Create) {
    EXPECT_THROW(game::Player(""), std::invalid_argument);
    EXPECT_THROW(game::Player("   "), std::invalid_argument);
    EXPECT_NO_THROW(game::Player("   1"));

    ASSERT_EQ(game::Player("dddd").GetName(), "dddd");
    ASSERT_EQ(game::Player(" dddd ").GetName(), "dddd");
    ASSERT_EQ(game::Player("dddd").GetAttackPower(), 1);
    ASSERT_EQ(game::Player("dddd").GetMaxHP(), 10);
    ASSERT_EQ(game::Player("dddd").GetHP(), 10);
}

TEST(PlayerTest, Damage) {
    game::Player p("name");

    p.Damage(-1);
    ASSERT_EQ(p.GetHP(), 10);
    ASSERT_EQ(p.GetMaxHP(), 10);

    p.Damage(1);
    ASSERT_EQ(p.GetHP(), 9);
    ASSERT_EQ(p.GetMaxHP(), 10);

    p.Damage(100);
    ASSERT_EQ(p.GetHP(), 0);
    ASSERT_EQ(p.GetMaxHP(), 10);
}

TEST(PlayerTest, Heal) {
    game::Player p("name");

    p.Damage(9);
    ASSERT_EQ(p.GetHP(), 1);
    ASSERT_EQ(p.GetMaxHP(), 10);

    p.Heal(-3);
    ASSERT_EQ(p.GetHP(), 1);
    ASSERT_EQ(p.GetMaxHP(), 10);

    p.Heal(3);
    ASSERT_EQ(p.GetHP(), 4);
    ASSERT_EQ(p.GetMaxHP(), 10);

    p.Heal(10);
    ASSERT_EQ(p.GetHP(), 10);
    ASSERT_EQ(p.GetMaxHP(), 10);
}