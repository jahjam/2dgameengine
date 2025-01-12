#pragma once

#include "Prop.h"
#include <glm/glm.hpp>

struct RigidBodyProp : public Prop
{
    RigidBodyProp(glm::vec2 velocity = glm::vec2(0.0, 0.0))
        : Prop(typeid(RigidBodyProp))
        , velocity(velocity)
    {}
    Prop* clone(void* memory) const override { return new (memory) RigidBodyProp(*this); }
    size_t getSize() const override { return sizeof(RigidBodyProp); };

    glm::vec2 velocity;
};
