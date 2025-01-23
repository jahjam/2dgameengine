#pragma once

#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>

#include <map>
#include <vector>

#include "Actor.h"
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

    // this should be moved to the Script level
    // as it can be useful in ALL scripts
    template <typename T>
    T *getActorProp(std::unordered_map<std::string, IStore *> *propStores, Actor *actor,
                    std::string propName)
    {
        auto endIt = propStores->end();
        auto propIt = propStores->find(propName);

        if (propIt == endIt)
        {
            LOG(FATAL) << "Tried to access a prop that doesn't exist";
        }

        T *prop = static_cast<T *>(propIt->second->get(actor->getName()));

        if (!prop)
        {
            LOG(FATAL) << "Casting has failed!";
        }

        return prop;
    }

    void renderActor(std::unordered_map<std::string, IStore *> *propStores, AssetStore *assetStore,
                     SDL_Renderer *renderer, Actor *actor)
    {
        TransformProp *tProp = getActorProp<TransformProp>(propStores, actor, "TransformProp");
        SpriteProp *sProp = getActorProp<SpriteProp>(propStores, actor, "SpriteProp");

        SDL_Texture *texture = assetStore->getTexture(sProp->assetId);
        SDL_Rect srcRect = sProp->srcRect;

        if (srcRect.w == 0 && srcRect.h == 0)
        {
            // get the height and width without having to pass it in explicitly
            SDL_QueryTexture(texture, NULL, NULL, &srcRect.w, &srcRect.h);
        }

        // if you've not specified h and w for a sprite, it'll be calculated
        // in srcRect in the above function, so use that instead
        auto spriteWidth = sProp->width ? sProp->width : srcRect.w;
        auto spriteHeight = sProp->height ? sProp->height : srcRect.h;

        SDL_Rect dstRect = {static_cast<int>(tProp->position.x),
                            static_cast<int>(tProp->position.y),
                            static_cast<int>(spriteWidth * tProp->scale.x),
                            static_cast<int>(spriteHeight * tProp->scale.y)};

        SDL_RenderCopyEx(renderer, texture, &srcRect, &dstRect, tProp->rotation, NULL,
                         SDL_FLIP_NONE);
    }

    void giveDirections_(std::unordered_map<std::string, IStore *> *propStores,
                         SDL_Renderer *renderer, AssetStore *assetStore) override
    {
        // sort actors into their yBuckets
        for (auto actor : this->getScriptActors_())
        {
            TransformProp *tProp = getActorProp<TransformProp>(propStores, actor, "TransformProp");
            SpriteProp *sProp = getActorProp<SpriteProp>(propStores, actor, "SpriteProp");

            bool actorIsNotTileMap = sProp->z != 0;
            if (actorIsNotTileMap)
            {
                float prevYPos = tProp->previousPosition.y;
                float curYPos = tProp->position.y;
                auto &yBucket = yBuckets[prevYPos];

                auto it = std::find(yBucket.begin(), yBucket.end(), actor);

                if (it == yBucket.end())
                {
                    yBucket.push_back(actor);
                }
                else if (prevYPos != curYPos)
                {
                    yBucket.erase(std::remove(yBucket.begin(), yBucket.end(), actor),
                                  yBucket.end());

                    if (yBucket.empty())
                    {
                        yBuckets.erase(prevYPos);
                    }

                    yBuckets[curYPos].push_back(actor);
                }
            }
            else
            {
                renderActor(propStores, assetStore, renderer, actor);
            }
        }

        // iterate the actors in the yBuckets
        // so that they render in correct y order
        for (auto [y, yBucket] : yBuckets)
        {
            for (auto actor : yBucket)
            {
                renderActor(propStores, assetStore, renderer, actor);
            }
        }
    }

    Script *clone_() const override { return new RenderScript(*this); };

    std::map<float, std::vector<Actor *>> yBuckets;
};
