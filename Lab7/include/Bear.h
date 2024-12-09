#pragma once
#include "NPC.h"
class Bear:public NPC {
    std::string name;
    int x,y;
    bool alive;
public:
    Bear(const std::string& n,int xx,int yy);
    std::string GetName()const override;
    int GetX()const override;
    int GetY()const override;
    std::string GetType()const override;
    bool IsAlive()const override;
    void Kill() override;
    void Move(int dx,int dy) override;
};