#include "APS.h"
#include "easylogging++.h"
#include <algorithm>
#include <utility>

uint32_t IProp::nameCounter = 0;

//
// ACTOR
//
//
uint32_t Actor::getName() const { return this->name; };

//
// SCRIPT
//
//
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
// DIRECTOR
//

Actor Director::hireActor() {
  uint32_t actorName = this->numActors++;

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
