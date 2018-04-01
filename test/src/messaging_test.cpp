#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <vector>
#include <string>
#include <gamenge/ecs/ecs_common.hpp>
#include <gamenge/ecs/ecs.hpp>

#define TRANSFORM_COMPONENT_MASK 0x01 << 14

class MessagingFixtureTest : public ::testing::Test {
    protected:
        enum MessageType {
            KILL_MESSAGE,
            DATA_MESSAGE
        };

        typedef struct TransformComponent : public Component {
            float x, y, z;
        } TransformComponent;

        typedef struct KillMessage : public Message {
            KillMessage(EID target) : Message(target, KILL_MESSAGE) {};
            std::string message;
        } KillMessage;

        typedef struct DataMessage : public Message {
            DataMessage(EID target) : Message(target, DATA_MESSAGE) {};
            unsigned int data;
        } DataMessage;

        class MessagingSystem : public System {
        public:
            MessagingSystem() : System(Mask(TRANSFORM_COMPONENT_MASK), 1, true) {};

            void tick(Nanos delta, EID eid, ComponentBundle componentBundle) {
                MessagingComponent *messagingComponent = dynamic_cast<MessagingComponent *>(componentBundle.at(Mask(0x00)));

                std::vector<KillMessage *> killMessages;
                std::vector<DataMessage *> dataMessages;

                for (auto it = messagingComponent->messages.begin(); it != messagingComponent->messages.end(); ++it) {
                    if (((Message *) *it)->type == KILL_MESSAGE) {
                        killMessages.push_back(dynamic_cast<KillMessage *>(*it));
                    }

                    if (((Message *) *it)->type == DATA_MESSAGE) {
                        dataMessages.push_back(dynamic_cast<DataMessage *>(*it));
                    }
                }

                for (auto it = killMessages.begin(); it != killMessages.end(); ++it) {
                    masterString += ((KillMessage *) *it)->message;
                }

                for (auto it = dataMessages.begin(); it != dataMessages.end(); ++it) {
                    masterData += ((DataMessage *) *it)->data;
                }
            }

            std::string getMasterString() { return masterString; };
            unsigned int getMasterData() { return masterData; }
        private:
            std::string masterString = "";
            unsigned int masterData = 0;
        };

        virtual void SetUp()
        {
            entity1 = ecs.addEntity();
            entity2 = ecs.addEntity();

            ecs.addComponent(entity1, Mask(TRANSFORM_COMPONENT_MASK), new TransformComponent());
            ecs.addComponent(entity2, Mask(TRANSFORM_COMPONENT_MASK), new TransformComponent());

            messagingSystem = new MessagingSystem();
            ecs.addSystem(messagingSystem);
        }

        virtual void TearDown()
        {
            ecs.destroy();
        }

        ECS ecs;
        EID entity1, entity2;
        MessagingSystem *messagingSystem;
};

TEST_F(MessagingFixtureTest, aTest)
{
    KillMessage *killMessage1 = new KillMessage(entity1);
    killMessage1->message = "abc";

    KillMessage *killMessage2 = new KillMessage(entity2);
    killMessage2->message = "xyz";

    ecs.sendMessage(killMessage1);
    ecs.sendMessage(killMessage2);

    ecs.tick(1234);

    EXPECT_EQ("abcxyz", messagingSystem->getMasterString());
    EXPECT_EQ(0, messagingSystem->getMasterData());

    DataMessage *dataMessage1 = new DataMessage(entity1);
    dataMessage1->data = 12;

    DataMessage *dataMessage2 = new DataMessage(entity2);
    dataMessage2->data = 15;

    ecs.sendMessage(dataMessage1);
    ecs.sendMessage(dataMessage2);

    ecs.tick(1234);

    EXPECT_EQ(27, messagingSystem->getMasterData());
}