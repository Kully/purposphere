#include "lib.h"

#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <math.h>
#include <time.h>

int xres;
int yres;

SDL_Window* window;
SDL_Renderer* renderer;
SDL_Texture* texture;

uint32_t* pixels;

const uint8_t* key;

void setup(int _xres, int _yres)
{
    xres = _xres;
    yres = _yres;
    window = SDL_CreateWindow(
            "TWEETCART",
            SDL_WINDOWPOS_UNDEFINED,
            SDL_WINDOWPOS_UNDEFINED,
            xres,
            yres,
            SDL_WINDOW_SHOWN);
    renderer = SDL_CreateRenderer(
            window,
            -1,
            SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    texture = SDL_CreateTexture(
            renderer,
            SDL_PIXELFORMAT_ARGB8888,
            SDL_TEXTUREACCESS_STREAMING,
            xres,
            yres);
    key = SDL_GetKeyboardState(NULL);
}

void resize(int size)
{
    SDL_SetWindowSize(window, xres * size, yres * size);
    SDL_SetWindowPosition(window, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);
}

void lock(void)
{
    void* raw;
    int pitch;
    SDL_LockTexture(texture, NULL, &raw, &pitch);
    pixels = (uint32_t*) raw;
}

void unlock(void)
{
    SDL_UnlockTexture(texture);
    SDL_RenderCopy(renderer, texture, NULL, NULL);
    SDL_RenderPresent(renderer);
}

void shutdown(void)
{
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyTexture(texture);
}

void delay(int ms)
{
    SDL_Delay(ms);
}

uint32_t get(int x, int y)
{
    return pixels[x + y * xres];
}

void put(int x, int y, uint32_t pixel)
{
    pixels[x + y * xres] = pixel;
}

void line(int x0, int y0, int x1, int y1, uint32_t pixel)
{
    int dx =  abs (x1 - x0), sx = x0 < x1 ? 1 : -1;
    int dy = -abs (y1 - y0), sy = y0 < y1 ? 1 : -1;
    int err = dx + dy, e2; /* error value e_xy */
    for (;;)
    {
        put(x0, y0, pixel);
        if(x0 == x1 && y0 == y1)
            break;
        e2 = 2 * err;
        if(e2 >= dy)
        {
            err += dy;
            x0 += sx;
        }
        if(e2 <= dx)
        {
            err += dx;
            y0 += sy;
        }
    }
}

void circle(int xm, int ym, int r, uint32_t pixel)
{
    int x = -r;
    int y = 0;
    int err = 2 - 2 * r;
    do
    {
        put(xm - x, ym + y, pixel);
        put(xm - y, ym - x, pixel);
        put(xm + x, ym - y, pixel);
        put(xm + y, ym + x, pixel);
        r = err;
        if(r >  x)
            err += ++x * 2 + 1;
        if(r <= y)
            err += ++y * 2 + 1;
   }
   while(x < 0);
}

void filled_circle(int x0, int y0, int radius, uint32_t pixel)
{
    int x = radius;
    int y = 0;
    int xChange = 1 - (radius << 1);
    int yChange = 0;
    int radiusError = 0;
    while(x >= y)
    {
        for(int i = x0 - x; i <= x0 + x; i++)
        {
            put(i, y0 + y, pixel);
            put(i, y0 - y, pixel);
        }
        for(int i = x0 - y; i <= x0 + y; i++)
        {
            put(i, y0 + x, pixel);
            put(i, y0 - x, pixel);
        }
        y++;
        radiusError += yChange;
        yChange += 2;
        if (((radiusError << 1) + xChange) > 0)
        {
            x--;
            radiusError += xChange;
            xChange += 2;
        }
    }
}

void filled_rect(int x0, int y0, int x1, int y1, uint32_t pixel)
{
    for(int x = x0; x < x1; x++)
    for(int y = y0; y < y1; y++)
        put(x, y, pixel);
}

void clear(void)
{
    for(int x = 0; x < xres; x++)
    for(int y = 0; y < yres; y++)
        put(x, y, 0x0);
}

void clear_with_color(uint32_t color)
{
    for(int x = 0; x < xres; x++)
    for(int y = 0; y < yres; y++)
        put(x, y, color);
}

bool end(void)
{
    SDL_PumpEvents();
    return key[SDL_SCANCODE_ESCAPE] || key[SDL_SCANCODE_END];
}

float uptime(void)
{
    return SDL_GetTicks() / 1000.f;
}

void fseed(void)
{
    srand(time(NULL));
}

float frand(float max)
{
    return (float) rand() / (RAND_MAX / max);
}
