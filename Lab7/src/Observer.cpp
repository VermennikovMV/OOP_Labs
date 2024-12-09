#include "Observer.h"
#include <iostream>
#include <fstream>

void Subject::Attach(Observer* o){observers.push_back(o);}
void Subject::Detach(Observer* o){for(auto it=observers.begin();it!=observers.end();++it){if(*it==o){observers.erase(it);break;}}}
void Subject::Notify(const std::string& killer,const std::string& victim){for(auto&o:observers)o->OnKill(killer,victim);}

static std::mutex console_m;
ConsoleObserver::~ConsoleObserver(){}
void ConsoleObserver::OnKill(const std::string& killer,const std::string& victim){
    std::lock_guard<std::mutex> lk(console_m);
    std::cout<<killer<<" killed "<<victim<<"\n";
}

static std::mutex log_m;
LogObserver::~LogObserver(){}
void LogObserver::OnKill(const std::string& killer,const std::string& victim){
    std::lock_guard<std::mutex> lk(log_m);
    std::ofstream f("log.txt",std::ios::app);
    f<<killer<<" killed "<<victim<<"\n";
}
