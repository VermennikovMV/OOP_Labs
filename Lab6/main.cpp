#include "include/NPC.h"
#include "include/Ork.h"
#include "include/Squirrel.h"
#include "include/Bear.h"
#include "include/Factory.h"
#include "include/Observer.h"
#include "include/Visitors.h"
#include "include/Game_functions.h"
int main(){
    Subject subject;
    ConsoleObserver consoleObs;
    LogObserver logObs;
    subject.Attach(&consoleObs);
    subject.Attach(&logObs);
    std::vector<std::unique_ptr<NPC>> npcs;
    npcs.push_back(Factory::Create("Ork","Grok",10,10));
    npcs.push_back(Factory::Create("Ork","Mrok",12,12));
    npcs.push_back(Factory::Create("Bear","Balu",15,15));
    npcs.push_back(Factory::Create("Squirrel","Chippy",20,20));
    PrintAll({npcs[0].get(),npcs[1].get(),npcs[2].get(),npcs[3].get()});
    SaveToFile({npcs[0].get(),npcs[1].get(),npcs[2].get(),npcs[3].get()},"output.txt");
    std::vector<std::unique_ptr<NPC>> loaded;
    LoadFromFile(loaded,"output.txt");
    PrintAll({loaded[0].get(),loaded[1].get(),loaded[2].get(),loaded[3].get()});
    Battle(loaded,5,subject);
    PrintAll({loaded[0].get(),loaded[1].get(),loaded[2].get(),loaded[3].get()});
}
