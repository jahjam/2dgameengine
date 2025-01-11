#include "Script.h"
#include "easylogging++.h"
#include <algorithm>

void Script::requireProp(const Prop &prop) {
  scriptRequirements.set(prop.getName());
}

void Script::addActor(Actor *actor) { this->actors.push_back(actor); };

void Script::removeActor(Actor *actor) {
  auto actorIt = std::find_if(
      this->actors.begin(), this->actors.end(),
      [actor](Actor *otherActor) { return *otherActor == *actor; });

  if (actorIt != this->actors.end()) {
    this->actors.erase(actorIt);
  } else {
    LOG(WARNING) << "Actor (" << actor->getName() << ") not found";
  }
};

const std::vector<Actor *> &Script::getScriptActors() { return this->actors; };

const ScriptRequirements &Script::getScriptRequirements() const {
  return this->scriptRequirements;
};
