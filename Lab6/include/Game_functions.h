#pragma once
#include <vector>
#include <string>
#include <memory>
class NPC;
class Subject;
void PrintAll(const std::vector<NPC*>& npcs);
void SaveToFile(const std::vector<NPC*>& npcs,const std::string& filename);
void LoadFromFile(std::vector<std::unique_ptr<NPC>>& npcs,const std::string& filename);
void Battle(std::vector<std::unique_ptr<NPC>>& npcs,int range,Subject& subject);