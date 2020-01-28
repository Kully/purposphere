#include "lib.h"

int main(void)
{
    setup(80, 80);
    resize(3);
    while(!end())
    {
        lock();
        clear();
        /* CODE GOES BETWEEN CLEAR AND UNLOCK*/
        unlock();
        delay(15);
    }
    shutdown();
}

