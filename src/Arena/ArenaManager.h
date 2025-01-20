#pragma once

#include <vector>

#include "Actor.h"
#include "Arena.h"
#include "Prop.h"

class ArenaManager
{
    Arena *arena_;
    std::vector<Block> toDestroy_;

   public:
    ArenaManager() = default;
    ArenaManager(Arena &arena) : arena_(&arena) {};
    ~ArenaManager();

    Actor *allocateActor_(const Actor &actor);
    void deallocateActor_(Actor *actor);
    Prop *allocateProp_(const Prop &prop);
    void deallocateProp_(Prop *prop);

    void cleanUp();
};
