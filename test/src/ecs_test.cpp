#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <gamenge/ecs/ecs_common.hpp>
#include <gamenge/ecs/ecs.hpp>

#define TEST_COMPONENT1_MASK 0x01 << 5
#define TEST_COMPONENT2_MASK 0x01 << 17

using namespace Gamenge;

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

        class TestSystem : public System {
        public:
            TestSystem() : System(Mask(0x01), 1, true) {};
            void tick(Nanos delta, EID eid, ComponentBundle componentBundle) {};
        };

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
        }

        virtual void TearDown() {
            ecs.destroy();
        }

        ECS ecs;
        EID eid;

        TestComponent1 *component1;
        TestComponent2 *component2;
};


TEST(ECSTest, addGetEntity)
{
    ECS ecs;
    EID eid = ecs.addEntity();

    EXPECT_TRUE(0 <= eid);
    EXPECT_EQ(Mask(0x00), ecs.getEntity(eid));
    EXPECT_TRUE(ecs.isEnabled(eid));
}

TEST(ECSTest, removeEntity)
{
    ECS ecs;
    EID eid = ecs.addEntity();
    EXPECT_EQ(Mask(0x00), ecs.getEntity(eid));
    EXPECT_TRUE(ecs.isEnabled(eid));

    ecs.removeEntity(eid);
    EXPECT_EQ(Mask(0x00), ecs.getEntity(eid));
    EXPECT_FALSE(ecs.isEnabled(eid));
}

TEST_F(ECSFixtureTest, addGetComponent)
{
    ecs.addComponent(eid, Mask(TEST_COMPONENT1_MASK), component1);
    ecs.addComponent(eid, Mask(TEST_COMPONENT2_MASK), component2);

    EXPECT_TRUE(NULL != ecs.getComponent(eid, Mask(TEST_COMPONENT1_MASK)));
    EXPECT_TRUE(NULL != ecs.getComponent(eid, Mask(TEST_COMPONENT2_MASK)));
}

TEST_F(ECSFixtureTest, removeComponent)
{
    ecs.addComponent(eid, Mask(TEST_COMPONENT1_MASK), component1);
    ecs.addComponent(eid, Mask(TEST_COMPONENT2_MASK), component2);

    EXPECT_TRUE(NULL != ecs.getComponent(eid, Mask(TEST_COMPONENT1_MASK)));
    ecs.removeComponent(eid, Mask(TEST_COMPONENT1_MASK));
    EXPECT_EQ(NULL, ecs.getComponent(eid, Mask(TEST_COMPONENT1_MASK)));

    EXPECT_TRUE(NULL != ecs.getComponent(eid, Mask(TEST_COMPONENT2_MASK)));
    ecs.removeComponent(eid, Mask(TEST_COMPONENT2_MASK));
    EXPECT_EQ(NULL, ecs.getComponent(eid, Mask(TEST_COMPONENT2_MASK)));
}