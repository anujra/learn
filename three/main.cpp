#include <iostream>
#include <mutex>
#include <thread>
#include <vector>
#include <algorithm>
#include <iterator>
#include <sstream>
#include <format>
#include "spin_lock.h"

void to_io(const std::string& ss) {
    static std::mutex io_mutex;
    std::lock_guard<std::mutex> lk(io_mutex);
    std::cout << ss << std::endl;
}



void server(bool& run, int64_t& inc, std::string name) {
    to_io(std::format("{}  {}", name, inc));

    while(run) {

    }

}

void network(bool& run, int64_t& inc, std::string name) {
    to_io(std::format("{}  {}", name, inc));
    while(run) {

    }

}

void strat00(bool& run, int64_t& inc, std::string name) {
    to_io(std::format("{}  {}", name, inc));
    while(run) {
        
    }

}

void strat01(bool& run, int64_t& inc, std::string name) {
    to_io(std::format("{}  {}", name, inc));
    while(run) {
        
    }

}



int main()
{
    std::cout << "Hello world" << std::endl;
    // vector container stores threads
    std::vector<std::thread> workers;

    bool run = true;
    int64_t inc = 0;

    workers.push_back(std::thread(server, std::ref(run), std::ref(inc), "server"));
    workers.push_back(std::thread(network, std::ref(run), std::ref(inc), "network"));
    workers.push_back(std::thread(strat00, std::ref(run), std::ref(inc), "strat00"));
    workers.push_back(std::thread(strat01, std::ref(run), std::ref(inc), "strat01"));

    std::this_thread::sleep_for(std::chrono::seconds(1));
    run = false;


    std::for_each(workers.begin(), workers.end(), [](std::thread &t) 
    {
        t.join();
    });

   return 0;
}