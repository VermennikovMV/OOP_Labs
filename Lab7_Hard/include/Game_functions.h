#pragma once
#include <string>
#include <vector>
#include <memory>
#include <map>
#include <coroutine>
#include <atomic>
#include <shared_mutex>
#include <random>
#include <mutex>
#include <iostream>
#include <fstream>
#include <thread>
#include <chrono>

class NPC;
class Subject;

void PrintAll(const std::vector<NPC*>& npcs);
void SaveToFile(const std::vector<NPC*>& npcs,const std::string& filename);
void LoadFromFile(std::vector<std::unique_ptr<NPC>>& npcs,const std::string& filename);

struct awaiter {
    bool await_ready() const noexcept {return false;}
    void await_suspend(std::coroutine_handle<> h){std::this_thread::sleep_for(std::chrono::milliseconds(100));h.resume();}
    void await_resume() noexcept {}
};

struct task {
    struct promise_type {
        task get_return_object(){return task{std::coroutine_handle<promise_type>::from_promise(*this)};}
        std::suspend_always initial_suspend(){return {};}
        std::suspend_always final_suspend() noexcept{return {};}
        void return_void(){}
        void unhandled_exception(){}
    };
    std::coroutine_handle<promise_type> coro;
    ~task(){if(coro)coro.destroy();}
};

task MovementAndFightCoroutine(std::vector<std::unique_ptr<NPC>>& npcs,std::shared_mutex& m,Subject& subj,std::atomic_bool& stop);
void PrintMap(const std::vector<std::unique_ptr<NPC>>& npcs);
bool CanKill(const NPC& killer,const NPC& target);

extern std::map<std::string,int> move_dist;
extern std::map<std::string,int> kill_dist;
extern std::mutex io_m;
