#pragma once

#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>

#include "Script.h"
#include "SpriteProp.h"
#include "TransformProp.h"
#include "easylogging++.h"

class RenderScript : public Script
{
   public:
    RenderScript()
    {
        this->requireProp(TransformProp());
        this->requireProp(SpriteProp());
    }

    void giveDirections(std::unordered_map<std::string, IStore *> *propStores,
                        SDL_Renderer *renderer) override
    {
        for (auto actor : this->getScriptActors())
        {
            auto endIt = propStores->end();
            auto tranformIt = propStores->find("TransformProp");
            auto spriteIt = propStores->find("SpriteProp");

            if (tranformIt == endIt || spriteIt == endIt)
            {
                LOG(FATAL) << "Tried to access a prop that doesn't exist";
            }

            TransformProp *transformProp =
                static_cast<TransformProp *>(tranformIt->second->get(actor->getName()));
            SpriteProp *spriteProp =
                static_cast<SpriteProp *>(spriteIt->second->get(actor->getName()));

            if (!transformProp || !spriteProp)
            {
                LOG(FATAL) << "Casting has failed!";
            }

            SDL_Rect objRect = {static_cast<int>(transformProp->position.x),
                                static_cast<int>(transformProp->position.y),
                                static_cast<int>(spriteProp->width),
                                static_cast<int>(spriteProp->height)};

            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
            SDL_RenderFillRect(renderer, &objRect);
        }
    }

    Script *clone() const override { return new RenderScript(*this); };
};
