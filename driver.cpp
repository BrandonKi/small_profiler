#include <iostream>
#include <chrono>
#include <thread>

#include "small_profiler.h"

void helper() {
    PROFILE();
    std::this_thread::sleep_for(std::chrono::milliseconds(100));

}

int main(int, char**) {
    PROFILE();
    std::this_thread::sleep_for(std::chrono::milliseconds(200));
    helper();

}