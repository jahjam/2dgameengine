#include "Store.h"

IStore::~IStore() {}
void Store::add(Prop *prop, const Name &actorName)
{
    // NOTE: this method can possibly leave huge empty
    // gaps in the data structure if only actor 0
    // and actor 1000 has a specific prop
    // look up 'sparse sets' to maybe tackle this issue
    // we could use the sparse vector to push entities
    // onto and these point to the dense vector props
    if (actorName >= this->propVarients.size())
    {
        this->propVarients.resize(actorName + 1);
    }

    this->propVarients[actorName] = prop;
}
Prop *Store::get(Name actorName) { return this->propVarients[actorName]; }
size_t Store::getSize() { return this->propVarients.size(); };
void Store::resize(size_t num) { this->propVarients.resize(num); }
void Store::remove(const Name &actorName)
{
    this->propVarients.erase(this->propVarients.begin() + actorName);
}
