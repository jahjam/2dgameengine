#include "Script.h"

#include <algorithm>

#include "easylogging++.h"

void Script::requireProp_(const Prop &prop) { scriptRequirements_.set(prop.getName()); }

void Script::addActor_(Actor *actor) { this->actors_.push_back(actor); };

void Script::removeActor_(Actor *actor)
{
    auto actorIt = std::find_if(this->actors_.begin(), this->actors_.end(),
                                [actor](Actor *otherActor) { return *otherActor == *actor; });

    if (actorIt != this->actors_.end())
    {
        this->actors_.erase(actorIt);
    }
    else
    {
        LOG(WARNING) << "Actor (" << actor->getName() << ") not found";
    }
};

const std::vector<Actor *> &Script::getScriptActors_() { return this->actors_; };

const ScriptRequirements &Script::getScriptRequirements_() const
{
    return this->scriptRequirements_;
};
