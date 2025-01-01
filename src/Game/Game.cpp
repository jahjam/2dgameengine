#include "Game.h"
#include "easylogging++.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

Game::Game() {
  this->isRunning = false;
  LOG(INFO) << "Game constructor called";
}

Game::~Game() { LOG(ERROR) << "Game destructor called"; }

void Game::initialise() {
  if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
    LOG(ERROR) << "Error initialising SDL";
    return;
  }
  this->window =
      SDL_CreateWindow(NULL, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                       WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_BORDERLESS

      );
  if (!this->window) {
    LOG(ERROR) << "Error creating SDL window";
    return;
  }

  this->renderer =
      SDL_CreateRenderer(this->window, -1, SDL_RENDERER_PRESENTVSYNC);

  if (!this->renderer) {
    LOG(ERROR) << "Error creating SDL renderer";
    return;
  }
  SDL_SetWindowFullscreen(this->window, SDL_WINDOW_FULLSCREEN);

  this->isRunning = true;
}

void Game::destroy() {
  SDL_DestroyRenderer(this->renderer);
  SDL_DestroyWindow(this->window);
  SDL_Quit();
}

void Game::render() {
  SDL_SetRenderDrawColor(this->renderer, 21, 21, 21, 255);
  SDL_RenderClear(this->renderer);

  // Draw a PNG texture
  SDL_Surface *surface = IMG_Load("./assets/images/truck-ford-right.png");
  if (!surface) {
    LOG(ERROR) << "IMG_Load failed!";
    this->isRunning = false;
    return;
  }
  SDL_Texture *texture = SDL_CreateTextureFromSurface(this->renderer, surface);
  if (!texture) {
    LOG(ERROR) << "Loading texture failed!";
    this->isRunning = false;
    return;
  }

  SDL_FreeSurface(surface);

  SDL_Rect dstRect = {10, 10, surface->w, surface->h};
  SDL_RenderCopy(this->renderer, texture, NULL, &dstRect);
  SDL_DestroyTexture(texture);

  SDL_RenderPresent(this->renderer);
}

void Game::run() {
  while (this->isRunning) {
    this->processInput();
    this->update();
    this->render();
  }
}

void Game::setup() {}

void Game::update() {
  int timeToWait = MS_PER_FRAME - (SDL_GetTicks() - this->msPreviousFrame);
  if (timeToWait > 0 && timeToWait <= MS_PER_FRAME) {
    SDL_Delay(timeToWait);
  }

  double deltaTime = (SDL_GetTicks() - this->msPreviousFrame) / 1000.0f;

  msPreviousFrame = SDL_GetTicks();
}

void Game::processInput() {
  SDL_Event sdlEvent;
  while (SDL_PollEvent(&sdlEvent)) {
    switch (sdlEvent.type) {
    case SDL_QUIT:
      this->isRunning = false;
      break;
    case SDL_KEYDOWN:
      if (sdlEvent.key.keysym.sym == SDLK_ESCAPE) {
        this->isRunning = false;
      }
      break;
    }
  }
}
