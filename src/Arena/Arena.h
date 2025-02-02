#pragma once

#include <cstddef>
#include <cstdlib>
#include <vector>

struct Chunk
{
    char* data;
};

class IArena
{
    virtual ~IArena() = default;

    virtual void _setMaxAlign() = 0;
    virtual size_t _pos() = 0;
    virtual size_t _getMemoryRemaining() = 0;
    virtual void* _pushNoZero() = 0;
    virtual void* _pushAligner() = 0;
    virtual void* _push() = 0;
    virtual void _pop() = 0;
    virtual void _clear() = 0;
};

template <typename T>
class Arena : public IArena
{
   private:
    size_t _chunkCapacity;
    size_t _totalSize;
    size_t _memoryChunkRemaining;
    size_t _top;
    size_t _alignment;
    std::vector<Chunk> _memoryChain;
    size_t _curChunk;

   public:
    Arena(size_t cap = 1024);
    ;
    ~Arena();

    void _setMaxAlign() override;
    size_t _pos() override;
    size_t _getMemoryRemaining() override;
    void* _pushNoZero() override;
    void* _pushAligner() override;
    void* _push() override;
    void _pop() override;
    void _clear() override;
};
