#include "Store.h"

IStore::~IStore() {}
void Store::add(Prop *prop, const Name &actorName)
{
    if (actorName >= this->propVarients.size()) {
        this->propVarients.resize(actorName + 1);
    }

    this->propVarients[actorName] = prop;
}
Prop *Store::get(Name actorName)
{
    return this->propVarients[actorName];
}
size_t Store::getSize() { return this->propVarients.size(); };
void Store::resize(size_t num) { this->propVarients.resize(num); }
void Store::remove(const Name &actorName) {
  this->propVarients.erase(this->propVarients.begin() + actorName);
}
