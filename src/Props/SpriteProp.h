#pragma once

#include <SDL2/SDL_rect.h>
#include <string>

struct SpriteProp
{
    SpriteProp(std::string assetId = "",
               float width = 0.0,
               float height = 0.0,
               int srcRectX = 0,
               int srcRectY = 0,
               u_int16_t z = 1) :
        height(height),
        width(width),
        assetId(assetId),
        srcRect({srcRectX, srcRectY, static_cast<int>(width), static_cast<int>(height)}),
        z(z)
    {
    }

    float width;
    float height;
    std::string assetId;
    SDL_Rect srcRect;
    u_int16_t z;
};
