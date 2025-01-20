#include "ArenaManager.h"

ArenaManager::~ArenaManager() { delete arena_; }

Actor *ArenaManager::allocateActor_(const Actor &actor)
{
    void *memory = arena_->allocate_(sizeof(Actor));
    return new (memory) Actor(actor);
};

void ArenaManager::deallocateActor_(Actor *actor)
{
    actor->~Actor();
    toDestroy_.push_back({actor, sizeof(Actor)});
};

Prop *ArenaManager::allocateProp_(const Prop &prop)
{
    size_t size = prop.getSize();
    void *memory = arena_->allocate_(size);
    return prop.clone(memory);
};

void ArenaManager::deallocateProp_(Prop *prop)
{
    size_t size = prop->getSize();
    toDestroy_.push_back({prop, sizeof(size)});
};

void ArenaManager::cleanUp()
{
    if (toDestroy_.empty())
    {
        return;
    }
    for (Block block : toDestroy_)
    {
        arena_->deallocate_(block.data, block.size);
    }
    toDestroy_.clear();
};
