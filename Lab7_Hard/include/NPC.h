#pragma once
#include <string>
class NPC {
public:
    virtual ~NPC()=default;
    virtual std::string GetName()const=0;
    virtual int GetX()const=0;
    virtual int GetY()const=0;
    virtual std::string GetType()const=0;
    virtual bool IsAlive()const=0;
    virtual void Kill()=0;
    virtual void Move(int dx,int dy)=0;
};