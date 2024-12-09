#include "../include/Game_functions.h"
#include "../include/NPC.h"
#include "../include/Factory.h"
#include "../include/Visitors.h"
#include "../include/Observer.h"
#include <fstream>
#include <iostream>
#include <map>

std::map<std::string,int> move_dist={{"Ork",20},{"Squirrel",5},{"Bear",5}};
std::map<std::string,int> kill_dist={{"Ork",10},{"Squirrel",5},{"Bear",10}};
std::mutex io_m;

bool CanKill(const NPC& killer,const NPC& target){
    std::string kt=killer.GetType();
    std::string tt=target.GetType();
    if(kt=="Ork" && (tt=="Bear"||tt=="Ork"))return true;
    if(kt=="Bear" && tt=="Squirrel")return true;
    return false;
}

void PrintAll(const std::vector<NPC*>& npcs){
    for(auto& n:npcs){
        if(n->IsAlive()) {
            std::lock_guard<std::mutex> lk(io_m);
            std::cout<<n->GetType()<<" "<<n->GetName()<<" "<<n->GetX()<<" "<<n->GetY()<<"\n";
        }
    }
}

void SaveToFile(const std::vector<NPC*>& npcs,const std::string& filename){
    std::ofstream f(filename);
    for(auto& n:npcs){
        if(n->IsAlive())f<<n->GetType()<<" "<<n->GetName()<<" "<<n->GetX()<<" "<<n->GetY()<<"\n";
    }
}

void LoadFromFile(std::vector<std::unique_ptr<NPC>>& npcs,const std::string& filename){
    std::ifstream fi(filename);
    std::string type,name;int x,y;
    while(fi>>type>>name>>x>>y){
        npcs.push_back(Factory::Create(type,name,x,y));
    }
}

void PrintMap(const std::vector<std::unique_ptr<NPC>>& npcs){
    std::vector<std::string> map(100,std::string(100,' '));
    for(auto &n:npcs){
        if(n->IsAlive()){
            map[n->GetY()][n->GetX()]='*';
        }
    }
    std::lock_guard<std::mutex> lk(io_m);
    for(auto &line:map) std::cout<<line<<"\n";
    std::cout<<"----\n";
}

task MovementAndFightCoroutine(std::vector<std::unique_ptr<NPC>>& npcs,std::shared_mutex& m,Subject& subj,std::atomic_bool& stop) {
    std::mt19937 gen(std::random_device{}());
    std::uniform_int_distribution<int> move_dist_rand(-1,1);
    std::uniform_int_distribution<int> dice(1,6);
    while(!stop.load()) {
        {
            std::unique_lock l(m);
            for(auto &n:npcs){
                if(n->IsAlive()){
                    int d=move_dist[n->GetType()];
                    int dx=move_dist_rand(gen)*d;
                    int dy=move_dist_rand(gen)*d;
                    n->Move(dx,dy);
                }
            }
            for(size_t i=0;i<npcs.size();++i){
                for(size_t j=i+1;j<npcs.size();++j){
                    auto&a=npcs[i];auto&b=npcs[j];
                    if(a->IsAlive() && b->IsAlive()){
                        int dx=a->GetX()-b->GetX();
                        int dy=a->GetY()-b->GetY();
                        int dist=dx*dx+dy*dy;
                        int kd=kill_dist[a->GetType()];
                        if(dist<=kd*kd && CanKill(*a,*b)){
                            int atk=dice(gen);
                            int def=dice(gen);
                            if(atk>def){
                                b->Kill();
                                subj.Notify(a->GetName(),b->GetName());
                            }
                        } else {
                            int kd2=kill_dist[b->GetType()];
                            if(dist<=kd2*kd2 && CanKill(*b,*a)){
                                int atk=dice(gen);
                                int def=dice(gen);
                                if(atk>def){
                                    a->Kill();
                                    subj.Notify(b->GetName(),a->GetName());
                                }
                            }
                        }
                    }
                }
            }
        }
        co_await awaiter{};
    }
}
