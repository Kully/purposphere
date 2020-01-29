#include "lib.h"

// #define RED = 0xffff0000;

int main(void)
{
    setup(80, 80);
    resize(3);
    while(!end())
    {
        lock();
        clear();
        

        line(5, 6, 60, 70, 0xffff0000);

        unlock();
        delay(15);
    }
    shutdown();
}

