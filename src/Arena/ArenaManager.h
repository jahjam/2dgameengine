#pragma once

#include "Arena.h"

struct FreeListNode {
  void *mem;
  FreeListNode *next;
};

template <typename T> class ArenaManager {
private:
  FreeListNode *_freeListNode;
  Arena<T> _arena;
  size_t _size;

public:
  ArenaManager()
      : _arena(Arena<T>()), _freeListNode(nullptr), _size(sizeof(T)) {}
  ~ArenaManager() { _clearFreeList(); };

  void *_allocate();
  void *_deallocate(void *ptr);
  void _clearFreeList() const;
  void _clearFreeListAndArena() const;
};

#include "ArenaManager.tpp"
