#pragma once

#include <bitset>
#include <cstdint>

// Requirements typedef explaination:
// Think of this as a script's prop requirements
// A crude example: For two actors to use the StarWarsScript
// they would need (to name a couple) a LightSabreProp and a StarshipProp
// if they don't have those they can't use the StarWarsScript
const uint32_t MAX_PROPS = 32;
typedef std::bitset<MAX_PROPS> ScriptRequirements;

// Max game memory assigned at start of app
// (this can be fixed later to not just assign
// loads of memory from the get go, but for now
// it's fine)
const size_t MAX_GAME_MEMORY = 524288;

// Typedefs
typedef size_t Name;
