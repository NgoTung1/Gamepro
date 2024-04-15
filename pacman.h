#ifndef PACMAN_H
#define PACMAN_H
#include "Monster.h"
#include "position.h"
#include "InitAndMap.h"
class pacman {
public:
    pacman();
    ~pacman();
    void tilewall();
    void render_frames(SDL_Renderer* renderer);
    void init_frame();
    void get();
    void reset_frame();
    void checkcollision();
    SDL_Texture* pac_texture;
    Position position;

private:
int h_frame;
int w_frame;
int x_frame;
int y_frame;
int x;
int y;
SDL_Rect pacframes[3];
int pacframe = 0;





};
pacman::pacman() {
pacframe = 0;
h_frame = 0;
w_frame = 0;
x_frame = 0;
y_frame = 0;
position.x = 270;
position.y =530;



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
void pacman::render_frames(SDL_Renderer* renderer) {

while(pacframe != 3) {

    SDL_Rect* current_pacframe = &pacframes[pacframe];
    SDL_Rect renderquad = {position.x,position.y,w_frame,h_frame};
    SDL_RenderCopy(renderer,pac_texture,current_pacframe,&renderquad);
    SDL_RenderPresent(renderer);
    pacframe++;
}
reset_frame();

}


#endif
