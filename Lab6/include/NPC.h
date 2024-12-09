#pragma once
#include <string>
class Visitor;
class NPC {
public:
    virtual ~NPC()=default;
    virtual void Accept(Visitor& v)=0;
    virtual std::string GetName() const=0;
    virtual int GetX() const=0;
    virtual int GetY() const=0;
    virtual std::string GetType() const=0;
    virtual bool IsAlive() const=0;
    virtual void Kill()=0;
};