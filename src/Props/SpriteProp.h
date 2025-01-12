#pragma once

#include <SDL2/SDL_rect.h>

#include "Prop.h"

struct SpriteProp : public Prop
{
    SpriteProp(std::string assetId = "", float width = 10.0, float height = 10.0, int srcRectX = 0,
               int srcRectY = 0)
        : Prop(typeid(SpriteProp)),
          height(height),
          width(width),
          assetId(assetId),
          srcRect({srcRectX, srcRectY, static_cast<int>(width), static_cast<int>(height)})
    {
    }
    Prop* clone(void* memory) const override { return new (memory) SpriteProp(*this); }
    size_t getSize() const override { return sizeof(SpriteProp); };

    float width;
    float height;
    std::string assetId;
    SDL_Rect srcRect;
};
