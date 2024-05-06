#ifndef PACMAN_H
#define PACMAN_H
#include "Monster.h"
#include "position.h"
#include "InitAndMap.h"
class pacman:public Position {
public:
    pacman();
    ~pacman();
    void tilewall();
    void render_frames_right(SDL_Renderer* renderer);
    void render_frames_left(SDL_Renderer* renderer);
    void render_frames_up(SDL_Renderer* renderer);
    void render_frames_down(SDL_Renderer* renderer);
    void init_frame();
    void get();
    void reset_frame();
    void checkcollision();
    void checkscore();
    SDL_Texture* pac_texture;


private:
int h_frame;
int w_frame;
int x_frame;
int y_frame;
SDL_Rect pacframes[3];
int pacframe = 0;





};
pacman::pacman() {
pacframe = 0;
h_frame = 0;
w_frame = 0;
x_frame = 0;
y_frame = 0;
x = 270;
y =530;


}
// x và y là tọa độ của pacman trong map, còn x_frame và y_frame là tọa độ của ảnh
pacman::~pacman()
{
}

// Lấy chiều cao và chiều rộng của ảnh
void pacman::get()
    {
        SDL_Rect dest;
        SDL_QueryTexture(pac_texture, NULL, NULL, &dest.w, &dest.h);
        h_frame = dest.h;
        w_frame = dest.w/3;

    }
//gán tọa độ cho từng frame ảnh
void pacman::init_frame() {
    pacframes[0].x = 0;
    pacframes[0].y = 0;
    pacframes[0].w = w_frame;
    pacframes[0].h = h_frame;

    pacframes[1].x = w_frame;
    pacframes[1].y = 0;
    pacframes[1].w = w_frame;
    pacframes[1].h = h_frame;

    pacframes[2].x = w_frame*2;
    pacframes[2].y = 0;
    pacframes[2].w = w_frame;
    pacframes[2].h = h_frame;

}
//trả frame về 0
void pacman::reset_frame() {
    pacframe = 0;
}
//render animation
void pacman::render_frames_right(SDL_Renderer* renderer) {

while(pacframe != 3) {

    SDL_Rect* current_pacframe = &pacframes[pacframe];
    SDL_Rect renderquad = {x,y,w_frame,h_frame};
    SDL_RenderCopy(renderer,pac_texture,current_pacframe,&renderquad);
    SDL_RenderPresent(renderer);
    pacframe++;
}
reset_frame();

}
void pacman::render_frames_left(SDL_Renderer* renderer) {

while(pacframe != 3) {

    SDL_Rect* current_pacframe = &pacframes[pacframe];
    SDL_Rect renderquad = {x,y,w_frame,h_frame};
    SDL_RenderCopyEx(renderer,pac_texture,current_pacframe,&renderquad,180,NULL,SDL_FLIP_NONE);
    SDL_RenderPresent(renderer);
    pacframe++;
}
reset_frame();

}void pacman::render_frames_down(SDL_Renderer* renderer) {

while(pacframe != 3) {

    SDL_Rect* current_pacframe = &pacframes[pacframe];
    SDL_Rect renderquad = {x,y,w_frame,h_frame};
    SDL_RenderCopyEx(renderer,pac_texture,current_pacframe,&renderquad,90,NULL,SDL_FLIP_NONE);
    SDL_RenderPresent(renderer);
    pacframe++;
}
reset_frame();

}void pacman::render_frames_up(SDL_Renderer* renderer) {

while(pacframe != 3) {

    SDL_Rect* current_pacframe = &pacframes[pacframe];
    SDL_Rect renderquad = {x,y,w_frame,h_frame};
    SDL_RenderCopyEx(renderer,pac_texture,current_pacframe,&renderquad,-90,NULL,SDL_FLIP_VERTICAL);
    SDL_RenderPresent(renderer);
    pacframe++;
}
reset_frame();

}
void pacman::checkscore() {
if(mapp[(y)/tile_size][(x)/tile_size]=='.') {
        mapp[(y)/tile_size][(x)/tile_size]=' ';
        score++;
}

}


#endif
