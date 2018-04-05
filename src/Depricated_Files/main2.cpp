#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <sstream>

#include "./Utilities/General_Purpose/Timer.h"
#include "./Utilities/Utility_Components/InputHandler.h"
#include "./Utilities/Utility_Components/Constants.h"

#include "./Actors/Character/Player.h"
#include "./Actors/Character/TestNonPlayer.h"
#include "./Level/Level.h"
#include "./Actors/Prop/Prop.h"
#include "./Actors/Particle/Particle.h"
#include "./Utilities/Color_Utilities/AEOIAFColor.h"
#include "./Actors/Character/Faction.h"

using namespace std;
using namespace AEOIAF_Utilities;
using namespace AEOIAF_Level;
using namespace AEOIAF_Actor;
using namespace AEOIAF_Content;
using namespace AEOIAF_AIBehavior;

const int SCREEN_FPS = 60;
const int SCREEN_TICKS_PER_FRAME = 1000 / SCREEN_FPS;

bool bEnableVsync;

SDL_Window* myWindow = NULL; //Window we'll be rendering to
SDL_Surface* mySurface = NULL; //The surface contained by the window
SDL_Renderer* myRenderer = NULL; //Renders textures

Player player;
TestSoldier soldier;
Level testLevel;
Prop simpleProp;
ParticleEmitter testEmitter;

bool Initialize(); //Starts SDL and makes window
bool LoadMedia(); //See method name
SDL_Texture* LoadTexture(string path);
void Close(); //Frees media and shuts down SDL

//Must have this type of main, otherwise you get an undefined reference to main.
//Uses this type so SDL can be easily ported to other platforms.

//Note: LevelLoader will add a dummy player at position 0 of character vector
//Note: Have another Update method for AI
int main(int argc, char* args[])
{
    bEnableVsync = false;

    if(!Initialize())
        cout << "Failed to initialize" << endl;

    else
    {
        if(!LoadMedia())
            cout << "Failed to load media" << endl;

        else
        {
            //Main loop flag
            bool bQuit = false;

            //Event handler
            SDL_Event e;

            //Timer timer;
            Timer fpsTimer;
            Timer capTimer;
            stringstream timeText; //Memory text stream

            int countedFrames = 0;
            fpsTimer.Start();

            //While application is runnin
            while(!bQuit)
            {
                if(!bEnableVsync)
                    capTimer.Start();

                //Handle all events on que
                //What this does is keep processing the event queue until it is empty.
                while(SDL_PollEvent(&e) != 0)
                {
                    //If user requests quit
                    if(e.type == SDL_QUIT)
                        bQuit = true;
                }

                InputHandler::Update();

                float avgFps = countedFrames / (fpsTimer.GetTicks() / 1000.0f);
                if(avgFps > 2000000) avgFps = 0;

                timeText.str("");
                timeText << "Average FPS: " << avgFps;

                //player.Update(&testLevel, &e);

                testLevel.Update(&e);
                testEmitter.Update(&testLevel, &e);
                soldier.Update(&testLevel, &e);
                //simpleProp.Update(&testLevel, &e);

                InputHandler::SavePreviousKeyboardState();

                SDL_SetRenderDrawColor(myRenderer, 100, 149, 237, 255);
                SDL_RenderClear(myRenderer);

                testLevel.Draw(myRenderer, &player.Camera().GetViewMatrix());
                //player.Draw(myRenderer, SDL_FLIP_NONE, false, false, false);
                /*simpleProp.Draw(myRenderer, SDL_FLIP_NONE, false, false, true,
                                &player.Camera().GetViewMatrix());*/
                soldier.Draw(myRenderer, SDL_FLIP_NONE, false, false, true,
                             &player.Camera().GetViewMatrix());

                testEmitter.Draw(myRenderer, SDL_FLIP_NONE, false, false, true, &player.Camera().GetViewMatrix());

                SDL_RenderPresent(myRenderer);
                ++countedFrames;

                if(!bEnableVsync)
                {
                    int frameTicks = capTimer.GetTicks();
                    if(frameTicks < SCREEN_TICKS_PER_FRAME)
                        SDL_Delay(SCREEN_TICKS_PER_FRAME - frameTicks);
                }
            }
        }
    }

    Close();

    return 0;
}

