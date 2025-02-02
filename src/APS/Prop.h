#pragma once

struct IProp
{
   protected:
    static int nextName;
};

// Used to assign a unique id to a component type
template <typename T>
class Prop : public IProp
{
    // Returns the unique id of Component<T>
    static int getName();
};
