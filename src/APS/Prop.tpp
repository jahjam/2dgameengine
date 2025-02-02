#include "Prop.h"

template <typename T>
int Prop<T>::getName()
{
    static auto name = nextName++;
    return name;
}
