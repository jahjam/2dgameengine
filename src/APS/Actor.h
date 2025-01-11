#pragma once

#include "APS.h"

class Actor {
private:
  Name name;

public:
  Actor(Name name) : name(name) {};
  Name getName() const;

  bool operator==(const Actor &otherActor) const { return this->name == otherActor.getName(); }
  bool operator<(const Actor &otherActor) const {
    return this->name < otherActor.name;
  }
};
