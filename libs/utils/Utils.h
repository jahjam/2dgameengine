#pragma once
#include <cstddef>
#include <typeindex>

namespace Utils
{
size_t generateUniqueName(std::type_index type);
}
