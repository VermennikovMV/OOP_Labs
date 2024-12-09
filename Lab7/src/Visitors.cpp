#include "../include/Visitors.h"
#include "../include/Ork.h"
#include "../include/Squirrel.h"
#include "../include/Bear.h"
#include "../include/NPC.h"
#include "../include/Observer.h"
#include <cmath>

FightVisitor::FightVisitor(std::vector<NPC*>& n,int r,Subject& sub):npcs(n),range(r),subject(sub){}
FightVisitor::~FightVisitor(){}
void FightVisitor::Visit(Ork& o){}
void FightVisitor::Visit(Squirrel& s){}
void FightVisitor::Visit(Bear& b){}
void FightVisitor::AttemptKill(NPC& killer,const std::string& t1,const std::string& t2){}
bool FightVisitor::InRange(const NPC& a,const NPC& b){return false;}
void FightVisitor::KillTarget(NPC& killer,NPC& target){}