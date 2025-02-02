#pragma once

#include <SDL2/SDL.h>

#include <cstddef>
#include <set>
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
    // [index = prop name], [value = IStore *prop]
    std::vector<IStore*> propStores;

    // The ScriptRequirements let us know which props an actor possesses
    // [vector index = actorName]
    std::vector<ScriptRequirements> actorsProps;

    std::unordered_map<std::type_index, Script*> m_scripts;

    std::set<Actor*> actorsToBeHired;
    std::set<Actor*> actorsToBeFired;

    ArenaManager<Actor> m_actorManager;

   public:
    Director();
    ~Director();

    Actor* hireActor();
    void direct();
    void addActorToScript(Actor* actor);
    void cleanUp() const;

    template <typename T, typename... TArgs>
    void giveProp(Arena<T>& propArena,
                  Arena<Store<T>>& storeArena,
                  const Name actorName,
                  TArgs&&... args);
    template <typename T>
    void removeProp(Arena<T>& propArena, Name actorName);
    template <typename T>
    bool hasProp(Name& actorName) const;
    template <typename T>
    T& getProp(Name& actorName) const;

    template <typename T, typename... TArgs>
    void addScript(Arena<T>& scriptArena, TArgs&&... args);
    template <typename T>
    void removeScript(Arena<T>& scriptArena);
    template <typename T>
    bool hasScript() const;
    template <typename T>
    T& getScript() const;
};
