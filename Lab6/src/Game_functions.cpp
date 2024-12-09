#include "../include/Game_functions.h"
#include "../include/NPC.h"
#include "../include/Factory.h"
#include "../include/Visitors.h"
#include "../include/Observer.h"
#include <fstream>
#include <iostream>
void PrintAll(const std::vector<NPC*>& npcs){
    for(auto& n:npcs){
        if(n->IsAlive())std::cout<<n->GetType()<<" "<<n->GetName()<<" "<<n->GetX()<<" "<<n->GetY()<<"\n";
    }
}
void SaveToFile(const std::vector<NPC*>& npcs,const std::string& filename){
    std::ofstream f(filename);
    for(auto& n:npcs){
        if(n->IsAlive())f<<n->GetType()<<" "<<n->GetName()<<" "<<n->GetX()<<" "<<n->GetY()<<"\n";
    }
}
void LoadFromFile(std::vector<std::unique_ptr<NPC>>& npcs,const std::string& filename){
    std::ifstream f(filename);
    std::string type,name;
    int x,y;
    while(f>>type>>name>>x>>y){
        npcs.push_back(Factory::Create(type,name,x,y));
    }
}
void Battle(std::vector<std::unique_ptr<NPC>>& npcs,int range,Subject& subject){
    bool fighting=true;
    while(fighting){
        fighting=false;
        std::vector<NPC*> alive;
        for(auto& n:npcs)if(n->IsAlive())alive.push_back(n.get());
        FightVisitor visitor(alive,range,subject);
        for(auto& n:alive){
            n->Accept(visitor);
        }
        for(auto& n:alive){
            if(!n->IsAlive())fighting=true;
        }
    }
}
