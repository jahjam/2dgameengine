
#include "Prop.h"
#include "Script.h"

template <typename T>
void Script::requireProp()
{
    m_scriptRequirements.set(Prop<T>::getName());
}
