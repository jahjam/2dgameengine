#include <cassert>
#include "Arena.h"

template <typename T>
Arena<T>::Arena(size_t cap) :
    _chunkCapacity(cap),
    _top(0),
    _memoryChunkRemaining(cap),
    _alignment(alignof(max_align_t)),
    _totalSize(_chunkCapacity)
{
    char* mem = static_cast<char*>(std::malloc(cap));

    if (!mem)
    {
        throw std::bad_alloc();
    }

    _memoryChain.push_back({.data = mem});
    _curChunk = 0;
};

template <typename T>
Arena<T>::~Arena()
{
    for (auto chunk : _memoryChain)
    {
        std::free(chunk.data);
    }
    _memoryChain.clear();
    _chunkCapacity = 0;
    _top = 0;
};

template <typename T>
void Arena<T>::_setMaxAlign()
{
    _alignment = alignof(max_align_t);
}

template <typename T>
size_t Arena<T>::_pos()
{
    return _top;
};

template <typename T>
size_t Arena<T>::_getMemoryRemaining()
{
    return _memoryChunkRemaining;
}

template <typename T>
void* Arena<T>::_pushNoZero()
{
    size_t size = sizeof(T);
    assert(size < _chunkCapacity && "Size of type larged that size of arena chunk");

    _alignment = alignof(T);

    size_t padding;
    _top % _alignment == 0 ? padding = 0 : padding = _alignment - (_top % _alignment);

    if (_top + padding + size > _chunkCapacity)
    {
        _memoryChain.push_back({.data = static_cast<char*>(std::malloc(_chunkCapacity))});
        _curChunk++;
        _top = 0;
        _memoryChunkRemaining = _chunkCapacity;
        _totalSize += _chunkCapacity;
        padding = 0;
    }

    size_t topAndPadding = _top + padding;
    void* nextPosition = _memoryChain[_curChunk].data + topAndPadding;
    _top += padding + size;
    _memoryChunkRemaining = _chunkCapacity - _top;
    return nextPosition;
};

template <typename T>
void* Arena<T>::_pushAligner()
{
    size_t alignment = alignof(T);

    assert((alignment & (alignment - 1)) == 0 && "Alignment must be a power of 2");

    size_t padding;

    _top % alignment == 0 ? padding = 0 : padding = alignment - (_top % alignment);

    if (_top + padding > _chunkCapacity)
    {
        _memoryChain.push_back({.data = static_cast<char*>(std::malloc(_chunkCapacity))});
        _curChunk++;
        _top = 0;
        _memoryChunkRemaining = _chunkCapacity;
        _totalSize += _chunkCapacity;
        padding = 0;
    }

    _top = _top + padding;
    void* nextPosition = _memoryChain[_curChunk].data + _top;
    return nextPosition;
};

template <typename T>
void* Arena<T>::_push()
{
    void* ptr = _pushNoZero();
    void* alloc = std::memset(ptr, 0, sizeof(T));
    return alloc;
};

template <typename T>
void Arena<T>::_pop()
{
    size_t size = sizeof(T);
    if (size >= _top && _curChunk != 0)
    {
        _memoryChain.erase(_memoryChain.begin() + _curChunk);
        _curChunk--;
        _top = _chunkCapacity;
        _memoryChunkRemaining = 0;
        _totalSize -= _chunkCapacity;
        return;
    };

    assert(size <= _top && "Can't pop off more size than is used");

    _top -= size;
    _memoryChunkRemaining += size;
};

template <typename T>
void Arena<T>::_clear()
{
    if (_curChunk > 0)
    {
        for (auto it = _memoryChain.begin() + 1; it != _memoryChain.end(); ++it)
        {
            std::free(it->data);
            it = _memoryChain.erase(it);
        }
        _curChunk = 0;
    }

    _top = 0;
    _memoryChunkRemaining = _chunkCapacity;
};
