#include <gtest/gtest.h>
#include "../include/NPC.h"
#include "../include/Ork.h"
#include "../include/Squirrel.h"
#include "../include/Bear.h"
#include "../include/Factory.h"
#include "../include/Observer.h"
#include "../include/Visitors.h"
#include "../include/Game_functions.h"

TEST(test_01, basic_test_set) {
    std::vector<std::unique_ptr<NPC>> npcs;
    npcs.push_back(Factory::Create("Ork","O1",0,0));
    npcs.push_back(Factory::Create("Bear","B1",10,10));
    npcs.push_back(Factory::Create("Squirrel","S1",5,5));
    int c=0;
    for(auto&n:npcs)if(n->IsAlive())c++;
    ASSERT_EQ(c,3);
}

TEST(test_02, basic_test_set) {
    std::vector<std::unique_ptr<NPC>> npcs;
    npcs.push_back(Factory::Create("Ork","O1",0,0));
    npcs.push_back(Factory::Create("Ork","O2",0,0));
    npcs[1]->Kill();
    int c=0;
    for(auto&n:npcs)if(n->IsAlive())c++;
    ASSERT_EQ(c,1);
}

int main(int argc,char** argv){
    testing::InitGoogleTest(&argc,argv);
    return RUN_ALL_TESTS();
}