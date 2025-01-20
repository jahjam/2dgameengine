#include "Stage.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <fstream>

#include "MovementScript.h"
#include "RenderScript.h"
#include "SpriteProp.h"
#include "TransformProp.h"
#include "easylogging++.h"

Stage::Stage()
{
    isRunning_ = false;
    director_ = new Director();
    LOG(INFO) << "Game constructor called";
}

Stage::~Stage()
{
    delete director_;
    delete assetStore_;
    LOG(INFO) << "Game destructor called";
}

void Stage::initialise_()
{
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        LOG(ERROR) << "Error initialising SDL";
        return;
    }
    window_ = SDL_CreateWindow(NULL, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1366, 768,
                               SDL_WINDOW_BORDERLESS);
    if (!window_)
    {
        LOG(ERROR) << "Error creating SDL window";
        return;
    }

    renderer_ = SDL_CreateRenderer(window_, -1, SDL_RENDERER_PRESENTVSYNC);

    if (!renderer_)
    {
        LOG(ERROR) << "Error creating SDL renderer";
        return;
    }

    assetStore_ = new AssetStore(renderer_);
    // SDL_SetWindowFullscreen(window_, SDL_WINDOW_FULLSCREEN);

    isRunning_ = true;
}

void Stage::destroy_()
{
    SDL_DestroyRenderer(renderer_);
    SDL_DestroyWindow(window_);
    SDL_Quit();
}

void Stage::render_()
{
    SDL_SetRenderDrawColor(renderer_, 21, 21, 21, 255);
    SDL_RenderClear(renderer_);

    director_->readScript(director_->getScript(RenderScript()), renderer_, assetStore_);

    SDL_RenderPresent(renderer_);
}

void Stage::run_()
{
    setup_();
    while (isRunning_)
    {
        processInput_();
        update_();
        render_();
    }
}

void Stage::loadLevel_(u_int8_t level)
{
    /*
    // Below code is the beginning of thinking about scaling sprites to fit
    // screen size exactly
    int width = 800;
    int height = 700;
    int mapWidth = 25;
    int mapHeight = 20;
    float scaleX = static_cast<float>(width) / (mapWidth * tileSize);
    float scaleY = static_cast<float>(height) / (mapHeight * tileSize);
    float scale = std::min(scaleX, scaleY);
*/
    int tileSize = 32;
    float scale = 2.0;

    // Add the scripts that a required in this level
    director_->prepareScript(MovementScript());
    director_->prepareScript(RenderScript());

    // Add the tilemap
    assetStore_->addTexture("tilemap", "./assets/tilemaps/jungle.png");

    // Load level file
    // TODO: this all needs to be its own function
    std::string filePath = "./assets/tilemaps/jungle.map";
    std::ifstream file(filePath);

    if (!file.is_open())
    {
        LOG(ERROR) << "Could not open file" << filePath;
    }

    std::string line;
    int xCounter = 0;
    int yCounter = 0;
    while (std::getline(file, line))
    {
        std::istringstream stream(line);
        std::string token;

        while (std::getline(stream, token, ','))
        {
            int tileNumber = std::stoi(token);
            int row = token[0] - '0';
            int column = token[1] - '0';

            Name tile = director_->hireActor()->getName();
            SpriteProp tileSprite = SpriteProp("tilemap", 32.0, 32.0, column * 32.0, row * 32.0, 0);
            TransformProp tileTransform =
                TransformProp(glm::vec2(xCounter * (tileSize * static_cast<int>(scale)),
                                        yCounter * (tileSize * static_cast<int>(scale))),
                              glm::vec2(scale, scale), 0.0);
            director_->giveProp("TransformProp", tileTransform, tile);
            director_->giveProp("SpriteProp", tileSprite, tile);

            xCounter += 1;
        }

        xCounter = 0;
        yCounter += 1;
    }

    // Create tank actor
    Name tank = director_->hireActor()->getName();
    assetStore_->addTexture("tank-image", "./assets/images/tank-tiger-right.png");
    TransformProp tankTransform = TransformProp(glm::vec2(10.0, 30.0), glm::vec2(1.0, 1.0), 0.0);
    RigidBodyProp tankRigidBody = RigidBodyProp(glm::vec2(30.0, 0.0));
    SpriteProp tankSprite = SpriteProp("tank-image");

    // Give props
    director_->giveProp("TransformProp", tankTransform, tank);
    director_->giveProp("RigidBodyProp", tankRigidBody, tank);
    director_->giveProp("SpriteProp", tankSprite, tank);
}

void Stage::setup_() { loadLevel_(1); }

void Stage::update_()
{
    int timeToWait = MS_PER_FRAME - (SDL_GetTicks() - msPreviousFrame_);
    if (timeToWait > 0 && timeToWait <= MS_PER_FRAME)
    {
        SDL_Delay(timeToWait);
    }

    double deltaTime = (SDL_GetTicks() - msPreviousFrame_) / 1000.0f;

    msPreviousFrame_ = SDL_GetTicks();

    // read all scripts
    director_->readScript(director_->getScript(MovementScript()), deltaTime);

    // take everything and direct
    director_->direct();

    // this cleans up the memory allocated
    // in the arena that has been freed
    // anytime within the current frame
    director_->cleanUp();
}

void Stage::processInput_()
{
    SDL_Event sdlEvent;
    while (SDL_PollEvent(&sdlEvent))
    {
        switch (sdlEvent.type)
        {
            case SDL_QUIT:
                isRunning_ = false;
                break;
            case SDL_KEYDOWN:
                if (sdlEvent.key.keysym.sym == SDLK_ESCAPE)
                {
                    isRunning_ = false;
                }
                break;
        }
    }
}
