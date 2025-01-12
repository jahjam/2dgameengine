#include "Utils.h"

#include <unordered_map>

size_t Utils::generateUniqueName(std::type_index type)
{
    static size_t nameCounter = 0;
    static std::unordered_map<std::type_index, size_t> registry;

    auto it = registry.find(type);

    if (it == registry.end())
    {
        registry.insert({type, nameCounter++});
    }

    return registry.find(type)->second;
};
