#pragma once

#include <cstddef>
#include <list>

struct Block
{
    void *data;
    size_t size;
};

class Arena
{
   private:
    char *memory;
    size_t totalSize;
    std::list<Block> freeList;

   public:
    Arena(size_t size);
    ~Arena();
    void *allocate(size_t size);
    void deallocate(void *ptr, size_t size);
};
