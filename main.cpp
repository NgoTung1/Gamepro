#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include "pacman.h"
#include "Monster.h"
#include "InitAndMap.h"
#include <vector>
#include <SDL_ttf.h>
#include "Orange.h"
#include "White.h"

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
    Orange orange;
    orange.cam_texture = graphics.loadTexture("Orange.PNG");
    orange.get_cam();
    orange.init_frame_cam();

    White white;
    white.white_texture = graphics.loadTexture("White.PNG");
    white.get_white();
    white.init_frame_white();

    int get_direct = 10;
    graphics.render();
    graphics.presentScene();
    Direction direction;
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
        pac.render_frames_up(graphics.renderer);
        direction = UP;
        pac.travel(direction);
    orange.render_frames_cam(graphics.renderer);
    white.render_frames_white(graphics.renderer);
    orange.move_for_ghost(pac, get_direct);
//cái mapp sẽ check trước 1 đơn vị nên sẽ - đối với hướng up và left còn cộng thì với down và right
    SDL_RenderClear(graphics.renderer);
     graphics.render();
    pac.render_frames_up(graphics.renderer);
    white.render_frames_white(graphics.renderer);
    orange.render_frames_cam(graphics.renderer);
    graphics.presentScene();
}
        if (currentKeyStates[SDL_SCANCODE_DOWN] ) {
            pac.render_frames_down(graphics.renderer);
        direction = DOWN;
        pac.travel(direction);
    orange.render_frames_cam(graphics.renderer);
    white.render_frames_white(graphics.renderer);
    orange.move_for_ghost(pac, get_direct);
//cái mapp sẽ check trước 1 đơn vị nên sẽ - đối với hướng up và left còn cộng thì với down và right
    SDL_RenderClear(graphics.renderer);
     graphics.render();
    pac.render_frames_down(graphics.renderer);
    white.render_frames_white(graphics.renderer);
    orange.render_frames_cam(graphics.renderer);
    graphics.presentScene();

        }
        if (currentKeyStates[SDL_SCANCODE_LEFT] )
            {
               pac.render_frames_left(graphics.renderer);
        direction = LEFT;
        pac.travel(direction);
    orange.render_frames_cam(graphics.renderer);
    white.render_frames_white(graphics.renderer);
    orange.move_for_ghost(pac,get_direct);
//cái mapp sẽ check trước 1 đơn vị nên sẽ - đối với hướng up và left còn cộng thì với down và right
    SDL_RenderClear(graphics.renderer);
     graphics.render();
    pac.render_frames_left(graphics.renderer);
    white.render_frames_white(graphics.renderer);
    orange.render_frames_cam(graphics.renderer);
    graphics.presentScene();
        }
        if (currentKeyStates[SDL_SCANCODE_RIGHT] ) {pac.render_frames_right(graphics.renderer);
     pac.render_frames_right(graphics.renderer);
        direction = RIGHT;
        pac.travel(direction);
    orange.render_frames_cam(graphics.renderer);
    white.render_frames_white(graphics.renderer);
    orange.move_for_ghost(pac,get_direct);
//cái mapp sẽ check trước 1 đơn vị nên sẽ - đối với hướng up và left còn cộng thì với down và right
    SDL_RenderClear(graphics.renderer);
     graphics.render();
    pac.render_frames_right(graphics.renderer);
    white.render_frames_white(graphics.renderer);
    orange.render_frames_cam(graphics.renderer);
    graphics.presentScene();
        }

        SDL_Delay(100);
    }

    SDL_RenderClear(graphics.renderer);
    graphics.render_winpic();
    graphics.presentScene();
    waitUntilKeyPressed();

    graphics.quit();
    return 0;

}


