#include "lib.h"
#include "math.h"
#include "stdio.h"

/*

About the Coordinate System
---------------------------

Our vectors Vec3 should be interpretted in
an initial coordinate system that will then
be mapped via the function View() to a triangle
that is native to the mxn pixel display in C.

Our first coordinate system has span
  x:(-0.5, 0.5)
  y:(-0.5, 0.5)

*/ 

// resolution
int xres = 80;
int yres = 80;

// colors
#define BLACK 0x0
#define RED 0xffff0000
#define ORANGE 0xffffa500
#define GREEN 0xff00ff00
#define BLUE 0xff0000ff
#define YELLOW 0xffffff00
#define TEAL 0xff008080


typedef struct
{
    double x;
    double y;
    double z;
}
Vec3;

typedef struct
{
    Vec3 a;
    Vec3 b;
    Vec3 c;
}
Tri;

bool In_Triangle(Vec3 v, Tri t)
{   
    // distances from all triangle points (2D) to point in question
    double distance_a_v = distance(t.a.x, t.a.y, v.x, v.y);
    double distance_b_v = distance(t.b.x, t.b.y, v.x, v.y);
    double distance_c_v = distance(t.c.x, t.c.y, v.x, v.y);
    double sum_of_dists = distance_a_v + distance_b_v + distance_c_v;

    printf("dist a: %f \n", distance_a_v);
    printf("dist b: %f \n", distance_b_v);
    printf("dist c: %f \n", distance_c_v);
    printf("MAX: %f \n", MAX(distance_a_v, distance_b_v));
    printf("sum of dists: %f \n", sum_of_dists);
    printf("\n");

    if(sum_of_dists > 3*distance_c_v)
        return false;
    return true;
}

void Draw_Triangle(Tri t, uint32_t color)
{
    line(t.a.x, t.a.y, t.b.x, t.b.y, color);
    line(t.b.x, t.b.y, t.c.x, t.c.y, color);
    line(t.c.x, t.c.y, t.a.x, t.a.y, color);
}

void Draw_Filled_Triangle(Tri t, uint32_t color)
{
    printf("t.a.x: %f \n", t.a.x);
    printf("t.a.y: %f \n", t.a.x);

    line(t.a.x, t.a.y, t.b.x, t.b.y, color);
    line(t.b.x, t.b.y, t.c.x, t.c.y, color);
    line(t.c.x, t.c.y, t.a.x, t.a.y, color);

    int min_X = MIN(MIN(t.a.x, t.b.x), t.c.x);
    int max_X = MAX(MAX(t.a.x, t.b.x), t.c.x);
    int min_Y = MIN(MIN(t.a.y, t.b.y), t.c.y);
    int max_Y = MAX(MAX(t.a.y, t.b.y), t.c.y);

    for(int i=min_X; i<max_X; i++)
    for(int j=min_Y; j<max_Y; j++)
        {
            Vec3 point = {i, j, 1.0};
            if(In_Triangle(point, t))
                put(i, j, color);
            
            // printf("i: %d \n", i);
            // printf("j: %d \n\n", j);
        }
}

Vec3 Mul(Vec3 a, Vec3 b)
{
    return (Vec3) { a.x * b.x, a.y * b.y, a.z * b.z };
}

Vec3 Add(Vec3 a, Vec3 b)
{
    return (Vec3) { a.x + b.x, a.y + b.y, a.z + b.z };
}

Tri View(Tri t)
{
    Vec3 alpha = { xres, yres, 1.0 };
    Vec3 beta = { xres / 2, yres / 2, 0.0 };
    t.a = Mul(t.a, alpha);
    t.b = Mul(t.b, alpha);
    t.c = Mul(t.c, alpha);
    t.a = Add(t.a, beta);
    t.b = Add(t.b, beta);
    t.c = Add(t.c, beta);
    return t;
}

int main(void)
{
    setup(xres, yres);
    resize(5);

    float n = 0;
    Tri t = {
        { -0.25, -0.25, 1.0 },
        {  0.25, -0.25, 1.0 },
        {  0.0,   0.25, 0.0 },
    };
    while(!end())
    {
        lock();
        clear(0x0);

        Draw_Triangle(View(t), TEAL);
        // Draw_Filled_Triangle(View(t), TEAL);

        unlock();
        delay(15);
    }
    shutdown();
}
