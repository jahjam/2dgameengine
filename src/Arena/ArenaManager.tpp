#include <cstdlib>
#include <cstring>
#include "ArenaManager.h"

template <typename T>
void* ArenaManager<T>::_allocate()
{
    FreeListNode* firstFreeNode = _freeListNode;
    void* mem;

    if (firstFreeNode)
    {
        // get the memory block
        mem = firstFreeNode->mem;
        std::memset(mem, 0, _size);

        // handle freeing and next
        FreeListNode* next = firstFreeNode->next;
        _freeListNode = next;
        std::free(firstFreeNode);
    }
    else
    {
        _arena._setAutoAlign(_size);
        mem = _arena._push(_size);
    }

    return mem;
}

template <typename T>
void* ArenaManager<T>::_deallocate(void* ptr)
{
    FreeListNode* firstFreeNode = _freeListNode;
    FreeListNode* newNode = static_cast<FreeListNode*>(std::malloc(sizeof(FreeListNode)));

    if (firstFreeNode)
    {
        newNode->mem = ptr;
        newNode->next = nullptr;
        firstFreeNode->next = newNode;
    }
    else
    {
        newNode->mem = ptr;
        newNode->next = nullptr;
        _freeListNode = newNode;
    }

    return nullptr;
}

template <typename T>
void ArenaManager<T>::_clearFreeList()
{
    FreeListNode* cur = _freeListNode;
    while (cur != nullptr)
    {
        FreeListNode* temp = cur;
        cur = cur->next;
        std::free(temp);
    }
}

template <typename T>
void ArenaManager<T>::_clearFreeListAndArena()
{
    _clearFreeList();
    _arena._clear();
}
