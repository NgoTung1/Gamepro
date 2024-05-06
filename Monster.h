#ifndef MONSTER_H
#define MONSTER_H
#include <SDL.h>
#include <SDL_image.h>
#include "InitAndMap.h"
#include <SDL_ttf.h>
#include <SDL_mixer.h>
struct Graphics {
    SDL_Renderer *renderer;
    SDL_Window *window;
    SDL_Texture *wall;
    SDL_Texture *score;
    SDL_Texture *win;
    //SDL_Texture* menuu;
    TTF_Font* font = loadFont("Purisa BoldOblique.TTF",100);
    //SDL_Texture* ops1;
    //SDL_Texture* ops2;
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
    SDL_Texture* renderText(const char* text,
                            TTF_Font* font, SDL_Color textColor)
    {
        SDL_Surface* textSurface =
                TTF_RenderText_Solid( font, text, textColor );
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
    /*
    bool is_selected(int&x,int&y, SDL_Rect &rect ) {
     if( x >= rect.x && x <= rect.w+rect.x && y >= rect.y && y <= rect.y + rect.h) return true;
     return false;
    }

    void menu()
    {
        menuu = loadTexture("menu.JPG");
        renderTexture(menuu,0,0);
        int x = 0;
        int y = 0;

        ops1 = renderText("Start",font,white_color);
        ops2 = renderText("Exit",font,white_color);
        SDL_Rect dest1;
        SDL_Rect dest2;
        SDL_QueryTexture(ops1, NULL, NULL, &dest1.w, &dest1.h);
        SDL_QueryTexture(ops2, NULL, NULL, &dest2.w, &dest2.h);
        SDL_Rect ops[status_menu];
        SDL_SetTextureBlendMode(ops1, SDL_BLENDMODE_BLEND);
        SDL_SetTextureBlendMode(ops2, SDL_BLENDMODE_BLEND);


        ops[0].x = 336;
        ops[0].y = 504;
        ops[0].w = dest1.w;
        ops[0].h = dest1.h;

        ops[1].x = 336;
        ops[1].y = 554;
        ops[1].w = dest2.w;
        ops[1].h = dest2.h;
        renderTexture(ops1,ops[0].x,ops[0].y);
        renderTexture(ops2,ops[1].x,ops[1].y);
        presentScene();
        SDL_Event event;
        while(true) {
            while(SDL_PollEvent(&event)) {
                switch(event.type) {
            case SDL_QUIT:
                return;
            case SDL_MOUSEMOTION: {
                x = event.motion.x;
                y = event.motion.y;
                for(int i = 0;i<status_menu;i++) {
                if( i==0 ) {
                        if(!is_selected(x,y,ops[i])) {
                        SDL_SetTextureColorMod(ops1, red_color.r, red_color.g, red_color.b);
                        }
                        else {
                         SDL_SetTextureColorMod(ops1, white_color.r, white_color.g, white_color.b);
                    }
                }
                else
                {
                    if(!is_selected(x,y,ops[i])) {
                        SDL_SetTextureColorMod(ops2, red_color.r, red_color.g, red_color.b);
                    }
                    else {
                         SDL_SetTextureColorMod(ops2, white_color.r, white_color.g, white_color.b);
                    }
                }
                presentScene();
                }
            }

                }

            }
        }



    }
    */

    void init() {
     initSDL();
     wall = loadTexture("map.png");
     score = loadTexture("point.png");
     win = loadTexture("win.png");

    }
   void render_map()
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
    case '3': break;
    case '4': break;

    }

    }

    }
   }
    void render_winpic() {
    renderTexture(win,20,20);
    }
    void quit()
    {
        SDL_DestroyTexture(wall);
        SDL_DestroyTexture(score);
        SDL_DestroyTexture(win);
        //SDL_DestroyTexture(menuu);
        //SDL_DestroyTexture(ops1);
        //SDL_DestroyTexture(ops2);

        win = nullptr;
        score = nullptr;
        wall = nullptr;
        IMG_Quit();
        TTF_CloseFont(font);
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        TTF_Quit();
        Mix_Quit();
        SDL_Quit();
    }
};





#endif
