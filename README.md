# small_profiler
Simple inline C++ profiling. Outputs a json that can be used with chrome://tracing as a frontend.

Include the header then put `PROFILE()` at the begining of any function you wish to profile.

## Example
```cpp
#include "small_profiler.h"

int main(int, char**) {
    PROFILE();
}
```

To view the graph go to chrome://tracing click 'load' and select the generated json file.

To turn off profiling define the macro `NO_PROFILE` before including the header file.
