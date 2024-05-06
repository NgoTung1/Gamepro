#ifndef GAME_H
#define GAME_H
#include <SDL.h>
#include <SDL_image.h>
#include "pacman.h"
#include "Orange.h"
#include "White.h"
#include "Monster.h"
#include "position.h"
#include "InitAndMap.h"
#include "Red.h"
class Game {
public:
Game();
~Game();
void play(Direction direction, int &get_direct);
bool check_var();
Graphics graphics;
private:
pacman pac;
White white;
Orange orange;
Red red;


};
Game::Game()
{
    graphics.init();
    pac.pac_texture = graphics.loadTexture("PacMan32.PNG");
    pac.get();
    pac.init_frame();
    orange.cam_texture = graphics.loadTexture("Orange.PNG");
    orange.get_cam();
    orange.init_frame_cam();
    white.white_texture = graphics.loadTexture("White.PNG");
    white.get_white();
    white.init_frame_white();
    red.red_texture = graphics.loadTexture("Red.PNG");
    red.get_red();
    red.init_frame_red();
}
Game::~Game()
{
    SDL_DestroyTexture(pac.pac_texture);
    SDL_DestroyTexture(orange.cam_texture);
    SDL_DestroyTexture(white.white_texture);
    SDL_DestroyTexture(red.red_texture);
}
bool Game::check_var()
{
    if(pac.x == orange.x && pac.y == orange.y) return false;
    else if(pac.x == white.x && pac.y == white.y) return false;
    else if(pac.x == red.x && pac.y == red.y) return false;
    else return true;
}
void Game::play(Direction direction, int &get_direct)
{
    SDL_RenderClear(graphics.renderer);
    graphics.render_map();

    pac.travel(direction);
    orange.move_for_ghost(get_direct, pac);
    white.move_for_white(get_direct, pac);
    red.move_for_red(get_direct, pac);

    switch(direction) {
        case UP:
            pac.render_frames_up(graphics.renderer);
            break;
        case DOWN:
            pac.render_frames_down(graphics.renderer);
            break;
        case LEFT:
            pac.render_frames_left(graphics.renderer);
            break;
        case RIGHT:
            pac.render_frames_right(graphics.renderer);
            break;
    }
    pac.checkscore();
    white.render_frames_white(graphics.renderer);
    orange.render_frames_cam(graphics.renderer);
    red.render_frames_red(graphics.renderer);

    graphics.presentScene();
}

#endif
