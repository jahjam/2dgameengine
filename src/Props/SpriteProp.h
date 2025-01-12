#pragma once

#include "Prop.h"

struct SpriteProp : public Prop
{
    SpriteProp(float width = 10.0, float height = 10.0)
        : Prop(typeid(SpriteProp))
        , height(height)
        , width(width)
    {}
    Prop* clone(void* memory) const override { return new (memory) SpriteProp(*this); }
    size_t getSize() const override { return sizeof(SpriteProp); };

    float width;
    float height;
};
