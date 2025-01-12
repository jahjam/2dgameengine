#pragma once

#include <typeindex>

#include "APS.h"
#include "Utils.h"

class Prop
{
   public:
    Prop(std::type_index type) : name(Utils::generateUniqueName(type)) {};
    ~Prop() = default;
    Name getName() const;
    virtual Prop *clone(void *memory) const { return new (memory) Prop(*this); };
    virtual size_t getSize() const { return sizeof(Prop); };

private:
    Name name;
};
