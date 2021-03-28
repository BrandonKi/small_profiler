#include <iostream>
#include <chrono>
#include <thread>

// #define PROFILE_OUTPUT_FILE "yo.json"
// #define NO_PROFILE

#include "small_profiler.h"

void helper() {
    PROFILE();
    std::this_thread::sleep_for(std::chrono::milliseconds(100));

}

int main(int, char**) {
    PROFILE();
    std::this_thread::sleep_for(std::chrono::milliseconds(200));
    helper();

    std::thread s{[](){PROFILE();}};
    s.join();

}