bool Initialize()
{
    //Initialization flag
    bool bSuccess = true;

    //Initialize SDL. Have to do this before actually using SDL
    if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0)
    {
        cout << "SDL Could not initialize: " << SDL_GetError() << endl;
        bSuccess = false;
    }

    else
    {
        myWindow = SDL_CreateWindow("An Engine of Ice and Fire",
                                    SDL_WINDOWPOS_UNDEFINED, //X position
                                    SDL_WINDOWPOS_UNDEFINED, //Y position
                                    Constants::SCREEN_WIDTH,
                                    Constants::SCREEN_HEIGHT,
                                    SDL_WINDOW_SHOWN); //Shows window upon creation

        if(myWindow == NULL)
        {
            cout << "Window could not be created: " << SDL_GetError() << endl;
            bSuccess = false;
        }

        else
        {
            //Create renderer for window
            myRenderer = bEnableVsync ? SDL_CreateRenderer(myWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC)
                                      : SDL_CreateRenderer(myWindow, -1, SDL_RENDERER_ACCELERATED);

            if(myRenderer == NULL)
            {
                cout << "Renderer could not be created: " << SDL_GetError() << endl;
                bSuccess = false;
            }

            else
            {
                SDL_SetRenderDrawColor(myRenderer, 255, 255, 255, 255);
                int imgFlags = IMG_INIT_PNG;

                //Now that we're using SDL_image, we need to initialize it.
                if(!(IMG_Init(imgFlags) & imgFlags))
                {
                    cout << "SDL_Image could not initialize: " << IMG_GetError() << endl;
                    bSuccess = false;
                }

                if(TTF_Init() == -1)
                {
                    cout << "SDL_ttf could not initialize: " << TTF_GetError() << endl;
                    bSuccess = false;
                }
            }
        }
    }

    return bSuccess;
}

