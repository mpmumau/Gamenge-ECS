#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <gamenge/ecs/ecs.hpp>
#include <gamenge/ecs/entity_manager.hpp>

using namespace Gamenge;

TEST(EntityManagerTest, Construct)
{
    EntityManager entityManager;

    Entity entity = entityManager.getEntity(12);
    EXPECT_EQ(false, entity.enabled);
}

TEST(EntityManagerTest, AddEntity)
{
    EntityManager entity_manager;
    EID eid = entity_manager.addEntity();
    EXPECT_TRUE(eid >= 0);

    EID eid2 = entity_manager.addEntity();
    EXPECT_TRUE(eid2 > 0);
}

TEST(EntityManagerTest, GetEntity)
{
    EntityManager entityManager;

    Entity noEntity = entityManager.getEntity(0);
    EXPECT_EQ(false, noEntity.enabled);

    EID eid = entityManager.addEntity();
    Entity entity = entityManager.getEntity(eid);
    //EXPECT_EQ(true, entity.enabled);
}