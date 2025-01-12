#include "Director.h"

#include <SDL2/SDL_render.h>

#include "easylogging++.h"

Director::Director()
{
    Arena *arena = new Arena(MAX_GAME_MEMORY);
    this->manager = new ArenaManager(*arena);
}

Director::~Director() { delete this->manager; }

bool propHasNoStore(const std::string &propName,
                    std::unordered_map<std::string, IStore *> &propStores)
{
    return propStores.find(propName) == propStores.end();
};

void Director::giveProp(const std::string &propName, const Prop &prop, const Name actorName)
{
    Prop *newProp = this->manager->allocateProp(prop);

    if (propHasNoStore(propName, this->propStores))
    {
        // NOTE: this should probably be managed by the arena
        // but currently not
        Store *newPropStore = new Store();
        this->propStores[propName] = newPropStore;
    }

    IStore *propStore = this->propStores[propName];

    if (actorName >= propStore->getSize())
    {
        propStore->resize(this->numActors);
    }

    propStore->add(newProp, actorName);
    this->actorsProps[actorName].set(prop.getName());
}

Actor *Director::hireActor()
{
    Name actorName = this->numActors++;

    Actor *actor = this->manager->allocateActor(Actor(actorName));

    this->actorsToBeHired.insert(actor);

    if (actorName >= this->actorsProps.size())
    {
        this->actorsProps.resize(actorName + 1);
    }

    return actor;
}

void Director::direct()
{
    for (auto *actor : this->actorsToBeHired)
    {
        this->addActorToScript(actor);
    }
    this->actorsToBeHired.clear();
}

void Director::addActorToScript(Actor *actor)
{
    const auto actorName = actor->getName();

    const auto &actorsCurProps = this->actorsProps[actorName];

    for (auto &script : this->scripts)
    {
        const auto &scriptPropRequirements = script.second->getScriptRequirements();

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

        if (actorHasRequiredProps)
        {
            script.second->addActor(actor);
        }
    }
}

void Director::removeProp(const std::string &propName, const Name &actorName)
{
    if (propHasNoStore(propName, this->propStores))
    {
        return;
    }

    IStore *propStore = this->propStores[propName];
    Prop *prop = propStore->get(actorName);

    // NOTE: this order is important
    this->actorsProps[actorName].set(prop->getName(), false);
    this->manager->deallocateProp(prop);
    propStore->remove(actorName);
}

bool Director::hasProp(Name &actorName, Name &propName) const
{
    return this->actorsProps[actorName].test(propName);
}

void Director::prepareScript(const Script &script)
{
    this->scripts.insert({std::type_index(typeid(script)), script.clone()});
};

void Director::removeScript(const Script &script)
{
    delete this->scripts[std::type_index(typeid(script))];
    this->scripts.erase(std::type_index(typeid(script)));
};

bool Director::hasScript(const Script &script) const
{
    return this->scripts.find(std::type_index(typeid(script))) != this->scripts.end();
};

Script &Director::getScript(const Script &script) const
{
    auto foundScript = this->scripts.find(std::type_index(typeid(script)));
    return *foundScript->second;
};

void Director::readScript(Script &script, double deltaTime)
{
    script.giveDirections(&this->propStores, deltaTime);
}

void Director::readScript(Script &script, SDL_Renderer *renderer, AssetStore *assetStore)
{
    script.giveDirections(&this->propStores, renderer, assetStore);
}

void Director::cleanUp() const { this->manager->cleanUp(); }
