#pragma once

#include "Prop.h"
#include <glm/ext/vector_float2.hpp>

class RigidBodyProp : public Prop {
protected:
    static Name name;
    static bool initialised;

public:
    RigidBodyProp(glm::vec2 velocity = glm::vec2(0.0, 0.0))
    {
        if (!this->initialised) {
            this->name = nameCounter++;
            this->initialised = true;
        }

        this->velocity = velocity;
    }

    Name getName() const override { return this->name; }
    Prop* clone(void* memory) const override { return new (memory) RigidBodyProp(*this); }
    size_t getSize() const override { return sizeof(RigidBodyProp); };

    glm::vec2 velocity;
};

Name RigidBodyProp::name = 0;
bool RigidBodyProp::initialised = false;
