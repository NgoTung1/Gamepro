#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include "pacman.h"
#include "Monster.h"
#include "InitAndMap.h"
#include <vector>

using namespace std;


void waitUntilKeyPressed()
{
    SDL_Event e;
    while (true) {
        if ( SDL_PollEvent(&e) != 0 &&
             (e.type == SDL_KEYDOWN || e.type == SDL_QUIT) )
            return;
        SDL_Delay(100);
    }
}

int main(int argc, char* argv[])
{

    Graphics graphics;
    graphics.init();
    pacman pac;
    pac.pac_texture = graphics.loadTexture("PacMan32.PNG");
    pac.get();
    pac.init_frame();

    graphics.render();
    graphics.presentScene();
    bool quit = false;
    SDL_Event event;
    while (!quit) {
        //Handle events on queue
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) quit = true;
        }

        const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);
// Bên trong vòng lặp chính
// tải frame, cập nhật tọa độ, xóa render, cập nhật lại background, cập nhật lại frame mới, tính toán collision
if (currentKeyStates[SDL_SCANCODE_UP]) {
    pac.render_frames(graphics.renderer);
//cái mapp sẽ check trước 1 đơn vị nên sẽ - đối với hướng up và left còn cộng thì với down và right
    if(mapp[(pac.position.y-tile_size-wall_height)/tile_size][(pac.position.x-wall_width)/tile_size]=='#'){
    pac.position.y+=0;
    }
    else pac.position.y -=20;
    SDL_RenderClear(graphics.renderer);
    graphics.render();
    pac.render_frames(graphics.renderer);
    graphics.presentScene();
}
        if (currentKeyStates[SDL_SCANCODE_DOWN] ) {
            pac.render_frames(graphics.renderer);
    if(mapp[(pac.position.y+tile_size-wall_height)/tile_size][(pac.position.x-wall_width)/tile_size]=='#'){
    pac.position.y+=0;
    }
    else pac.position.y +=20;

    SDL_RenderClear(graphics.renderer);
    graphics.render();
    pac.render_frames(graphics.renderer);
    graphics.presentScene();

        }
        if (currentKeyStates[SDL_SCANCODE_LEFT] ) {pac.render_frames(graphics.renderer);
    if(mapp[(pac.position.y-wall_height)/tile_size][(pac.position.x-tile_size-wall_width)/tile_size]=='#'){
    pac.position.x+=0;
    }
    else pac.position.x -=20;
    SDL_RenderClear(graphics.renderer);
    graphics.render();
    pac.render_frames(graphics.renderer);
    graphics.presentScene();
        }
        if (currentKeyStates[SDL_SCANCODE_RIGHT] ) {pac.render_frames(graphics.renderer);
    if(mapp[(pac.position.y-wall_height)/tile_size][(pac.position.x+tile_size-wall_width)/tile_size]=='#'){
    pac.position.x+=0;
    }
    else pac.position.x +=20;
    SDL_RenderClear(graphics.renderer);
    graphics.render();
    pac.render_frames(graphics.renderer);
    graphics.presentScene();
        }

        cerr << ".\n";

        SDL_Delay(100);
    }



    waitUntilKeyPressed();

    graphics.quit();
    return 0;

}


