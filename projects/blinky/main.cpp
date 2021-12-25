
#include <cstdio>
#include <cstdint>

#include "asf.h"

int main() {

    system_init();

    while(1)
    {
        for(auto idx = 0; idx < 32767; idx++)
        {
            idx += 1;
        }
    }
}

