#include "Observer.h"
#include <iostream>
#include <fstream>

void Subject::Attach(Observer* o){observers.push_back(o);}
void Subject::Detach(Observer* o){
    for(auto it=observers.begin(); it!=observers.end(); ++it){
        if(*it==o){observers.erase(it);break;}
    }
}
void Subject::Notify(const std::string& killer,const std::string& victim){
    for(auto& o:observers)o->OnKill(killer,victim);
}

ConsoleObserver::~ConsoleObserver(){} // Обязательно объявлен в header, здесь определяем тело
void ConsoleObserver::OnKill(const std::string& killer,const std::string& victim){
    std::cout<<killer<<" killed "<<victim<<"\n";
}

LogObserver::~LogObserver(){} // Аналогично
void LogObserver::OnKill(const std::string& killer,const std::string& victim){
    std::ofstream f("log.txt",std::ios::app);
    f<<killer<<" killed "<<victim<<"\n";
}
