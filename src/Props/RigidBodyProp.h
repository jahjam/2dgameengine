#pragma once

#include <glm/glm.hpp>

struct RigidBodyProp
{
    RigidBodyProp(glm::vec2 velocity = glm::vec2(0.0, 0.0)) : velocity(velocity) {}

    glm::vec2 velocity;
};
