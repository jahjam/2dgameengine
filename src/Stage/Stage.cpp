#include "Stage.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "MovementScript.h"
#include "RenderScript.h"
#include "SpriteProp.h"
#include "TransformProp.h"
#include "easylogging++.h"

Stage::Stage()
{
    this->isRunning = false;
    this->director = new Director();
    LOG(INFO) << "Game constructor called";
}

Stage::~Stage()
{
    delete this->director;
    delete this->assetStore;
    LOG(INFO) << "Game destructor called";
}

void Stage::initialise()
{
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        LOG(ERROR) << "Error initialising SDL";
        return;
    }
    this->window = SDL_CreateWindow(NULL, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 500, 500,
                                    SDL_WINDOW_BORDERLESS);
    if (!this->window)
    {
        LOG(ERROR) << "Error creating SDL window";
        return;
    }

    this->renderer = SDL_CreateRenderer(this->window, -1, SDL_RENDERER_PRESENTVSYNC);

    if (!this->renderer)
    {
        LOG(ERROR) << "Error creating SDL renderer";
        return;
    }

    this->assetStore = new AssetStore(this->renderer);
    // SDL_SetWindowFullscreen(this->window, SDL_WINDOW_FULLSCREEN);

    this->isRunning = true;
}

void Stage::destroy()
{
    SDL_DestroyRenderer(this->renderer);
    SDL_DestroyWindow(this->window);
    SDL_Quit();
}

void Stage::render()
{
    SDL_SetRenderDrawColor(this->renderer, 21, 21, 21, 255);
    SDL_RenderClear(this->renderer);

    this->director->readScript(this->director->getScript(RenderScript()), this->renderer,
                               this->assetStore);

    SDL_RenderPresent(this->renderer);
}

void Stage::run()
{
    this->setup();
    while (this->isRunning)
    {
        this->processInput();
        this->update();
        this->render();
    }
}

void Stage::setup()
{
    // Add the scripts that a required
    this->director->prepareScript(MovementScript());
    this->director->prepareScript(RenderScript());

    this->assetStore->addTexture("tank-image", "./assets/images/tank-tiger-right.png");

    // Create actors
    Name tank = this->director->hireActor()->getName();
    TransformProp tankTransform = TransformProp(glm::vec2(10.0, 30.0), glm::vec2(1.0, 1.0), 0.0);
    RigidBodyProp tankRigidBody = RigidBodyProp(glm::vec2(30.0, 0.0));
    SpriteProp tankSprite = SpriteProp("tank-image");

    // Give actors props
    this->director->giveProp("TransformProp", tankTransform, tank);
    this->director->giveProp("RigidBodyProp", tankRigidBody, tank);
    this->director->giveProp("SpriteProp", tankSprite, tank);
}

void Stage::update()
{
    int timeToWait = MS_PER_FRAME - (SDL_GetTicks() - this->msPreviousFrame);
    if (timeToWait > 0 && timeToWait <= MS_PER_FRAME)
    {
        SDL_Delay(timeToWait);
    }

    double deltaTime = (SDL_GetTicks() - this->msPreviousFrame) / 1000.0f;

    msPreviousFrame = SDL_GetTicks();

    // read all scripts
    this->director->readScript(this->director->getScript(MovementScript()), deltaTime);

    // take everything and direct
    this->director->direct();

    // this cleans up the memory allocated
    // in the arena that has been freed
    // anytime within the current frame
    this->director->cleanUp();
}

void Stage::processInput()
{
    SDL_Event sdlEvent;
    while (SDL_PollEvent(&sdlEvent))
    {
        switch (sdlEvent.type)
        {
            case SDL_QUIT:
                this->isRunning = false;
                break;
            case SDL_KEYDOWN:
                if (sdlEvent.key.keysym.sym == SDLK_ESCAPE)
                {
                    this->isRunning = false;
                }
                break;
        }
    }
}
