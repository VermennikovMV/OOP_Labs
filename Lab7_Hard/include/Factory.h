#pragma once
#include <memory>
#include <string>
#include "NPC.h"
class Factory {
public:
    static std::unique_ptr<NPC> Create(const std::string& type,const std::string& name,int x,int y);
};