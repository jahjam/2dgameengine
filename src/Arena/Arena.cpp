#include "Arena.h"

#include "easylogging++.h"

Arena::Arena(size_t size)
{
    // generic char buffer of memory
    this->memory = new char[size];
    // the total size of the whole arena
    this->totalSize = size;

    // initially the whole arena is one block
    // in the list
    this->freeList.push_back({memory, size});
};

// if the Arena goes out of scope
// delete all the memory allocated
Arena::~Arena() { delete[] this->memory; }

void *Arena::allocate(size_t requestedSize)
{
    // here we are iterating through the linked list
    // to find the first block that has enough
    // memory left to contain the requested size
    // if [it(block): size = 1024]
    // and [requestedSize = 300]
    // we can use this block of memory
    for (auto it = this->freeList.begin(); it != this->freeList.end(); it++)
    {
        if (it->size >= requestedSize)
        {
            // this is the current full block
            // of memory to grab from
            void *freeMemoryBlock = it->data;

            // calculate how much memory is left
            // in this block by subtracting
            // the requested size from the blocks size
            size_t remaining = it->size - requestedSize;
            if (remaining > 0)
            {
                // move the pointer along to the location
                // of the requestedSize
                it->data = (char *)it->data + requestedSize;
                it->size = remaining;
            }
            else
            {
                // here we erase the block if there's no
                // room left in it
                this->freeList.erase(it);
            }

            // return the original memory block
            // before it was amended in the above
            // if statement
            return freeMemoryBlock;
        }
    }

    // If no suitable block is found, throw an exception.
    // NOTE: We could create a new memory block here
    // if we want to, add that to the freeList, and return it,
    // but for simplicity at the moment just gonna crash
    LOG(FATAL) << "No more free memory to allocate!";
    throw std::bad_alloc();
};

void Arena::deallocate(void *ptr, size_t size)
{
    // this is adding back the memory block
    // to the free list for reuse
    this->freeList.push_back({ptr, size});

    // we sort the list here to put the
    // memory blocks back in order so that
    // we can merge them back into one block
    // if there's two adjacent blocks,
    // ie: [0x1000, 256 bytes], [0x1100, 128 bytes], [0x2000, 64 bytes]
    // 0x1000 + 256 == 0x1100
    // (this is why it needs to be sorted)
    // ultimately attempting to consolidate everything
    // back into one block
    this->freeList.sort([](const Block &a, const Block &b) { return a.data < b.data; });

    // get the first block of memory
    auto it = this->freeList.begin();
    // as long as the pointer doesn't
    // hit end, keep iterating
    while (it != this->freeList.end())
    {
        // get the next block of memory
        // (we need next in the while loop
        // as because we erase next below
        // on the next iteration of the free list
        // it will still be the same and
        // next will now point to the next
        // block (if there is one, of not
        // we move the iterator and the
        // while loop ends if that hits
        // the end))
        auto next = std::next(it);
        // if the size of the first block aligns
        // with the second block, we can consolidate
        // those blocks into one
        if (next != this->freeList.end() && (char *)(it->data) + it->size == next->data)
        {
            // increate the size of the current block
            // so that it 'consumes' the next block
            it->size += next->size;
            // then erase the next block
            this->freeList.erase(next);
        }
        else
        {
            // if the current block doesn't
            // align with the next, we move on
            ++it;
        }
    }
};
