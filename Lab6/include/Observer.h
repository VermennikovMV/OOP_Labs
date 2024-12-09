#pragma once
#include <string>
#include <vector>

class Observer {
public:
    virtual ~Observer()=default;
    virtual void OnKill(const std::string& killer,const std::string& victim)=0;
};

class Subject {
    std::vector<Observer*> observers;
public:
    void Attach(Observer* o);
    void Detach(Observer* o);
    void Notify(const std::string& killer,const std::string& victim);
};

class ConsoleObserver : public Observer {
public:
    virtual ~ConsoleObserver() override; // Обязательно virtual и override
    void OnKill(const std::string& killer,const std::string& victim) override;
};

class LogObserver : public Observer {
public:
    virtual ~LogObserver() override; // То же самое здесь
    void OnKill(const std::string& killer,const std::string& victim) override;
};
