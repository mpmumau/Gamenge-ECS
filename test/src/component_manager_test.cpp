#include <string>
#include <stdio.h>
#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <gamenge/ecs/ecs.hpp>
#include <gamenge/ecs/component_manager.hpp>

using namespace Gamenge;

typedef struct TestComponent1 : Component {
    float x, y, z;
} TestComponent1;

typedef struct TestComponent2: Component {
    std::string color;
    unsigned int r;
    unsigned int g;
    unsigned int b;
} TestComponent2;

Mask TEST_COMPONENT1_MASK = 0x01 << 5;
Mask TEST_COMPONENT2_MASK = 0x01 << 17;

class ComponentManagerTest : public ::testing::Test {
    protected:
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
            componentManager.destroy();
        }

        ECS ecs;
        EID eid;
        ComponentManager componentManager;
        TestComponent1 *component1;
        TestComponent2 *component2;
};

TEST_F(ComponentManagerTest, AddGetComponent)
{
    componentManager.addComponent(eid, TEST_COMPONENT1_MASK, component1);
    componentManager.addComponent(eid, TEST_COMPONENT2_MASK, component2);

    TestComponent1 *returnedComponent1 = dynamic_cast<TestComponent1 *> (componentManager.getComponent(eid, TEST_COMPONENT1_MASK));
    TestComponent2 *returnedComponent2 = dynamic_cast<TestComponent2 *> (componentManager.getComponent(eid, TEST_COMPONENT2_MASK));

    EXPECT_EQ(0.123123f, returnedComponent1->x);
    EXPECT_EQ(1231.123123f, returnedComponent1->y);
    EXPECT_EQ(8123781623.1231f, returnedComponent1->z);

    EXPECT_EQ("reddish-grey", returnedComponent2->color);
    EXPECT_EQ(128, returnedComponent2->r);
    EXPECT_EQ(127, returnedComponent2->g);
    EXPECT_EQ(126, returnedComponent2->b);

    EXPECT_EQ(NULL, componentManager.getComponent(52, TEST_COMPONENT2_MASK));
}

TEST_F(ComponentManagerTest, RemoveComponent)
{
    TestComponent1 *component;

    componentManager.addComponent(eid, TEST_COMPONENT1_MASK, component1);
    TestComponent1 *returnedComponent = dynamic_cast<TestComponent1 *> (componentManager.getComponent(eid, TEST_COMPONENT1_MASK));

    EXPECT_FALSE(NULL == returnedComponent);

    componentManager.removeComponent(eid, TEST_COMPONENT1_MASK);
    EXPECT_EQ(NULL, componentManager.getComponent(eid, TEST_COMPONENT2_MASK));
}

TEST_F(ComponentManagerTest, GetComponentBundle)
{
    componentManager.addComponent(eid, TEST_COMPONENT1_MASK, component1);
    componentManager.addComponent(eid, TEST_COMPONENT2_MASK, component2);

    Mask componentBundle1Mask = TEST_COMPONENT1_MASK;
    ComponentBundle componentBundle1 = componentManager.getComponentBundle(eid, componentBundle1Mask);

    TestComponent1 *returnedComponent1 = dynamic_cast<TestComponent1 *> (componentBundle1.at(TEST_COMPONENT1_MASK));
    EXPECT_EQ(0.123123f, returnedComponent1->x);
    EXPECT_EQ(1231.123123f, returnedComponent1->y);
    EXPECT_EQ(8123781623.1231f, returnedComponent1->z);

    Mask componentBundle2Mask = TEST_COMPONENT1_MASK | TEST_COMPONENT2_MASK;
    ComponentBundle componentBundle2 = componentManager.getComponentBundle(eid, componentBundle2Mask);

    returnedComponent1 = dynamic_cast<TestComponent1 *> (componentBundle2.at(TEST_COMPONENT1_MASK));
    EXPECT_EQ(0.123123f, returnedComponent1->x);
    EXPECT_EQ(1231.123123f, returnedComponent1->y);
    EXPECT_EQ(8123781623.1231f, returnedComponent1->z);

    TestComponent2 *returnedComponent2 = dynamic_cast<TestComponent2 *> (componentBundle2.at(TEST_COMPONENT2_MASK));
    EXPECT_EQ("reddish-grey", returnedComponent2->color);
    EXPECT_EQ(128, returnedComponent2->r);
    EXPECT_EQ(127, returnedComponent2->g);
    EXPECT_EQ(126, returnedComponent2->b);
}