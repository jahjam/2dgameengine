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
    SDL_Window *window_;
    SDL_Renderer *renderer_;
    bool isRunning_;
    int msPreviousFrame_ = 0;

    Director *director_;
    AssetStore *assetStore_;

   public:
    Stage();
    ~Stage();
    void initialise_();
    void destroy_();
    void processInput_();
    void setup_();
    void loadLevel_(u_int8_t level);
    void update_();
    void render_();
    void run_();
};
