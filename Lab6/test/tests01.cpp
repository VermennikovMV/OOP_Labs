#include <gtest/gtest.h>
#include "../include/NPC.h"
#include "../include/Ork.h"
#include "../include/Squirrel.h"
#include "../include/Bear.h"
#include "../include/Factory.h"
#include "../include/Observer.h"
#include "../include/Visitors.h"
#include "../include/Game_functions.h"

static int CountDead(const std::vector<std::unique_ptr<NPC>>& npcs) {
    int count=0;
    for(auto& n:npcs) if(!n->IsAlive()) count++;
    return count;
}

TEST(test_01, basic_test_set) {
    Subject subject;
    ConsoleObserver consoleObs;
    LogObserver logObs;
    subject.Attach(&consoleObs);
    subject.Attach(&logObs);
    std::vector<std::unique_ptr<NPC>> npcs;
    npcs.push_back(Factory::Create("Ork","O1",0,0));
    npcs.push_back(Factory::Create("Bear","B1",100,100));
    Battle(npcs,10,subject);
    ASSERT_TRUE(CountDead(npcs) == 0);
}

TEST(test_02, basic_test_set) {
    Subject subject;
    ConsoleObserver consoleObs;
    LogObserver logObs;
    subject.Attach(&consoleObs);
    subject.Attach(&logObs);
    std::vector<std::unique_ptr<NPC>> npcs;
    npcs.push_back(Factory::Create("Ork","O1",0,0));
    npcs.push_back(Factory::Create("Bear","B1",1,1));
    Battle(npcs,100,subject);
    ASSERT_TRUE(CountDead(npcs) == 1);
}

TEST(test_03, basic_test_set) {
    Subject subject;
    ConsoleObserver consoleObs;
    LogObserver logObs;
    subject.Attach(&consoleObs);
    subject.Attach(&logObs);
    std::vector<std::unique_ptr<NPC>> npcs;
    npcs.push_back(Factory::Create("Bear","Br1",0,0));
    npcs.push_back(Factory::Create("Squirrel","S1",1,1));
    Battle(npcs,100,subject);
    ASSERT_TRUE(CountDead(npcs) == 1);
}

TEST(test_04, basic_test_set) {
    Subject subject;
    ConsoleObserver consoleObs;
    LogObserver logObs;
    subject.Attach(&consoleObs);
    subject.Attach(&logObs);
    std::vector<std::unique_ptr<NPC>> npcs;
    npcs.push_back(Factory::Create("Squirrel","S1",0,0));
    npcs.push_back(Factory::Create("Squirrel","S2",1,1));
    Battle(npcs,100,subject);
    ASSERT_TRUE(CountDead(npcs) == 0);
}

TEST(test_05, basic_test_set) {
    Subject subject;
    ConsoleObserver consoleObs;
    LogObserver logObs;
    subject.Attach(&consoleObs);
    subject.Attach(&logObs);
    std::vector<std::unique_ptr<NPC>> npcs;
    npcs.push_back(Factory::Create("Ork","O1",0,0));
    npcs.push_back(Factory::Create("Ork","O2",1,1));
    Battle(npcs,100,subject);
    ASSERT_TRUE(CountDead(npcs) >= 1);
}

TEST(test_06, basic_test_set) {
    Subject subject;
    ConsoleObserver consoleObs;
    LogObserver logObs;
    subject.Attach(&consoleObs);
    subject.Attach(&logObs);
    std::vector<std::unique_ptr<NPC>> npcs;
    npcs.push_back(Factory::Create("Bear","B1",5,5));
    npcs.push_back(Factory::Create("Ork","O1",10,10));
    Battle(npcs,5,subject);
    ASSERT_TRUE(CountDead(npcs) == 0);
}

TEST(test_07, basic_test_set) {
    Subject subject;
    ConsoleObserver consoleObs;
    LogObserver logObs;
    subject.Attach(&consoleObs);
    subject.Attach(&logObs);
    std::vector<std::unique_ptr<NPC>> npcs;
    npcs.push_back(Factory::Create("Bear","B1",5,5));
    npcs.push_back(Factory::Create("Ork","O1",6,6));
    Battle(npcs,5,subject);
    ASSERT_TRUE(CountDead(npcs) == 1);
}

TEST(test_08, basic_test_set) {
    Subject subject;
    ConsoleObserver consoleObs;
    LogObserver logObs;
    subject.Attach(&consoleObs);
    subject.Attach(&logObs);
    std::vector<std::unique_ptr<NPC>> npcs;
    npcs.push_back(Factory::Create("Squirrel","S1",5,5));
    npcs.push_back(Factory::Create("Bear","B1",5,5));
    Battle(npcs,10,subject);
    ASSERT_TRUE(CountDead(npcs) == 1);
}

int main(int argc,char** argv){
    testing::InitGoogleTest(&argc,argv);
    return RUN_ALL_TESTS();
}
