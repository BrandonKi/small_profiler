#ifndef SMALL_PROFILER_H
#define SMALL_PROFILER_H

#include <iostream>
#include <fstream>
#include <thread>
#include <chrono>
#include <string>
#include <sstream>

#if defined(__linux__)
#include <sys/types.h>
#include <unistd.h>
#elif defined(_WIN32)
#include <windows.h>
#endif

#define PROFILE() small_profiler::internal_scoped_profiler temp{__FUNCTION__}

namespace small_profiler {

    unsigned long long get_pid() {
        #if defined(__linux__)
        return getpid();
        #elif defined(_WIN32)
        return GetCurrentProcessId();
        #endif
        return -1;
    }

    class internal_stream_wrapper {
        public:
            std::stringstream stream{"profile.json"};        

            internal_stream_wrapper() {
                stream << "{ \"traceEvents\": [";
            }
            ~internal_stream_wrapper() {
                stream.seekp(-1, std::ios_base::end);
                stream << "]}";
                std::ofstream out{"profile.json"};
                out << stream.str();
            }
    };

    internal_stream_wrapper file;
    auto program_start = std::chrono::high_resolution_clock::now();
    unsigned long long tid_counter = 0;

    class internal_scoped_profiler {
        public:
            internal_scoped_profiler(std::string name_p):
                begin(std::chrono::high_resolution_clock::now()), name(name_p)
            {
                std::cout << "c\n";
                
            }

            ~internal_scoped_profiler() {
                std::cout << "d\n";
                auto end = std::chrono::high_resolution_clock::now();

                auto pid = small_profiler::get_pid();
                auto tid = tid_counter++;
                auto ts = std::chrono::duration_cast<std::chrono::microseconds>(begin - program_start).count();
                auto dur = std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count();
                auto ph = "X";
                auto args = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count();

                std::string line = std::string(
                    "{ \"pid\":") + std::to_string(pid) + std::string(", \"tid\":") + std::to_string(tid) +
                    std::string(", \"ts\":") + std::to_string(ts) + std::string(", \"dur\":") + std::to_string(dur) +
                    std::string(", \"ph\":\"") + std::string(ph) + std::string("\", \"name\":\"") + name +
                    std::string("\", \"args\":{ \"ms\":") + std::to_string(args) + std::string("} },"
                );
                file.stream << line;
            }
        
        private:
            std::string name;
            std::chrono::time_point<std::chrono::high_resolution_clock> begin;
    };

};
/// { "pid":1, "tid":1, "ts":546867, "dur":121564, "ph":"X", "name":"DoThings", "args":{ "ms":121.6 } }

#endif