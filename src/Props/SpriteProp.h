#pragma once

#include "Prop.h"

class SpriteProp : public Prop
{
   protected:
    static Name name;
    static bool initialised;

   public:
    SpriteProp(float width = 10.0, float height = 10.0)
    {
        if (!initialised)
        {
            this->name = nameCounter++;
            initialised = true;
        }

        this->width = width;
        this->height = height;
    }

    Name getName() const override { return this->name; }
    Prop* clone(void* memory) const override { return new (memory) SpriteProp(*this); }
    size_t getSize() const override { return sizeof(SpriteProp); };

    float width;
    float height;
};

Name SpriteProp::name = 0;
bool SpriteProp::initialised = false;
