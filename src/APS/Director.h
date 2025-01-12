#pragma once

#include <SDL2/SDL.h>

#include <cstddef>
#include <set>
#include <string>
#include <typeindex>
#include <unordered_map>
#include <vector>

#include "APS.h"
#include "ArenaManager.h"
#include "Script.h"
#include "Store.h"

class Director
{
   private:
    size_t numActors = 0;

    // Each store contains all the varients of a certain prop type
    // ie:
    // [key = propName string], [value = IStore *prop]
    std::unordered_map<std::string, IStore *> propStores;

    // The ScriptRequirements let us know which props an actor possesses
    // [vector index = actorName]
    std::vector<ScriptRequirements> actorsProps;

    std::unordered_map<std::type_index, Script *> scripts;

    std::set<Actor *> actorsToBeHired;
    std::set<Actor *> actorsToBeFired;

    ArenaManager *manager;

   public:
    Director();
    ~Director();

    Actor *hireActor();
    void direct();

    // Prop management
    void giveProp(const std::string &propName, const Prop &prop, const Name actorName);
    void removeProp(const std::string &propName, const Name &actorName);
    bool hasProp(Name &actorName, Name &propName) const;

    // Script management
    void prepareScript(const Script &script);
    void removeScript(const Script &script);
    bool hasScript(const Script &script) const;
    Script &getScript(const Script &script) const;
    void readScript(Script &script, double deltaTime);
    void readScript(Script &script, SDL_Renderer *renderer, AssetStore *AssetStore);

    void addActorToScript(Actor *actor);

    void cleanUp() const;
};
