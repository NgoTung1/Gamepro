#ifndef WHITE_H
#define WHITE_H
#include "Monster.h"
#include "position.h"
#include "InitAndMap.h"
class White {
public:
White();
~White();
Position position_white;
void render_frames_white(SDL_Renderer* renderer);
void init_frame_white();
void get_white();
void reset_frame_white();
SDL_Texture* white_texture;




private:
int h_frame_white;
int w_frame_white;
int x_frame_white;
int y_frame_white;
int x;
int y;
SDL_Rect whiteframes[6];
int whiteframe;


};
White::White()
{
    h_frame_white = 0;
    w_frame_white = 0;
    x_frame_white = 0;
    y_frame_white = 0;
    position_white.x = 310;
    position_white.y = 350;
    whiteframe = 0;
}
White::~White(){

}
void White::get_white()
{

        SDL_Rect dest;
        SDL_QueryTexture(white_texture, NULL, NULL, &dest.w, &dest.h);
        h_frame_white = dest.h;
        w_frame_white = dest.w/6;
}
void White::reset_frame_white()
{
    whiteframe =0;
}
void White::init_frame_white()
{
    whiteframes[0].x = 0;
    whiteframes[0].y = 0;
    whiteframes[0].w = w_frame_white;
    whiteframes[0].h = h_frame_white;

    whiteframes[1].x = w_frame_white;
    whiteframes[1].y = 0;
    whiteframes[1].w = w_frame_white;
    whiteframes[1].h = h_frame_white;

    whiteframes[2].x = w_frame_white*2;
    whiteframes[2].y = 0;
    whiteframes[2].w = w_frame_white;
    whiteframes[2].h = h_frame_white;

    whiteframes[3].x = w_frame_white*3;
    whiteframes[3].y = 0;
    whiteframes[3].w = w_frame_white;
    whiteframes[3].h = h_frame_white;

    whiteframes[4].x = w_frame_white*4;
    whiteframes[4].y = 0;
    whiteframes[4].w = w_frame_white;
    whiteframes[4].h = h_frame_white;

    whiteframes[5].x = w_frame_white*5;
    whiteframes[5].y = 0;
    whiteframes[5].w = w_frame_white;
    whiteframes[5].h = h_frame_white;

}
void White::render_frames_white(SDL_Renderer* renderer)
{
    while(whiteframe != 6) {

    SDL_Rect* current_whiteframe = &whiteframes[whiteframe];
    SDL_Rect renderquad = {position_white.x,position_white.y,w_frame_white,h_frame_white};
    SDL_RenderCopy(renderer,white_texture,current_whiteframe,&renderquad);
    SDL_RenderPresent(renderer);
    whiteframe++;
}
reset_frame_white();
}


#endif

