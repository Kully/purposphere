#include "lib.h"
#include "math.h"
#include "stdio.h"

// colors
#define RED 0xffff0000
#define ORANGE 0xffffa500
#define GREEN 0xff00ff00
#define BLUE 0xff0000ff
#define YELLOW 0xffffff00
#define TEAL 0xff008080


// draw_triangle(5, 6, 60, 70, 20, 70, RED);
void draw_triangle(int x0, int y0, int x1, int y1, int x2, int y2, uint32_t pixel)
{
    line(x0, y0, x1, y1, pixel);
    line(x1, y1, x2, y2, pixel);
    line(x2, y2, x0, y0, pixel);
}

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
        clear();

        float x0 = (xres/2 + 30*sin(n));
        float y0 = (yres/2 - 30*cos(n));

        float x1 = (xres/2 + 30*sin(n+(2*M_PI)/3));
        float y1 = (yres/2 - 30*cos(n+(2*M_PI)/3));

        float x2 = (xres/2 + 30*sin(n+(4*M_PI)/3));
        float y2 = (yres/2 - 30*cos(n+(4*M_PI)/3));

        draw_triangle(x0, y0, x1, y1, x2, y2, TEAL);

        n += 0.02;
        unlock();
        delay(15);
    }
    shutdown();
}

