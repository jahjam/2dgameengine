#pragma once

#include <SDL2/SDL.h>

#include <vector>

#include "APS.h"
#include "Actor.h"

class Script
{
   private:
    ScriptRequirements m_scriptRequirements;
    std::vector<Actor*> m_actors;

   public:
    Script() = default;
    ~Script() = default;

    void addActor_(Actor* actor);
    void removeActor_(Actor* actor);
    const std::vector<Actor*>& getScriptActors_();
    const ScriptRequirements& getScriptRequirements_() const;

    template <typename T>
    void requireProp();
};
