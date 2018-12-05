#pragma once

#define LOG(format, ...) log(__FILE__, __LINE__, format, __VA_ARGS__);

void log(const char file[], int line, const char* format, ...);

// Configuration -----------
#define SCREEN_SIZE 1
#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480
#define FPS 30
#define FULLSCREEN false
#define VSYNC true
#define TITLE "GMEngine"
#define INTERMITENT_FAST 0.3
#define INTERMITENT_SLOW 0.5