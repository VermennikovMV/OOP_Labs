#include "../include/Factory.h"
#include "../include/Ork.h"
#include "../include/Squirrel.h"
#include "../include/Bear.h"
std::unique_ptr<NPC> Factory::Create(const std::string& type,const std::string& name,int x,int y) {
    if(type=="Ork") return std::make_unique<Ork>(name,x,y);
    if(type=="Squirrel") return std::make_unique<Squirrel>(name,x,y);
    if(type=="Bear") return std::make_unique<Bear>(name,x,y);
    return nullptr;
}