#include "Arena.h"

#include "easylogging++.h"

Arena::Arena(size_t size)
{
    // generic char buffer of memory
    memory_ = new char[size];
    // the total size of the whole arena
    totalSize_ = size;

    // initially the whole arena is one block
    // in the list
    freeList_.push_back({memory_, size});
};

// if the Arena goes out of scope
// delete all the memory allocated
Arena::~Arena() { delete[] memory_; }

void *Arena::allocate_(size_t requestedSize)
{
    // here we are iterating through the linked list
    // to find the first block that has enough
    // memory left to contain the requested size
    // if [it(block): size = 1024]
    // and [requestedSize = 300]
    // we can use this block of memory
    for (auto it = freeList_.begin(); it != freeList_.end(); it++)
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
                freeList_.erase(it);
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

void Arena::deallocate_(void *ptr, size_t size)
{
    // this is adding back the memory block
    // to the free list for reuse
    freeList_.push_back({ptr, size});

    // we sort the list here to put the
    // memory blocks back in order so that
    // we can merge them back into one block
    // if there's two adjacent blocks,
    // ie: [0x1000, 256 bytes], [0x1100, 128 bytes], [0x2000, 64 bytes]
    // 0x1000 + 256 == 0x1100
    // (this is why it needs to be sorted)
    // ultimately attempting to consolidate everything
    // back into one block
    freeList_.sort([](const Block &a, const Block &b) { return a.data < b.data; });

    // get the first block of memory
    auto it = freeList_.begin();
    // as long as the pointer doesn't
    // hit end, keep iterating
    while (it != freeList_.end())
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
        if (next != freeList_.end() && (char *)(it->data) + it->size == next->data)
        {
            // increate the size of the current block
            // so that it 'consumes' the next block
            it->size += next->size;
            // then erase the next block
            freeList_.erase(next);
        }
        else
        {
            // if the current block doesn't
            // align with the next, we move on
            ++it;
        }
    }
};
