#ifndef GAME_H
#define GAME_H
#include <SDL.h>
#include <SDL_image.h>
#include <string>
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
bool check_var(int &life);
void set_score();
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
    pac.pac_texture = graphics.loadTexture("PacMan.PNG");
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
    graphics.Waka = graphics.loadSound("assets/Waka.wav");
}
Game::~Game()
{
    SDL_DestroyTexture(pac.pac_texture);
    SDL_DestroyTexture(orange.cam_texture);
    SDL_DestroyTexture(white.white_texture);
    SDL_DestroyTexture(red.red_texture);
    graphics.quit();
}
bool Game::check_var(int &life)
{   if(life > 0)
     {
    if(pac.x == orange.x && pac.y == orange.y) {life--;
    pac.x= 270; pac.y = 530;
    return true;
    }
    else if(pac.x == white.x && pac.y == white.y) {
            life--;
    pac.x = 270; pac.y = 530;
    return true;

    }
    else if(pac.x == red.x && pac.y == red.y) {
        life --;
        pac.x = 270; pac.y = 530;
        return true;
    }
    return true;
    }
    else return false;
}
void Game::set_score()
{
    string score_text = "Score: " + to_string(score);
    graphics.load_text = graphics.renderText(score_text,graphics.font,white_color);
    graphics.renderTexture(graphics.load_text, SCREEN_WIDTH * 0.04, SCREEN_HEIGHT * 0.04);
    graphics.presentScene();
}
void Game::play(Direction direction, int &get_direct)
{
    SDL_RenderClear(graphics.renderer);
    graphics.render_map(life);
    set_score();
    pac.travel(direction);
    pac.checkscore(score);
    orange.move_for_ghost(get_direct, pac);
    white.move_for_white(get_direct, pac);
    red.move_for_red(get_direct, pac);

    switch(direction) {
        case UP:
            pac.render_frames_up(graphics.renderer);
            graphics.play_chunk(graphics.Waka);
            break;
        case DOWN:
            pac.render_frames_down(graphics.renderer);
            graphics.play_chunk(graphics.Waka);
            break;
        case LEFT:
            pac.render_frames_left(graphics.renderer);
            graphics.play_chunk(graphics.Waka);
            break;
        case RIGHT:
            pac.render_frames_right(graphics.renderer);
            graphics.play_chunk(graphics.Waka);
            break;
    }
    white.render_frames_white(graphics.renderer);
    orange.render_frames_cam(graphics.renderer);
    red.render_frames_red(graphics.renderer);
    graphics.presentScene();
}

#endif
