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
    char *memory_;
    size_t totalSize_;
    std::list<Block> freeList_;

   public:
    Arena(size_t size);
    ~Arena();
    void *allocate_(size_t size);
    void deallocate_(void *ptr, size_t size);
};
