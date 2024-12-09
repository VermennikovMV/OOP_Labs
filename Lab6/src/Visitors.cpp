#include "../include/Visitors.h"
#include "../include/Ork.h"
#include "../include/Squirrel.h"
#include "../include/Bear.h"
#include "../include/NPC.h"
#include "../include/Observer.h"
#include <cmath>

FightVisitor::FightVisitor(std::vector<NPC*>& n,int r,Subject& sub):npcs(n),range(r),subject(sub){}
FightVisitor::~FightVisitor(){}
void FightVisitor::Visit(Ork& o){
    if(!o.IsAlive())return;
    AttemptKill(o,"Bear","Ork");
}
void FightVisitor::Visit(Squirrel& s){
    if(!s.IsAlive())return;
}
void FightVisitor::Visit(Bear& b){
    if(!b.IsAlive())return;
    AttemptKill(b,"Squirrel");
}
void FightVisitor::AttemptKill(NPC& killer,const std::string& t1,const std::string& t2){
    for(auto& target:npcs){
        if(target->IsAlive()&&target!=&killer){
            if((!t1.empty()&&target->GetType()==t1)||(!t2.empty()&&target->GetType()==t2)){
                if(InRange(killer,*target)){
                    KillTarget(killer,*target);
                }
            }
        }
    }
}
bool FightVisitor::InRange(const NPC& a,const NPC& b){
    int dx=a.GetX()-b.GetX();
    int dy=a.GetY()-b.GetY();
    return dx*dx+dy*dy<=range*range;
}
void FightVisitor::KillTarget(NPC& killer,NPC& target){
    target.Kill();
    subject.Notify(killer.GetName(),target.GetName());
}
