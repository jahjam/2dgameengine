#include "APS.h"
#include "easylogging++.h"
#include <algorithm>
#include <utility>

//
// PROP
//

Name Prop::getStaticName() {
  static Name name = nameCounterI++;
  return name;
}

Name Prop::getName() const { return this->getStaticName(); }

Name IProp::nameCounterI = 0;

//
// ACTOR
//
//
Name Actor::getName() const { return this->name; };

//
// SCRIPT
//
//

void Script::requireProp(Name propName) { scriptRequirements.set(propName); }

void Script::addActorToScript(Actor actor) { this->actors.push_back(actor); };

void Script::removeActorFromScript(Actor actor) {
  auto actorIt =
      std::find(this->actors.begin(), this->actors.end(), actor.getName());

  if (actorIt != this->actors.end()) {
    this->actors.erase(actorIt);
  } else {
    LOG(WARNING) << "Actor (" << actor.getName() << ") not found";
  }
};

const std::vector<Actor> &Script::getScriptActors() { return this->actors; };

const ScriptRequirements &Script::getScriptRequirements() const {
  return this->scriptRequirements;
};

//
// STORE
//
IStore::~IStore() {}
void Store::add(const IProp &prop, const Name &actorName) {
  if (actorName >= this->propVarients.size()) {
    this->propVarients.resize(actorName + 1);
  }

  this->propVarients[actorName] = prop.clone();
}
IProp *Store::get(Name actorName) { return this->propVarients[actorName]; }
size_t Store::getSize() { return this->propVarients.size(); };
void Store::resize(size_t num) { this->propVarients.resize(num); }
void Store::remove(const Name &actorName) {
  this->propVarients.erase(this->propVarients.begin() + actorName);
}

//
// DIRECTOR
//
bool propHasNoStore(const std::string &propName,
                    std::unordered_map<std::string, IStore *> &propStores) {
  return propStores.find(propName) == propStores.end();
};

void Director::giveProp(const std::string &propName, const Name actorName,
                        const Prop &prop) {

  if (propHasNoStore(propName, this->propStores)) {
    Store *newPropStore = new Store();
    this->propStores[propName] = newPropStore;
  }

  IStore *propStore = this->propStores[propName];

  if (actorName >= propStore->getSize()) {
    propStore->resize(this->numActors);
  }

  propStore->add(prop, actorName);

  LOG(INFO) << "Actor: " << actorName << "given prop: " << propName;

  for (const auto &pair : this->propStores) {
    LOG(INFO) << pair.first << ": " << (*pair.second)[0]->getName();
  }

  this->actorsProps[actorName].set(prop.getName());
}

Actor Director::hireActor() {
  Name actorName = this->numActors++;

  Actor actor = Actor(actorName);

  this->actorsToBeHired.insert(actor);

  if (actorName >= this->actorsProps.size()) {
    this->actorsProps.resize(actorName + 1);
  }

  LOG(INFO) << "Actor created with name:" << actorName;

  return actor;
}

void Director::direct() {
  for (auto &actor : this->actorsToBeHired) {
    this->addActorToScript(actor);
  }
  this->actorsToBeHired.clear();
}

void Director::addActorToScript(Actor actor) {
  const auto actorName = actor.getName();

  const auto &actorsProps = this->actorsProps[actorName];

  for (auto &script : this->scripts) {
    const auto &scriptPropRequirements = script.second->getScriptRequirements();

    // an actor can have all the props available
    // but a script might just require two
    // so a simple comparison wouldn't work here
    // as they would be different
    // [actor = 11111111, script = 01001000]
    // we just want to know that the actor has
    // the required props, they can also have
    // more props but that doesn't matter here
    bool actorHasRequiredProps =
        (actorsProps & scriptPropRequirements) == scriptPropRequirements;

    if (actorHasRequiredProps) {
      script.second->addActorToScript(actor);
    }
  }
}

void Director::removeProp(const std::string &propName, Name propId,
                          const Name &actorName) {
  if (propHasNoStore(propName, this->propStores)) {
    return;
  }

  IStore *propStore = this->propStores[propName];
  propStore->remove(actorName);
  this->actorsProps[actorName].set(propId, false);
}

bool Director::hasProp(Name &actorName, Name &propName) const {
  return this->actorsProps[actorName].test(propName);
}

void Director::giveScript(const Script &script) {
  this->scripts.insert({std::type_index(typeid(script)), script.clone()});
};

void Director::removeScript(const Script &script) {
  this->scripts.erase(std::type_index(typeid(script)));
};

bool Director::hasScript(const Script &script) const {
  return this->scripts.find(std::type_index(typeid(script))) !=
         this->scripts.end();
};

Script &Director::getScript(const Script &script) const {
  auto foundScript = this->scripts.find(std::type_index(typeid(script)));
  return *foundScript->second;
};
