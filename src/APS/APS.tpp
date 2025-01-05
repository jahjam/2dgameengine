#include "APS.h"

//
// Script
//

template <typename T> void Script::requireProp() {
  const auto propName = Prop<T>::getName();
  scriptRequirements.set(propName);
}

//
// Prop
//

template <typename T> uint32_t Prop<T>::getName() {
  static auto name = nameCounter++;
  return name;
}

//
// Director
//

bool propHasNoStore(uint32_t &propName, std::vector<IStore *> &propStores) {
  return propName >= propStores.size() || !propStores[propName];
};

template <typename T> void Director::giveProp(Actor &actor, Prop<T> &prop) {
  const auto propName = prop.getName();
  const auto actorName = actor.getName();

  if (propHasNoStore(propName, this->propStores)) {
    Store<T> *newPropStore = new Store<T>();
    this->propStores[propName] = newPropStore;
  }

  Store<T> *propStore = Store<T>(this->propStores[propName]);

  if (actorName >= propStore->getSize()) {
    propStore->resize(this->numActors);
  }

  propStore->set(actorName, prop);

  this->actorsProps[actorName].set(propName);
}

template <typename T> void Director::removeProp(Actor &actor) {
  const auto propName = Prop<T>::getName();
  const auto actorName = actor.getName();

  if (propHasNoStore(propName, this->propStores)) {
    return;
  }

  Store<T> *propStore = this->propStores[propName];
  propStore->remove(actorName);
  this->actorsProps[actorName].set(propName, false);
}

template <typename T> bool Director::hasProp(Actor &actor) const {
  const auto propName = Prop<T>::getName();
  const auto actorName = actor.getName();

  return this->actorsProps[actorName].test(propName);
}

template <typename T, typename... TArgs>
void Director::giveScript(TArgs &&...args) {
  T *newScript = new T(std::forward<TArgs>(args)...);
  this->scripts.insert({std::type_index(typeid(T)), newScript});
}

template <typename T, typename... TArgs> void Director::removeScript() {
  this->scripts.erase(std::type_index(typeid(T)));
}

template <typename T> bool Director::hasScript() const {
  return this->scripts.find(std::type_index(typeid(T))) != this->scripts.end();
}

template <typename T> T &Director::getScript() const {
  auto script = this->scripts.find(std::type_index(typeid(T)));
  return *(std::static_pointer_cast<T>(script->second));
}