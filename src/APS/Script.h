#pragma once

#include <SDL2/SDL.h>

#include <unordered_map>
#include <vector>

#include "APS.h"
#include "Actor.h"
#include "Prop.h"
#include "Store.h"

class Script
{
   private:
    ScriptRequirements scriptRequirements;
    std::vector<Actor *> actors;

   public:
    Script() = default;
    virtual ~Script() = default;

    void addActor(Actor *actor);
    void removeActor(Actor *actor);
    const std::vector<Actor *> &getScriptActors();
    const ScriptRequirements &getScriptRequirements() const;

    // below functions aren't pure because a prop only uses
    // one or the other
    virtual void giveDirections(std::unordered_map<std::string, IStore *> *propStores,
                                double deltaTime) {};
    virtual void giveDirections(std::unordered_map<std::string, IStore *> *propStores,
                                SDL_Renderer *renderer) {};
    virtual Script *clone() const = 0;
    // To use a script an actor must have
    // specific props and those are set/required
    // in a script here
    void requireProp(const Prop &prop);
};
