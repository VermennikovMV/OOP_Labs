#include "include/NPC.h"
#include "include/Ork.h"
#include "include/Squirrel.h"
#include "include/Bear.h"
#include "include/Factory.h"
#include "include/Observer.h"
#include "include/Visitors.h"
#include "include/Game_functions.h"

int main(){
    Subject subject;
    ConsoleObserver consoleObs;
    LogObserver logObs;
    subject.Attach(&consoleObs);
    subject.Attach(&logObs);

    std::mt19937 gen(std::random_device{}());
    std::uniform_int_distribution<int> pos(0,99);
    std::uniform_int_distribution<int> typeDist(0,2);
    std::vector<std::string> types={"Ork","Squirrel","Bear"};

    std::vector<std::unique_ptr<NPC>> npcs;
    for(int i=0;i<50;++i){
        int x=pos(gen),y=pos(gen);
        int t=typeDist(gen);
        npcs.push_back(Factory::Create(types[t],"NPC"+std::to_string(i),x,y));
    }

    std::shared_mutex m;
    std::atomic_bool stop{false};
    auto t=MovementAndFightCoroutine(npcs,m,subject,stop);
    t.coro.resume();

    auto start=std::chrono::steady_clock::now();
    while(true){
        {
            std::shared_lock l(m);
            PrintMap(npcs);
        }
        std::this_thread::sleep_for(std::chrono::seconds(1));
        t.coro.resume();
        auto now=std::chrono::steady_clock::now();
        if(std::chrono::duration_cast<std::chrono::seconds>(now - start).count()>=30)break;
    }
    stop.store(true);
    t.coro.resume();

    {
        std::shared_lock l(m);
        int aliveCount=0;
        for(auto &n:npcs)if(n->IsAlive())aliveCount++;
        std::lock_guard<std::mutex> lk(io_m);
        std::cout<<"Survivors: "<<aliveCount<<"\n";
        for(auto &n:npcs){
            if(n->IsAlive()){
                std::cout<<n->GetType()<<" "<<n->GetName()<<" "<<n->GetX()<<" "<<n->GetY()<<"\n";
            }
        }
    }

    return 0;
}