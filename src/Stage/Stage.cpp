#include "Stage.h"
#include "easylogging++.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

Stage::Stage() {
  this->isRunning = false;
  LOG(INFO) << "Game constructor called";
}

Stage::~Stage() { LOG(ERROR) << "Game destructor called"; }

void Stage::initialise() {
  if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
    LOG(ERROR) << "Error initialising SDL";
    return;
  }
  this->window =
      SDL_CreateWindow(NULL, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                       WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_BORDERLESS);
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

void Stage::destroy() {
  SDL_DestroyRenderer(this->renderer);
  SDL_DestroyWindow(this->window);
  SDL_Quit();
}

void Stage::render() {
  SDL_SetRenderDrawColor(this->renderer, 21, 21, 21, 255);
  SDL_RenderClear(this->renderer);

  // TODO:
  // Render some actors

  SDL_RenderPresent(this->renderer);
}

void Stage::run() {
  while (this->isRunning) {
    this->processInput();
    this->update();
    this->render();
  }
}

void Stage::setup() {
  // TODO:
  // Actor tank = director.CreateActor();
  // tank.addProp<TransformProp>();
  // tank.addProp<BoxColliderProp>();
  // tank.addProp<SpriteComponent>("./assets/images/tank");
}

void Stage::update() {
  int timeToWait = MS_PER_FRAME - (SDL_GetTicks() - this->msPreviousFrame);
  if (timeToWait > 0 && timeToWait <= MS_PER_FRAME) {
    SDL_Delay(timeToWait);
  }

  double deltaTime = (SDL_GetTicks() - this->msPreviousFrame) / 1000.0f;

  msPreviousFrame = SDL_GetTicks();

  // TODO:
  // MovementScript.update();
  // CollisionScript.update();
  // DamageScript.update();
}

void Stage::processInput() {
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
