#include "Script.h"

#include <algorithm>

#include "easylogging++.h"

void Script::addActor_(Actor* actor)
{
    this->m_actors.push_back(actor);
};

void Script::removeActor_(Actor* actor)
{
    auto actorIt = std::find_if(this->m_actors.begin(), this->m_actors.end(),
                                [actor](Actor* otherActor) { return *otherActor == *actor; });

    if (actorIt != this->m_actors.end())
    {
        this->m_actors.erase(actorIt);
    }
    else
    {
        LOG(WARNING) << "Actor (" << actor->getName() << ") not found";
    }
};

const std::vector<Actor*>& Script::getScriptActors_()
{
    return this->m_actors;
};

const ScriptRequirements& Script::getScriptRequirements_() const
{
    return this->m_scriptRequirements;
};
