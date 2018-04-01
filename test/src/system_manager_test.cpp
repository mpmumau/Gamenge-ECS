#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <string>
#include <gamenge/common/common.hpp>
#include <gamenge/ecs/ecs_common.hpp>
#include <gamenge/ecs/ecs.hpp>
#include <gamenge/ecs/entity_manager.hpp>
#include <gamenge/ecs/component_manager.hpp>
#include <gamenge/ecs/system_manager.hpp>

#define TEST_COMPONENT_1 0x01 << 5
#define TEST_COMPONENT_2 0x01 << 16

using namespace Gamenge;

class SystemManagerFixtureTest : public ::testing::Test {
protected:
    class PositionSystem : public System {
    public:
        PositionSystem() : System(Mask(TEST_COMPONENT_1), 1) {};
        unsigned short getTimesTicked() { return timesTicked; };
        unsigned short getMasterSum() { return masterSum; };
        void tick(Nanos delta, EID eid, ComponentBundle componentBundle)
        {
            TestComponent1 *testComponent1 = dynamic_cast<TestComponent1 *>(componentBundle[Mask(TEST_COMPONENT_1)]);
            masterSum += testComponent1->v1;
            masterSum += testComponent1->v2;

            timesTicked++;
        }
    private:
        unsigned short timesTicked = 0;
        unsigned short masterSum = 0;
    };

    class OtherSystem : public System {
    public:
        OtherSystem() : System(Mask(TEST_COMPONENT_1) | Mask(TEST_COMPONENT_2), 2) {};
        unsigned int getRunningTally() { return runningTally; };
        void tick(Nanos delta, EID eid, ComponentBundle componentBundle)
        {
            TestComponent1 *testComponent1 = dynamic_cast<TestComponent1 *>(componentBundle[TEST_COMPONENT_1]);
            TestComponent2 *testComponent2 = dynamic_cast<TestComponent2 *>(componentBundle[TEST_COMPONENT_2]);

            runningTally += (testComponent1->v1 * testComponent2->multiplier1) + (testComponent1->v2 * testComponent2->multiplier2);
        }
    private:
        unsigned int runningTally = 0;
    };

    typedef struct TestComponent1 : Component {
        unsigned int v1 = 1;
        unsigned int v2 = 2;
    } TestComponent1;

    typedef struct TestComponent2 : Component {
        unsigned int multiplier1 = 5;
        unsigned int multiplier2 = 10;
    } TestComponent2;

    SystemManager systemManager;

    virtual void TearDown() {
        systemManager.destroy();
    }
};

TEST_F(SystemManagerFixtureTest, addSystem)
{
    OtherSystem *otherSystem = new OtherSystem();
    systemManager.addSystem(otherSystem);

    PositionSystem *positionSystem = new PositionSystem();
    systemManager.addSystem(positionSystem);

    EXPECT_EQ(2, systemManager.getNumSystems());
}

TEST_F(SystemManagerFixtureTest, removeSystem)
{
    OtherSystem *otherSystem = new OtherSystem();
    systemManager.addSystem(otherSystem);

    PositionSystem *positionSystem = new PositionSystem();
    systemManager.addSystem(positionSystem);

    EXPECT_EQ(2, systemManager.getNumSystems());

    systemManager.removeSystem(otherSystem->getMask());
    EXPECT_EQ(1, systemManager.getNumSystems());

    systemManager.removeSystem(positionSystem->getMask());
    EXPECT_EQ(0, systemManager.getNumSystems());
}

TEST_F(SystemManagerFixtureTest, tick)
{
    EntityManager entityManager;
    ComponentManager componentManager;

    EID eid = entityManager.addEntity();

    TestComponent1 *testComponent1 = new TestComponent1();
    entityManager.addMask(eid, Mask(TEST_COMPONENT_1));
    componentManager.addComponent(eid, Mask(TEST_COMPONENT_1), testComponent1);

    TestComponent2 *testComponent2 = new TestComponent2();
    entityManager.addMask(eid, Mask(TEST_COMPONENT_2));
    componentManager.addComponent(eid, Mask(TEST_COMPONENT_2), testComponent2);

    PositionSystem *positionSystem = new PositionSystem();
    OtherSystem *otherSystem = new OtherSystem();

    systemManager.addSystem(positionSystem);
    systemManager.addSystem(otherSystem);

    systemManager.tick(1234, &entityManager, &componentManager);
    systemManager.tick(1235, &entityManager, &componentManager);
    systemManager.tick(1236, &entityManager, &componentManager);

    EXPECT_EQ(3, positionSystem->getTimesTicked());
    EXPECT_EQ(9, positionSystem->getMasterSum());
    EXPECT_EQ(75, otherSystem->getRunningTally());

    componentManager.destroy();
}