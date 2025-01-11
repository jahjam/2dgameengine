#pragma once

#include "APS.h"

class Prop {
public:
  ~Prop() = default;
  virtual Name getName() const;
  virtual Prop *clone(void *memory) const { return new (memory) Prop(*this); };
  virtual size_t getSize() const { return sizeof(Prop); };

protected:
  static Name nameCounter;
};
