#ifndef MONSTER_H
#define MONSTER_H
#include <SDL.h>
#include <SDL_image.h>
#include "pacman.h"
#include "InitAndMap.h"
#include <SDL_ttf.h>
#include <SDL_mixer.h>
struct Graphics {
    SDL_Renderer *renderer;
    SDL_Window *window;
    SDL_Texture *wall;
    SDL_Texture *score;
    SDL_Texture *win;

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

                  SDL_CreateSoftwareRenderer(SDL_GetWindowSurface(window));

        if (renderer == nullptr)
             logErrorAndExit("CreateRenderer", SDL_GetError());

        SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
        SDL_RenderSetLogicalSize(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);
        if (TTF_Init() == -1) {
            logErrorAndExit("SDL_ttf could not initialize! SDL_ttf Error: ",
                             TTF_GetError());
        }
        if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 ) {
   logErrorAndExit( "SDL_mixer could not initialize! SDL_mixer Error: %s\n",
                    Mix_GetError() );
}


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
     score = loadTexture("score.png");
     win = loadTexture("win.png");

    }

    void render() {
    for (int i= 0;i< max_row;i++) {
    for (int j=0;j<max_col;j++) {
    int x = wall_height + j*tile_size;
    int y = wall_width +  i*tile_size;
    switch (mapp[i][j]) {
    case '#':{
    renderTexture(wall,x,y);
    break;
    }
    case '0': break;
    case '.': {
    renderTexture(score,x,y);
    break;
    }
    case ' ': break;
    case '3': break;
    case '4': break;

    }

    }

    }
    presentScene();
    }
    void render_winpic() {
    renderTexture(win,20,20);
    }
    void quit()
    {
        SDL_DestroyTexture(wall);
        SDL_DestroyTexture(score);
        SDL_DestroyTexture(win);
        win = nullptr;
        score = nullptr;
        wall = nullptr;
        IMG_Quit();

        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        TTF_Quit();
        Mix_Quit();
        SDL_Quit();
    }
};





#endif
