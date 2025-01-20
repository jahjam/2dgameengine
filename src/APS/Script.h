#pragma once

#include <SDL2/SDL.h>

#include <unordered_map>
#include <vector>

#include "APS.h"
#include "Actor.h"
#include "AssetStore.h"
#include "Prop.h"
#include "Store.h"

class Script
{
   private:
    ScriptRequirements scriptRequirements_;
    std::vector<Actor *> actors_;

   public:
    Script() = default;
    virtual ~Script() = default;

    void addActor_(Actor *actor);
    void removeActor_(Actor *actor);
    const std::vector<Actor *> &getScriptActors_();
    const ScriptRequirements &getScriptRequirements_() const;

    // below functions aren't pure because a prop only uses
    // one or the other
    virtual void giveDirections_(std::unordered_map<std::string, IStore *> *propStores,
                                 double deltaTime) {};
    virtual void giveDirections_(std::unordered_map<std::string, IStore *> *propStores,
                                 SDL_Renderer *renderer, AssetStore *assetStore) {};
    virtual Script *clone_() const = 0;
    // To use a script an actor must have
    // specific props and those are set/required
    // in a script here
    void requireProp_(const Prop &prop);
};
