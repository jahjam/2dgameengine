#include "Store.h"

template <typename T>
Store<T>::Store(size_t size)
{
    m_propVarients.resize(size);
}

template <typename T>
bool Store<T>::isEmpty() const
{
    return m_propVarients.empty();
}

template <typename T>
int Store<T>::getSize() const
{
    return m_propVarients.size();
}

template <typename T>
void Store<T>::resize(size_t n)
{
    m_propVarients.resize(n);
}

template <typename T>
void Store<T>::clear()
{
    m_propVarients.clear();
}

template <typename T>
void Store<T>::add(T prop, Name& actorName)
{
    // NOTE: this method can possibly leave huge empty
    // gaps in the data structure if only actor 0
    // and actor 1000 has a specific prop
    // look up 'sparse sets' to maybe tackle this issue
    // we could use the sparse vector to push entities
    // onto and these point to the dense vector props
    if (actorName >= m_propVarients.size())
    {
        m_propVarients.resize(actorName + 1);
    }

    this->m_propVarients[actorName] = prop;
}

template <typename T>
void Store<T>::remove(const Name& actorName)
{
    m_propVarients.erase(m_propVarients.begin() + actorName);
}

template <typename T>
void Store<T>::set(size_t index, T object)
{
    m_propVarients[index] = object;
}

template <typename T>
T& Store<T>::get(size_t index)
{
    return static_cast<T&>(m_propVarients[index]);
}

template <typename T>
T& Store<T>::operator[](unsigned int index)
{
    return m_propVarients[index];
}
