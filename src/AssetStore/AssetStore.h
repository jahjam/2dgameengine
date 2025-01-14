#pragma once

#include <SDL2/SDL_render.h>

#include <map>
#include <string>
class AssetStore
{
   private:
    SDL_Renderer* renderer;
    std::map<std::string, SDL_Texture*> textures;
    // TODO: create a map for fonts
    // TODO: create a map for audio

   public:
       AssetStore() = delete;
       AssetStore(SDL_Renderer* renderer);
       ~AssetStore();

       void clearAssets();
       void addTexture(const std::string& assetId, const std::string& filePath);
       SDL_Texture* getTexture(const std::string& assetId) const;
};
