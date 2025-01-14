#pragma once

#include <SDL2/SDL.h>

#include "AssetStore.h"
#include "Director.h"

#define FPS 60
#define MS_PER_FRAME 1000 / FPS
#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

class Stage
{
   private:
    SDL_Window *window;
    SDL_Renderer *renderer;
    bool isRunning;
    int msPreviousFrame = 0;

    Director *director;
    AssetStore *assetStore;

public:
    Stage();
    ~Stage();
    void initialise();
    void destroy();
    void processInput();
    void setup();
    void update();
    void render();
    void run();
};