bool LoadMedia()
{
    bool bSuccess = true;

    DrawableComponent* playerDrawableComponent = new DrawableComponent("TestPlayer.png");
    MovableComponent* playerMovableComponent = new MovableComponent;
    CollisionComponent* playerCollisionComponent = new CollisionComponent(64, 64);
    player.SetDrawableComponent(playerDrawableComponent);
    player.SetMovableComponent(playerMovableComponent);
    player.SetCollisionComponent(playerCollisionComponent);
    player.Initialize(myRenderer);

    DrawableComponent* soldierDrawableComponent = new DrawableComponent("TestPlayer.png");
    MovableComponent* soldierMovableComponent = new MovableComponent;
    soldierMovableComponent->SetVelX(2.0f);
    soldierMovableComponent->SetVelY(2.0f);
    CollisionComponent* soldierCollisionComponent = new CollisionComponent(64, 64);
    soldier.SetDrawableComponent(soldierDrawableComponent);
    soldier.SetMovableComponent(soldierMovableComponent);
    soldier.SetCollisionComponent(soldierCollisionComponent);
    soldier.Initialize(myRenderer);

    int levelWidth = 21;
    int levelHeight = 13;
    unsigned int tileTypes[] = { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 0, 0, 0, 0, 0, 0, 0,
                                 1, 1, 1, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0,
                                 2, 2, 2, 2, 2, 3, 3, 3, 3, 3, 3, 3, 3, 3, 0, 0, 0, 0, 0, 0, 0,
                                 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 3, 3, 0, 0, 0, 0, 0,
                                 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 2, 2, 2, 2, 3, 0, 0, 0, 0, 0,
                                 0, 0, 0, 0, 0, 0, 0, 0, 2, 1, 1, 1, 1, 1, 2, 3, 0, 0, 0, 0, 0,
                                 0, 0, 0, 0, 0, 0, 0, 0, 2, 1, 2, 2, 2, 2, 2, 3, 0, 0, 0, 0, 0,
                                 0, 0, 0, 0, 0, 0, 0, 0, 2, 1, 2, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0,
                                 2, 2, 2, 0, 0, 0, 0, 0, 2, 2, 2, 0, 0, 3, 3, 3, 3, 3, 3, 3, 3,
                                 1, 1, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 2, 2, 2, 2, 2, 2, 2,
                                 1, 1, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 2, 1, 1, 1, 1, 1, 1,
                                 1, 1, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 2, 1, 1, 1, 1, 1, 1,
                                 1, 1, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 2, 1, 1, 1, 1, 1, 1 };

    bool walls[] =             { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
                                 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
                                 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
                                 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
                                 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
                                 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1,
                                 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
                                 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
                                 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
                                 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
                                 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1,
                                 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1,
                                 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 };

    testLevel.SetWidth(levelWidth);
    testLevel.SetHeight(levelHeight);
    testLevel.SetTileTexturePath("tileSet.png");
    testLevel.SetNumTileTypes(4);
    testLevel.SetNumSpawnPoints(2);
    testLevel.Initialize(myRenderer, tileTypes, walls);
    SDL_Point toAdd = { 320, 192 };
    SDL_Point toAdd2 = { 320, 512 };
    testLevel.SetSpawnPoint(toAdd, 0);
    testLevel.SetSpawnPoint(toAdd2, 1);

    SDL_Point playerSpawnPoint;
    testLevel.GetSpawnPoint(playerSpawnPoint, 0);

    playerMovableComponent->SetX(playerSpawnPoint.x);
    playerMovableComponent->SetY(playerSpawnPoint.y);

    soldierMovableComponent->SetX(toAdd.x);
    soldierMovableComponent->SetY(toAdd.y);

    testLevel.AddCharacter(&player);

    DrawableComponent* propDrawableComponent = new DrawableComponent("rum_from_rum_world.png");
    MovableComponent* propMovableComponent = new MovableComponent;
    propMovableComponent->SetX(420);
    propMovableComponent->SetY(192);
    CollisionComponent* propCollisionComponent = new CollisionComponent(16, 16);
    simpleProp.SetID("RUM");
    simpleProp.SetDrawableComponent(propDrawableComponent);
    simpleProp.SetMovableComponent(propMovableComponent);
    simpleProp.SetCollisionComponent(propCollisionComponent);
    simpleProp.Initialize(myRenderer);

    testLevel.AddProp(&simpleProp);

    DrawableComponent* particleDrawComponent = new DrawableComponent("SimpleParticle.png");
    AEOIAFColor c(255, 0, 255, 255);
    particleDrawComponent->GetColor() = c;
    MovableComponent* particleEmitterMovComp = new MovableComponent;
    ParticleMoveComponent* particleMoveComponent = new ParticleMoveComponent(1.0f, 1.0f);
    particleMoveComponent->SetAccelFalloff(0.1f);
    particleEmitterMovComp->SetX(320);
    particleEmitterMovComp->SetY(192);
    testEmitter.SetNumParticles(10);
    testEmitter.SetMovableComponent(particleEmitterMovComp);
    testEmitter.SetParticleMoveComponent(particleMoveComponent);
    testEmitter.SetDrawableComponent(particleDrawComponent);
    testEmitter.Initialize(myRenderer);

    return bSuccess;
}

void Close()
{
    //Destroy window and renderer
    SDL_DestroyRenderer(myRenderer);
    SDL_DestroyWindow(myWindow);
    myWindow = NULL;
    myRenderer = NULL;

    //Quit SDL subsystems
    IMG_Quit();
    TTF_Quit();
    SDL_Quit();
}
