#ifndef MOVEMENTSCRIPT_H
#define MOVEMENTSCRIPT_H

#include "APS.h"

class MovementScript : Script {
public:
  MovementScript() {}

  void update() override {}

  Script *clone() const override { return new MovementScript(*this); };
};

#endif
