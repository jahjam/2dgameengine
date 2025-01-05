#ifndef APS_H
#define APS_H

#include <bitset>
#include <cstdint>
#include <memory>
#include <set>
#include <typeindex>
#include <unordered_map>
#include <vector>

// Requirements typedef explaination:
// Think of this as a script's prop requirements
// A crude example: For two actors to use the StarWarsScript
// they would need (to name a couple) a LightSabreProp and a StarshipProp
// if they don't have those they can't use the StarWarsScript
const uint32_t MAX_PROPS = 32;
typedef std::bitset<MAX_PROPS> ScriptRequirements;

//
// Prop
//

struct IProp {
protected:
  static uint32_t nameCounter;
};

template <typename T> class Prop : public IProp {
  static uint32_t getName();
};

//
// Actor
//

class Actor {
private:
  uint32_t name;

public:
  Actor(uint32_t name) : name(name) {};
  uint32_t getName() const;

  bool operator==(uint32_t otherName) const { return this->name == otherName; }
  bool operator<(const Actor &otherActor) const {
    return this->name < otherActor.name;
  }
};

//
// Script
//

class Script {
private:
  ScriptRequirements scriptRequirements;
  std::vector<Actor> actors;

public:
  Script() = default;
  ~Script() = default;

  void addActorToScript(Actor actor);
  void removeActorFromScript(Actor actor);
  const std::vector<Actor> &getScriptActors();
  const ScriptRequirements &getScriptRequirements() const;

  // To use a script an actor must have
  // specific props and those are set/required
  // in a script here
  template <typename T> void requireProp();
};

//
// Store
//

class IStore {
public:
  virtual ~IStore() = 0;
};

template <typename T> class Store : public IStore {
private:
  std::vector<T> propVarients;

public:
  Store(size_t size = 100) : propVarients(size) {}
  virtual ~Store() override = default;
  bool isEmpty() const { return propVarients.empty(); }
  size_t getSize() const { return propVarients.size(); }
  void resize(size_t n) { propVarients.resize(n); }
  void clear() { propVarients.clear(); }
  void add(T prop) { propVarients.push_back(prop); }
  void set(size_t i, T prop) { propVarients[i] = prop; }
  void remove(uint32_t actorName) {
    propVarients.erase(propVarients.begin() + actorName);
  }
  T &operator[](uint32_t i) { return propVarients[i]; }
};

//
// Director
//

class Director {
private:
  uint32_t numActors = 0;

  // Each store contains all the varients of a certain prop type
  // ie:
  // [key = propName], [value = actorName]
  std::unordered_map<uint32_t, IStore *> propStores;

  // The ScriptRequirements let us know which props an actor possesses
  // [vector index = actorName]
  std::vector<ScriptRequirements> actorsProps;

  std::unordered_map<std::type_index, std::shared_ptr<Script>> scripts;

  std::set<Actor> actorsToBeHired;
  std::set<Actor> actorsToBeFired;

public:
  Director() = default;

  Actor hireActor();
  void direct();

  // Prop management
  template <typename T> void giveProp(Actor &actor, Prop<T> &prop);
  template <typename T> void removeProp(Actor &actor);
  template <typename T> bool hasProp(Actor &actor) const;

  // Script management
  template <typename T, typename... TArgs> void giveScript(TArgs &&...args);
  template <typename T, typename... TArgs> void removeScript();
  template <typename T> bool hasScript() const;
  template <typename T> T &getScript() const;

  void addActorToScript(Actor actor);
};

#endif
