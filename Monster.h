#ifndef MONSTER_H
#define MONSTER_H
#include <SDL.h>
#include <SDL_image.h>
#include "pacman.h"
using namespace std;
struct Graphics {
    SDL_Renderer *renderer;
    SDL_Window *window;
    SDL_Texture *wall, *pacman, *ghost;

    void logErrorAndExit(const char* msg, const char* error)
    {
        SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR,
                       "%s: %s", msg, error);
        SDL_Quit();
    }

    void initSDL() {
        if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
            logErrorAndExit("SDL_Init", SDL_GetError());

        window = SDL_CreateWindow(WINDOW_TITLE, SDL_WINDOWPOS_CENTERED,
                   SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT,
                   SDL_WINDOW_SHOWN);
        if (window == nullptr)
                   logErrorAndExit("CreateWindow", SDL_GetError());

        if (!IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG))
            logErrorAndExit( "SDL_image error:", IMG_GetError());

        renderer = SDL_CreateRenderer(window, -1,
                     SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

        //renderer =
                  SDL_CreateSoftwareRenderer(SDL_GetWindowSurface(window));

        if (renderer == nullptr)
             logErrorAndExit("CreateRenderer", SDL_GetError());

        SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
        SDL_RenderSetLogicalSize(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);
    }

    void prepareScene(SDL_Texture * background)
    {
        SDL_RenderClear(renderer);
        SDL_RenderCopy( renderer, background, NULL, NULL);
    }

    void presentScene()
    {
        SDL_RenderPresent(renderer);
    }

    SDL_Texture *loadTexture(const char *filename)
    {
        SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO,
                       "Loading %s", filename);
        SDL_Texture *texture = IMG_LoadTexture(renderer, filename);
        if (texture == NULL)
            SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION,
                  SDL_LOG_PRIORITY_ERROR, "Load texture %s", IMG_GetError());

        return texture;
    }

    void renderTexture(SDL_Texture *texture, int x, int y)
    {
        SDL_Rect dest;

        dest.x = x;
        dest.y = y;
        SDL_QueryTexture(texture, NULL, NULL, &dest.w, &dest.h);

        SDL_RenderCopy(renderer, texture, NULL, &dest);
    }

    void init() {
     initSDL();
     wall = loadTexture("map.png");
     ghost = loadTexture("ghost1.png");
     pacman = loadTexture("pacmann.png");

    }
    void render() {
    for (int i= 0;i< max_row;i++) {
    for (int j=0;j<max_col;j++) {
    int x = wall_height + j*image_sizeh;
    int y = wall_width +  i*image_sizew;
    switch (mapp[i][j]) {
    case '0':
    renderTexture(wall,x,y);
    break;
    case '1': break;
    case '5': renderTexture(pacman,x,y); break;
    case '2': renderTexture(ghost,x,y); break;
    case '3': break;
    case '4': break;

    }

    }

    }
    presentScene();
    }
    void quit()
    {
        SDL_DestroyTexture(wall);
        wall = nullptr;
        SDL_DestroyTexture(ghost);
        ghost = nullptr;
        SDL_DestroyTexture(pacman);
        pacman = nullptr;
        IMG_Quit();

        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
    }
};





#endif
