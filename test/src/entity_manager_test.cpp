#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <gamenge/ecs/ecs.hpp>
#include <gamenge/ecs/entity_manager.hpp>

using namespace Gamenge;

TEST(EntityManagerTest, construct)
{
    EntityManager entityManager;

    EXPECT_EQ(false, entityManager.isEnabled(12));
}

TEST(EntityManagerTest, addEntity)
{
    EntityManager entity_manager;
    EID eid = entity_manager.addEntity();
    EXPECT_TRUE(eid >= 0);

    EID eid2 = entity_manager.addEntity();
    EXPECT_TRUE(eid2 > 0);
}

TEST(EntityManagerTest, removeEntity)
{
    EntityManager entityManager;

    EID eid = entityManager.addEntity();
    EXPECT_EQ(true, entityManager.isEnabled(eid));

    entityManager.removeEntity(eid);
    EXPECT_EQ(false, entityManager.isEnabled(eid));
}

TEST(EntityManagerTest, addGetMask)
{
    EntityManager entityManager;

    EID eid = entityManager.addEntity();
    Mask mask = 0x01 < 17 | 0x01 < 12 | 0x01 < 3;

    entityManager.addMask(eid, mask);
    EXPECT_TRUE(MaskUtils::matches(0x01 < 17 | 0x01 < 12 | 0x01 < 3, entityManager.getMask(eid)));
    EXPECT_TRUE(MaskUtils::matchesAny(0x01 < 12, entityManager.getMask(eid)));
}

TEST(EntityManagerTest, removeMask)
{
    EntityManager entityManager;
    EID eid = entityManager.addEntity();

    Mask component1 = 0x01 < 2;
    Mask component2 = 0x01 < 17;
    Mask component3 = 0x01 < 18;
    Mask component4 = 0x01 < 32;
    Mask fullMask = component1 | component2 | component3 | component4;

    entityManager.addMask(eid, fullMask);
    EXPECT_TRUE(MaskUtils::matches(fullMask, entityManager.getMask(eid)));
    EXPECT_TRUE(MaskUtils::matchesAny(component1, entityManager.getMask(eid)));
    EXPECT_TRUE(MaskUtils::matchesAny(component2, entityManager.getMask(eid)));
    EXPECT_TRUE(MaskUtils::matchesAny(component3, entityManager.getMask(eid)));
    EXPECT_TRUE(MaskUtils::matchesAny(component4, entityManager.getMask(eid)));

    entityManager.removeMask(eid, component1);
    EXPECT_FALSE(MaskUtils::matches(entityManager.getMask(eid), fullMask));
    EXPECT_FALSE(MaskUtils::matchesAny(component1, entityManager.getMask(eid)));

    entityManager.removeMask(eid, component2);
    EXPECT_FALSE(MaskUtils::matchesAny(component2, entityManager.getMask(eid)));
}