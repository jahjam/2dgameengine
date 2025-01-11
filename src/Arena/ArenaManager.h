#pragma once

#include <vector>

#include "Actor.h"
#include "Arena.h"
#include "Prop.h"

class ArenaManager
{
    Arena *arena;
    std::vector<Block> toDestroy;

   public:
    ArenaManager() = default;
    ArenaManager(Arena &arena) : arena(&arena) {};
    ~ArenaManager();

    Actor *allocateActor(const Actor &actor);
    void deallocateActor(Actor *actor);
    Prop *allocateProp(const Prop &prop);
    void deallocateProp(Prop *prop);

    void cleanUp();
};
