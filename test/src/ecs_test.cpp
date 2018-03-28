#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <gamenge/ecs/ecs.hpp>

TEST(ECSTest, AddEntity)
{
    Gamenge::ECS ecs;

    EXPECT_TRUE(-1 != ecs.addEntity());
}