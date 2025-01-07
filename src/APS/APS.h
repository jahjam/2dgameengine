#ifndef APS_H
#define APS_H

#include <bitset>
#include <cstdint>
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

// Typedefs
typedef size_t Name;

//
// Prop
//

struct IProp {
protected:
  static Name nameCounterI;

public:
  virtual IProp *clone() const = 0;
  virtual Name getName() const = 0;
};

class Prop : public IProp {
public:
  ~Prop() = default;
  virtual Prop *clone() const override { return new Prop(*this); };
  static Name getStaticName();
  Name getName() const override;
};

//
// Actor
//

class Actor {
private:
  Name name;

public:
  Actor(Name name) : name(name) {};
  Name getName() const;

  bool operator==(Name otherName) const { return this->name == otherName; }
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
  virtual void update() = 0;
  virtual Script *clone() const = 0;
  // To use a script an actor must have
  // specific props and those are set/required
  // in a script here
  void requireProp(Name propName);
};

//
// Store
//

class IStore {
public:
  virtual ~IStore() = 0;
  virtual size_t getSize() = 0;
  virtual void resize(size_t num) = 0;
  virtual void add(const IProp &prop, const Name &actorName) = 0;
  virtual void remove(const Name &actorName) = 0;
  virtual IProp *get(Name actorName) = 0;
  virtual IProp *operator[](size_t i) = 0;
};

class Store : public IStore {
private:
  // raw byte buffer
  std::vector<IProp *> propVarients;

public:
  Store(size_t size = 100) : propVarients(size) {}
  ~Store() override = default;
  size_t getSize() override;
  void resize(size_t num) override;
  void add(const IProp &prop, const Name &actorName) override;
  void remove(const Name &actorName) override;
  IProp *get(Name actorName) override;

  IProp *operator[](size_t i) override { return propVarients[i]; };
};

//
// Director
//

class Director {
private:
  size_t numActors = 0;

  // Each store contains all the varients of a certain prop type
  // ie:
  // [key = propName string], [value = actorName]
  std::unordered_map<std::string, IStore *> propStores;

  // The ScriptRequirements let us know which props an actor possesses
  // [vector index = actorName]
  std::vector<ScriptRequirements> actorsProps;

  std::unordered_map<std::type_index, Script *> scripts;

  std::set<Actor> actorsToBeHired;
  std::set<Actor> actorsToBeFired;

public:
  Director() = default;

  Actor hireActor();
  void direct();

  // Prop management
  void giveProp(const std::string &propName, const Name actorName,
                const Prop &prop);
  void removeProp(const std::string &propName, Name propId,
                  const Name &actorName);
  bool hasProp(Name &actorName, Name &propName) const;

  // Script management
  void giveScript(const Script &script);
  void removeScript(const Script &script);
  bool hasScript(const Script &script) const;
  Script &getScript(const Script &script) const;

  void addActorToScript(Actor actor);
};

#endif
