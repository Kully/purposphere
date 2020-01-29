#include "lib.h"
#include "math.h"
#include "stdio.h"

// colors
#define BLACK 0x0
#define RED 0xffff0000
#define ORANGE 0xffffa500
#define GREEN 0xff00ff00
#define BLUE 0xff0000ff
#define YELLOW 0xffffff00
#define TEAL 0xff008080


int main(void)
{
    int xres = 80;
    int yres = 80;
    setup(xres, yres);
    resize(5);

    float n = 0;
    while(!end())
    {
        lock();
        clear(0x0);

        int radius = 5 + 35*(pow(sin(uptime()/4), 2));
        float n = 2*uptime();
        float x0 = (xres/2 + radius*sin(n));
        float y0 = (yres/2 + radius*cos(n));

        float x1 = (xres/2 + radius*sin(n+(2*M_PI)/3));
        float y1 = (yres/2 + radius*cos(n+(2*M_PI)/3));

        float x2 = (xres/2 + radius*sin(n+(4*M_PI)/3));
        float y2 = (yres/2 + radius*cos(n+(4*M_PI)/3)); 

        triangle(x0, y0, x1, y1, x2, y2, TEAL);

        unlock();
        delay(15);
    }
    shutdown();
}

