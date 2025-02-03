
#include "Arena.h"
#include "Director.h"
#include "Prop.h"
#include <cassert>

bool propHasNoStore(const Name &propName, std::vector<IStore *> &propStores) {
  return propName >= propStores.size();
};

template <typename T, typename... TArgs>
void Director::giveProp(const Name actorName, Arena<T> &propArena,
                        Arena<Store<T>> &storeArena, TArgs &&...args) {
  const auto propName = Prop<T>::getName();

  void *propMem = propArena._push();
  T *newProp = new (propMem) T(std::forward<TArgs>(args)...);

  if (propHasNoStore(propName, this->propStores)) {
    propStores.resize(propName + 1, nullptr);
    void *storeMem = storeArena._push();
    T *newStore = new (storeMem) Store<T>();
    this->propStores[propName] = newStore;
  }

  Store<T> *propStore = this->propStores[propName];

  if (actorName >= propStore->getSize()) {
    propStore->resize(this->numActors);
  }

  propStore->add(newProp, actorName);
  this->actorsProps[actorName].set(propName);
}

template <typename T>
void Director::removeProp(Name actorName, Arena<T> &propArena) {
  auto propName = Prop<T>::getName();

  if (propHasNoStore(propName, this->propStores)) {
    return;
  }

  Store<T> *propStore = this->propStores[propName];
  T *prop = propStore->get(actorName);

  // NOTE: this order is important
  this->actorsProps[actorName].set(prop->getName(), false);
  propArena._pop();
  propStore->remove(actorName);
};

template <typename T> bool Director::hasProp(Name &actorName) const {
  auto propName = Prop<T>::getName();
  return actorsProps[actorName].test(propName);
};

template <typename T> T &Director::getProp(Name &actorName) const {
  assert(hasProp<T>(actorName) && "Actor doesn't have this prop!");
  auto propName = Prop<T>::getName();
  Store<T> *propStore = this->propStores[propName];
  return propStore->get(actorName);
};

template <typename T, typename... TArgs>
void Director::addScript(TArgs &&...args) {
  T *newScript = new T(std::forward(args)...);
  m_scripts.insert({std::type_index(typeid(newScript)), newScript});
};

template <typename T> void Director::removeScript(Arena<T> &scriptArena) {
  delete m_scripts[std::type_index(typeid(T))];
  m_scripts.erase(std::type_index(typeid(T)));
};

template <typename T> bool Director::hasScript() const {
  return m_scripts.find(std::type_index(typeid(T))) != m_scripts.end();
};
template <typename T> T &Director::getScript() const {
  assert(hasScript<T>() && "Can't get script. Script not found!");
  return m_scripts.find(std::type_index(typeid(T)));
};
