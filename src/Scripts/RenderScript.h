#pragma once

#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>

#include <algorithm>
#include <map>
#include <vector>

#include "Actor.h"
#include "AssetStore.h"
#include "Script.h"
#include "SpriteProp.h"
#include "Store.h"
#include "TransformProp.h"

class RenderScript : public Script {
public:
  RenderScript() {
    requireProp<TransformProp>();
    requireProp<SpriteProp>();
  }

  void renderActor(AssetStore *assetStore, SDL_Renderer *renderer,
                   Actor *actor) {
    TransformProp tProp = Store<TransformProp>().get(actor->getName());
    SpriteProp sProp = Store<SpriteProp>().get(actor->getName());

    SDL_Texture *texture = assetStore->getTexture(sProp.assetId);
    SDL_Rect srcRect = sProp.srcRect;

    if (srcRect.w == 0 && srcRect.h == 0) {
      // get the height and width of sprite without having to pass it in
      // explicitly
      SDL_QueryTexture(texture, NULL, NULL, &srcRect.w, &srcRect.h);
    }

    auto spriteWidth = sProp.width ? sProp.width : srcRect.w;
    auto spriteHeight = sProp.height ? sProp.height : srcRect.h;

    SDL_Rect dstRect = {static_cast<int>(tProp.position.x),
                        static_cast<int>(tProp.position.y),
                        static_cast<int>(spriteWidth * tProp.scale.x),
                        static_cast<int>(spriteHeight * tProp.scale.y)};

    SDL_RenderCopyEx(renderer, texture, &srcRect, &dstRect, tProp.rotation,
                     NULL, SDL_FLIP_NONE);
  }

  void giveDirections_(AssetStore *assetStore, SDL_Renderer *renderer) {
    // sort actors into their yBuckets
    for (auto actor : this->getScriptActors_()) {
      TransformProp tProp = Store<TransformProp>().get(actor->getName());
      SpriteProp sProp = Store<SpriteProp>().get(actor->getName());

      bool actorIsNotTileMap = sProp.z != 0;
      if (actorIsNotTileMap) {
        float prevYPos = tProp.previousPosition.y;
        float curYPos = tProp.position.y;
        auto &yBucket = yBuckets[prevYPos];

        auto it = std::find(yBucket.begin(), yBucket.end(), actor);

        if (it == yBucket.end()) {
          yBucket.push_back(actor);
        } else if (prevYPos != curYPos) {
          yBucket.erase(std::remove(yBucket.begin(), yBucket.end(), actor),
                        yBucket.end());

          if (yBucket.empty()) {
            yBuckets.erase(prevYPos);
          }

          yBuckets[curYPos].push_back(actor);
        }
      } else {
        renderActor(assetStore, renderer, actor);
      }
    }

    // iterate the actors in the yBuckets
    // so that they render in correct y order
    for (auto [y, yBucket] : yBuckets) {
      for (auto actor : yBucket) {
        renderActor(assetStore, renderer, actor);
      }
    }
  }

  std::map<float, std::vector<Actor *>> yBuckets;
};
