#include <iostream>
#include <chrono>
#include <thread>

#include "small_profiler.h"

void helper() {
    PROFILE();
    std::this_thread::sleep_for(std::chrono::milliseconds(800));

}

int main(int, char**) {
    PROFILE();
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    helper();

}