#include "./AssetStore.h"

#include <SDL2/SDL_image.h>

#include "easylogging++.h"

AssetStore::AssetStore(SDL_Renderer *renderer) {
  this->renderer = renderer;
  LOG(INFO) << "AssetStore constructor called";
}

AssetStore::~AssetStore() {
  this->clearAssets();
  LOG(INFO) << "AssetStore destructor called";
}

void AssetStore::clearAssets() {
  for (auto texture : textures) {
    SDL_DestroyTexture(texture.second);
  }

  textures.clear();
}

void AssetStore::addTexture(const std::string &assetId,
                            const std::string &filePath) {
  SDL_Texture *texture = IMG_LoadTexture(this->renderer, filePath.c_str());

  if (!texture) {
    LOG(ERROR) << "Texture/IMG error:" << IMG_GetError();
  }

  this->textures.emplace(assetId, texture);
};

SDL_Texture *AssetStore::getTexture(const std::string &assetId) const {
  return this->textures.at(assetId);
};
