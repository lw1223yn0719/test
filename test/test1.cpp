#include <gtest/gtest.h>
#include "manager.hpp"

TEST(ManagerTest, test1)
{
    Elevator e(10, 800, ALL);
    e.wattings.push_back(Passager(1, 10, 50));
    e.loadPassager();
    EXPECT_EQ(e.passagers.size(), 1);
    EXPECT_EQ(e.wattings.size(), 0);
}

TEST(ManagerTest, test2)
{
    Elevator e(10, 800, ALL);
    for(int i = 0; i < 10; i++)
    {
        e.wattings.push_back(Passager(1, 10, 50));
    }
    e.loadPassager();
    EXPECT_EQ(e.passagers.size(), 10);
    EXPECT_EQ(e.wattings.size(), 0);
}

TEST(ManagerTest, test3)
{
    Elevator e(10, 800, ALL);
    for(int i = 0; i < 20; i++)
    {
        e.wattings.push_back(Passager(1, 10, 50));
    }
    e.loadPassager();
    EXPECT_EQ(e.passagers.size(), 10);
    EXPECT_EQ(e.wattings.size(), 10);
}

TEST(ManagerTest, test4)
{
    Elevator e(10, 800, ALL);
    for(int i = 0; i < 20; i++)
    {
        e.wattings.push_back(Passager(1, 1, 50));
    }
    e.loadPassager();
    e.unloadPassager();
    EXPECT_EQ(e.passagers.size(), 0);
    EXPECT_EQ(e.wattings.size(), 0);
}