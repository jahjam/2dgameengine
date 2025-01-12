#include "ArenaManager.h"

ArenaManager::~ArenaManager() { delete this->arena; }

Actor *ArenaManager::allocateActor(const Actor &actor)
{
    void *memory = arena->allocate(sizeof(Actor));
    return new (memory) Actor(actor);
};

void ArenaManager::deallocateActor(Actor *actor)
{
    actor->~Actor();
    this->toDestroy.push_back({actor, sizeof(Actor)});
};

Prop *ArenaManager::allocateProp(const Prop &prop)
{
    size_t size = prop.getSize();
    void *memory = arena->allocate(size);
    return prop.clone(memory);
};

void ArenaManager::deallocateProp(Prop *prop)
{
    size_t size = prop->getSize();
    this->toDestroy.push_back({prop, sizeof(size)});
};

void ArenaManager::cleanUp()
{
    if (this->toDestroy.empty())
    {
        return;
    }
    for (Block block : this->toDestroy)
    {
        arena->deallocate(block.data, block.size);
    }
    this->toDestroy.clear();
};
