#pragma once

#include <glm/ext/vector_float2.hpp>

#include "Prop.h"

// TODO: Add constant name to avoid
// typing errors
// const std::string

class TransformProp : public Prop
{
   protected:
    static Name name;
    static bool initialised;

   public:
    TransformProp(glm::vec2 position = glm::vec2(0.0, 0.0), glm::vec2 scale = glm::vec2(1.0, 1.0),
                  double rotation = 0.0)
    {
        if (!initialised)
        {
            this->name = nameCounter++;
            initialised = true;
        }

        this->position = position;
        this->scale = scale;
        this->rotation = rotation;
    }

    Name getName() const override { return this->name; }
    Prop* clone(void* memory) const override { return new (memory) TransformProp(*this); }
    size_t getSize() const override { return sizeof(TransformProp); };

    glm::vec2 position;
    glm::vec2 scale;
    double rotation;
};

Name TransformProp::name = 0;
bool TransformProp::initialised = false;
