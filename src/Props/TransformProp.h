#ifndef TRANSFORMPROP_H
#define TRANSFORMPROP_H

#include <glm/ext/vector_float2.hpp>

struct TransformProp {
  glm::vec2 position;
  glm::vec2 scale;
  double rotation;

  TransformProp(glm::vec2 position = glm::vec2(0, 0),
                glm::vec2 scale = glm::vec2(1, 1), double rotation = 0) {
    this->position = position;
    this->scale = scale;
    this->rotation = rotation;
  }
};

#endif
