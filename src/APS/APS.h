#ifndef APS_H
#define APS_H

#include <bitset>
#include <cstdint>
#include <vector>

// Requirements typedef explaination:
// Think of this as a script's prop requirements
// A crude example: For two actors to use the StarWarsScript
// they would need (to name a couple) a LightSabreProp and a StarshipProp
// if they don't have those they can't use the StarWarsScript
const uint32_t MAX_PROPS = 32;
typedef std::bitset<MAX_PROPS> ScriptRequirements;

struct IProp {
protected:
  static uint32_t nameCounter;
};

template <typename T> class Prop : public IProp {
  static uint32_t getName();
};

class Actor {
private:
  uint32_t name;

public:
  Actor(uint32_t name) : name(name) {};
  uint32_t getName() const;

  bool operator==(uint32_t otherName) const { return this->name == otherName; }
};

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

class IBox {
public:
  virtual ~IBox() = 0;
};

template <typename T> class Box : public IBox {
private:
  std::vector<T> props;

public:
  Box(size_t size = 100) : props(size) {}
  virtual ~Box() override = default;
  bool isEmpty() const { return props.empty(); }
  size_t getSize() const { return props.size(); }
  void reSize(size_t n) { props.resize(n); }
  void clear() { props.clear(); }
  void add(T prop) { props.push_back(prop); }
  void set(size_t i, T prop) { props[i] = prop; }

  T &operator[](uint32_t i) { return props[i]; }
};

class Director {
private:
  uint32_t numActors = 0;
  std::vector<IBox *> propBoxes;
};

#endif
