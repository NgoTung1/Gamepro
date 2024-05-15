#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include "pacman.h"
#include "Monster.h"
#include "game.h"
#include "InitAndMap.h"
#include <vector>
#include <SDL_ttf.h>
#include "Orange.h"
#include "White.h"
#include "Red.h"
#include "Timer.h"

using namespace std;

int main(int argc, char* argv[]) {
    Timer time;
    Game game;
    int get_direct = 10;
    Direction direction;
    int menu_play;
    game.graphics.play_music(game.graphics.intro);
    do {
        menu_play = game.graphics.ren_menu();
        if (menu_play == 1) {
            bool quit = false;
            SDL_Event event;
            game.graphics.render_map(life);
            game.set_score();
            game.play(direction,get_direct);
            game.graphics.presentScene();
            while (!quit) {
                time.Start();
                 if(game.check_var(life) == false) quit = true;
                while (SDL_PollEvent(&event)) {
                    if (event.type == SDL_QUIT) quit = true;
                }
                const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);
                // tải frame, cập nhật tọa độ, xóa render, cập nhật lại background, cập nhật lại frame mới, tính toán collision
                //cái mapp sẽ check trước 1 đơn vị nên sẽ - đối với hướng up và left còn cộng thì với down và right
                if (currentKeyStates[SDL_SCANCODE_UP]) {
                     direction = UP;
                     game.play(direction,get_direct);
                }
                if (currentKeyStates[SDL_SCANCODE_DOWN] ) {
                        direction = DOWN;
                        game.play(direction,get_direct);
                }
                if (currentKeyStates[SDL_SCANCODE_LEFT] ) {
                        direction = LEFT;
                        game.play(direction,get_direct);
                 }
                if (currentKeyStates[SDL_SCANCODE_RIGHT] ) {
                         direction = RIGHT;
                         game.play(direction,get_direct);
                }
                int realtime = time.get_ticks();
                int tpf = 1000/fps;
                if(realtime < tpf) {
                    int delay = tpf - realtime;
                    SDL_Delay(delay);
                }
                if(score == max_score) quit = true;
            }
            game.graphics.quit();
        }
    } while(menu_play != 0);
    return 0;
}



