#ifndef MONSTER_H
#define MONSTER_H
#include <SDL.h>
#include <string>
#include <SDL_image.h>
#include "InitAndMap.h"
#include <SDL_ttf.h>
#include <SDL_mixer.h>
using namespace std;
struct Graphics {
    SDL_Renderer *renderer;
    SDL_Window *window;
    SDL_Texture *wall;
    SDL_Texture *score;
    SDL_Texture* load_text;
    SDL_Texture* Big_score;
    SDL_Texture* menu;
    SDL_Texture* pac_life;
    TTF_Font* font;
    Mix_Music* intro;
    Mix_Chunk* Waka;
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
    TTF_Font* loadFont(const char* path, int size)
    {
        TTF_Font* gFont = TTF_OpenFont( path, size );
        if (gFont == nullptr) {
            SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION,
                           SDL_LOG_PRIORITY_ERROR,
                           "Load font %s", TTF_GetError());
        }
        return gFont;
    }
    Mix_Music *loadMusic(const char* path)
    {
        Mix_Music *gMusic = Mix_LoadMUS(path);
        if (gMusic == nullptr) {
            SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION,
                           SDL_LOG_PRIORITY_ERROR,
                "Could not load music! SDL_mixer Error: %s", Mix_GetError());
        }
        return gMusic;
    }
    // chỉnh lại tham số thứ 2 là 0 với 0 là số lần lặp lại
    void play_music(Mix_Music *gMusic)
    {
        if (gMusic == nullptr) return;

            Mix_PlayMusic( gMusic, 0 );
    }
    Mix_Chunk* loadSound(const char* path) {
        Mix_Chunk* gChunk = Mix_LoadWAV(path);
        if (gChunk == nullptr) {
            SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION,
                           SDL_LOG_PRIORITY_ERROR,
               "Could not load sound! SDL_mixer Error: %s", Mix_GetError());
        }
    }
    void play_chunk(Mix_Chunk* gChunk) {
        if (gChunk != nullptr) {
            Mix_PlayChannel( -1, gChunk, 0 );
        }
    }


    SDL_Texture* renderText(std::string text,
                            TTF_Font* font, SDL_Color textColor)
    {
        SDL_Surface* textSurface =
                TTF_RenderText_Solid( font, text.c_str(), textColor );
        if( textSurface == nullptr ) {
            SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION,
                           SDL_LOG_PRIORITY_ERROR,
                           "Render text surface %s", TTF_GetError());
            return nullptr;
        }

        SDL_Texture* texture =
                SDL_CreateTextureFromSurface( renderer, textSurface );
        if( texture == nullptr ) {
            SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION,
                           SDL_LOG_PRIORITY_ERROR,
                           "Create texture from text %s", SDL_GetError());
        }
        SDL_FreeSurface( textSurface );
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
     font = loadFont("assets/Purisa-BoldOblique.ttf",30);
     wall = loadTexture("map.png");
     score = loadTexture("point.png");
     pac_life = loadTexture("pacmann.PNG");
     Big_score = loadTexture("score.png");
     intro = loadMusic("Intro.wav");

    }
   void render_map(int &life)
   {
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
    renderTexture(score,x+5,y+5);
    break;
    }
    case ' ': break;
    case 'o': {renderTexture(Big_score,x,y); break; }
    case '5': {renderTexture(pac_life,x,y-10);
    if(life== 2 ) mapp[2][23] = ' ';
    else if(life == 1) mapp[2][22] = ' ';
    else if(life == 0) mapp[2][21] = ' ';
    break;}

    }

    }

    }
   }
   int ren_menu() {
    menu = loadTexture("Paly.PNG");
    renderTexture(menu, 0, 100);
    presentScene();

    int x=0, y=0;
    SDL_Event mevent;
    bool quitt = false;

    while (!quitt) {
        while (SDL_PollEvent(&mevent)) {
            switch (mevent.type) {
            case SDL_QUIT:{
                quitt = true;
                return 0;
            }

            case SDL_MOUSEBUTTONDOWN:
                x = mevent.button.x;
                y = mevent.button.y;
                if ((x >= 241 && x <= 314) && (y >= 489 && y <= 517)) {
                    // Play
                    SDL_RenderClear(renderer);
                    quitt = true;
                    return 1;
                } else if ((x >= 250 && x <= 307) && (y >= 537 && y <= 565)) {
                    // Exit
                    quitt = true;
                    return 0;
                }
            default:
                break;
            }
        }
    }
}

    void quit()
    {
        SDL_DestroyTexture(wall);
        SDL_DestroyTexture(score);
        SDL_DestroyTexture(load_text);
        SDL_DestroyTexture(Big_score);
        SDL_DestroyTexture(menu);
        SDL_DestroyTexture(pac_life);
        pac_life = nullptr;
        Big_score = nullptr;
        load_text = nullptr;
        score = nullptr;
        wall = nullptr;
        IMG_Quit();
        TTF_CloseFont(font);
        font = nullptr;
        Mix_FreeChunk(Waka);
        Mix_FreeMusic(intro);
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        TTF_Quit();
        Mix_Quit();
        SDL_Quit();
    }
};





#endif
