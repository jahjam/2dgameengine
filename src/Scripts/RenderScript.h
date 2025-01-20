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
        this->requireProp_(TransformProp());
        this->requireProp_(SpriteProp());
    }

    void giveDirections_(std::unordered_map<std::string, IStore *> *propStores,
                         SDL_Renderer *renderer, AssetStore *assetStore) override
    {
        for (auto actor : this->getScriptActors_())
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

            SDL_Texture *texture = assetStore->getTexture(spriteProp->assetId);
            SDL_Rect srcRect = spriteProp->srcRect;

            if (srcRect.w == 0 && srcRect.h == 0)
            {
                // get the height and width without having to pass it in explicitly
                SDL_QueryTexture(texture, NULL, NULL, &srcRect.w, &srcRect.h);
            }

            // if you've not specified h and w for a sprite, it'll be calculated
            // in srcRect in the above function, so use that instead
            auto spriteWidth = spriteProp->width ? spriteProp->width : srcRect.w;
            auto spriteHeight = spriteProp->height ? spriteProp->height : srcRect.h;

            SDL_Rect dstRect = {static_cast<int>(transformProp->position.x),
                                static_cast<int>(transformProp->position.y),
                                static_cast<int>(spriteWidth * transformProp->scale.x),
                                static_cast<int>(spriteHeight * transformProp->scale.y)};

            SDL_RenderCopyEx(renderer, texture, &srcRect, &dstRect, transformProp->rotation, NULL,
                             SDL_FLIP_NONE);
        }
    }

    Script *clone_() const override { return new RenderScript(*this); };
};
