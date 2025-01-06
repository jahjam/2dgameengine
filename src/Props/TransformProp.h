#ifndef TRANSFORMPROP_H
#define TRANSFORMPROP_H

#include "APS.h"
#include <glm/ext/vector_float2.hpp>

class TransformProp : public Prop {
  glm::vec2 position;
  glm::vec2 scale;
  double rotation;

public:
  TransformProp(glm::vec2 position = glm::vec2(0, 0),
                glm::vec2 scale = glm::vec2(1, 1), double rotation = 0) {
    this->position = position;
    this->scale = scale;
    this->rotation = rotation;
  }

  Prop *clone() const override { return new TransformProp(*this); };
};

#endif
