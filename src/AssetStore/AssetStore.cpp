#include "./AssetStore.h"

#include <SDL2/SDL_image.h>

#include "easylogging++.h"

AssetStore::AssetStore(SDL_Renderer* renderer)
{
    this->renderer = renderer;
    LOG(INFO) << "AssetStore constructor called";
}

AssetStore::~AssetStore()
{
    this->clearAssets();
    LOG(INFO) << "AssetStore destructor called";
}

void AssetStore::clearAssets()
{
    for (auto texture : textures)
    {
        SDL_DestroyTexture(texture.second);
    }

    textures.clear();
}

void AssetStore::addTexture(const std::string& assetId, const std::string& filePath)
{
    SDL_Surface* surface = IMG_Load(filePath.c_str());

    if (!surface) {
        LOG(ERROR) << "Surface failed to load, something might be wrong with the file path";
    }

    SDL_Texture* texture = SDL_CreateTextureFromSurface(this->renderer, surface);
    SDL_FreeSurface(surface);

    this->textures.emplace(assetId, texture);
};

SDL_Texture* AssetStore::getTexture(const std::string& assetId) const
{
    return this->textures.at(assetId);
};
