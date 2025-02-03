#include "Director.h"

#include <SDL2/SDL_render.h>

#include "APS.h"
#include "Actor.h"

Director::Director() : m_actorManager(ArenaManager<Actor>()) {}

Director::~Director() {}

Actor *Director::hireActor() {
  Name actorName = this->numActors++;

  void *actorMem = m_actorManager._allocate();
  Actor *actor = new (actorMem) Actor(actorName);

  this->actorsToBeHired.insert(actor);

  if (actorName >= this->actorsProps.size()) {
    this->actorsProps.resize(actorName + 1);
  }

  return actor;
}

void Director::direct() {
  for (auto *actor : this->actorsToBeHired) {
    this->addActorToScript(actor);
  }
  this->actorsToBeHired.clear();

  // TODO: remove actors that are waiting to be fired
}

void Director::addActorToScript(Actor *actor) {
  const auto actorName = actor->getName();

  const auto &actorsCurProps = this->actorsProps[actorName];

  for (auto &script : this->m_scripts) {
    const auto &scriptPropRequirements =
        script.second->getScriptRequirements_();

    // an actor can have all the props available
    // but a script might just require two
    // so a simple comparison wouldn't work here
    // as they would be different
    // [actor = 11111111, script = 01001000]
    // we just want to know that the actor has
    // the required props, they can also have
    // more props but that doesn't matter here
    bool actorHasRequiredProps =
        (actorsCurProps & scriptPropRequirements) == scriptPropRequirements;

    if (actorHasRequiredProps) {
      script.second->addActor_(actor);
    }
  }
}

void Director::cleanUpActors() const {
  m_actorManager._clearFreeListAndArena();
}
