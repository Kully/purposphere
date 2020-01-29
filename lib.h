#pragma once

#include <stdint.h>
#include <stdbool.h>

#define MAX(a, b) ((a) > (b) ? (a) : (b))

// CREATES A WINDOW WITH SPECIFIED X AND Y RESOLUTION
void setup(int _xres, int _yres);

// RESIZES THE WINDOW BY A FACTOR OF SIZE
void resize(int size);

// LOCKS VIDEO MEMORY
void lock(void);

// UNLOCKS AND PRESENTS VIDEO MEMORY TO THE WINDOW
void unlock(void);

// CLOSES WINDOW
void shutdown(void);

// WAITS SOME AMOUNT OF MILLISECONDS
void delay(int ms);

// RETURNS THE PIXEL VALUE IN VIDEO MEMORY
uint32_t get(int x, int y);

// PLACES A PIXEL IN VIDEO MEMORY
void put(int x, int y, uint32_t pixel);

// DRAWS A LINE IN VIDEO MEMORY
void line(int x0, int y0, int x1, int y1, uint32_t pixel);

// DRAWS A CIRCLE OUTLINE IN VIDEO MEMORY
void circle(int xm, int ym, int r, uint32_t pixel);

// DRAWS A FILLED IN CIRCLED IN VIDEO MEMORY
void filled_circle(int x0, int y0, int radius, uint32_t pixel);

// DRAWS A FILLED IN RECTANGLE IN VIDEO MEMORY
void filled_rect(int x0, int y0, int x1, int y1, uint32_t pixel);

// CLEARS VIDEO MEMORY
void clear(void);

// CLEARS VIDEO MEMORY WITH SPECIFIED COLOR
void clear_with_color(uint32_t color);

// RETURNS TRUE IF ESCAPE OR END KEYS WERE PUSHED
bool end(void);

// RETURNS THE NUMBER OF SECONDS SINCE PROGRAM HAS STARTED
float uptime(void);

// SEEDS THE FLOATING POINT RANDOM NUMBER GENERATOR
void fseed(void);

// RETURNS A RANDOM FLOATING POINT VALUE
float frand(float max);
