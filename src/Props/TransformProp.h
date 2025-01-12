#pragma once

#include <glm/glm.hpp>

#include "Prop.h"

// TODO: Add constant name to avoid
// typing errors
// const std::string

struct TransformProp : public Prop
{
    TransformProp(glm::vec2 position = glm::vec2(0.0, 0.0),
                  glm::vec2 scale = glm::vec2(1.0, 1.0),
                  double rotation = 0.0)
        : Prop(typeid(TransformProp))
        , position(position)
        , scale(scale)
        , rotation(rotation)
    {}

    Prop* clone(void* memory) const override { return new (memory) TransformProp(*this); }
    size_t getSize() const override { return sizeof(TransformProp); };

    glm::vec2 position;
    glm::vec2 scale;
    double rotation;
};
