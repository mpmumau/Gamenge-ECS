#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <gamenge/common/common.hpp>
#include <gamenge/ecs/ecs_common.hpp>
#include <gamenge/ecs/ecs.hpp>

class ECSFixtureTest : public ::testing::Test {
    protected:
        typedef struct TestComponent1 : Component {
            float x, y, z;
        } TestComponent1;

        typedef struct TestComponent2: Component {
            std::string color;
            unsigned int r;
            unsigned int g;
            unsigned int b;
        } TestComponent2;

        virtual void SetUp()
        {
            eid = ecs.addEntity();

            component1 = new TestComponent1();
            component1->x = 0.123123f;
            component1->y = 1231.123123f;
            component1->z = 8123781623.1231f;

            component2 = new TestComponent2();
            component2->color = "reddish-grey";
            component2->r = 128;
            component2->g = 127;
            component2->b = 126;

            ecs.addComponent(eid, TEST_COMPONENT1_MASK, component1);
            ecs.addComponent(eid, TEST_COMPONENT2_MASK, component2);
        }

        virtual void TearDown() {
            ecs.destroy();
        }

        ECS ecs;
        EID eid;

        Mask TEST_COMPONENT1_MASK = 0x01 << 5;
        Mask TEST_COMPONENT2_MASK = 0x01 << 17;

        TestComponent1 *component1;
        TestComponent2 *component2;
};


TEST(ECSTest, addGetEntity)
{
    ECS ecs;
    EID eid = ecs.addEntity();

    EXPECT_TRUE(-1 != eid);
    EXPECT_EQ(0x00, ecs.getEntity(eid));
    EXPECT_EQ(true, ecs.isEnabled(eid));
}

TEST(ECSTest, removeEntity)
{
    ECS ecs;
    EID eid = ecs.addEntity();
    EXPECT_TRUE(ecs.isEnabled(eid));

    ecs.removeEntity(eid);
    EXPECT_FALSE(ecs.isEnabled(eid));
}

TEST_F(ECSFixtureTest, addGetComponent)
{
    EXPECT_TRUE(NULL != ecs.getComponent(eid, TEST_COMPONENT1_MASK));
}

TEST_F(ECSFixtureTest, removeComponent)
{
    EXPECT_TRUE(NULL != ecs.getComponent(eid, TEST_COMPONENT1_MASK));

    ecs.removeComponent(eid, TEST_COMPONENT1_MASK);
    EXPECT_EQ(NULL, ecs.getComponent(eid, TEST_COMPONENT1_MASK));
}