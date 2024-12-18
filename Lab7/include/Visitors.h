#pragma once
#include <vector>
#include <string>
#include "Ork.h"
#include "Squirrel.h"
#include "Bear.h"
#include "NPC.h"
#include "Observer.h"
class Visitor {
public:
    virtual ~Visitor()=default;
    virtual void Visit(Ork& o)=0;
    virtual void Visit(Squirrel& s)=0;
    virtual void Visit(Bear& b)=0;
};
class FightVisitor:public Visitor {
    std::vector<NPC*>& npcs;
    int range;
    Subject& subject;
public:
    FightVisitor(std::vector<NPC*>& n,int r,Subject& sub);
    virtual ~FightVisitor();
    void Visit(Ork& o) override;
    void Visit(Squirrel& s) override;
    void Visit(Bear& b) override;
private:
    void AttemptKill(NPC& killer,const std::string& t1="",const std::string& t2="");
    bool InRange(const NPC& a,const NPC& b);
    void KillTarget(NPC& killer,NPC& target);
};