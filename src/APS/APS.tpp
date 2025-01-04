#include "APS.h"

template <typename T> void Script::requireProp() {
  const auto propName = Prop<T>::getName();
  scriptRequirements.set(propName);
}

template <typename T> uint32_t Prop<T>::getName() {
  static auto name = nameCounter++;
  return name;
}
