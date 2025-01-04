#include "APS.h"
#include "easylogging++.h"
#include <algorithm>

//
// ACTOR
//
uint32_t Actor::getName() const { return this->name; };

//
// SCRIPT
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
