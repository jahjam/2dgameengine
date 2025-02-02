#pragma once

#include <vector>
#include "APS.h"

class IStore
{
   public:
    virtual ~IStore() {}
};

template <typename T>
class Store : public IStore
{
   private:
    std::vector<T> m_propVarients;

   public:
    Store(size_t size = 100);

    virtual ~Store() = default;

    bool isEmpty() const;
    int getSize() const;
    void resize(size_t n);
    void clear();
    void add(T prop, Name& actorName);
    void remove(const Name& actorName);
    void set(size_t index, T object);
    T& get(size_t index);

    T& operator[](unsigned int index);
};
