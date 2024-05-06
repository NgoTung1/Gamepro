#ifndef RED_H
#define RED_H
#include <vector>
#include <cmath>
#include "pacman.h"
#include "Monster.h"
#include "position.h"
#include "InitAndMap.h"
#include "Orange.h"
using namespace std;
class Red:public Position{

public:
Red();
~Red();
void render_frames_red(SDL_Renderer* renderer);
void init_frame_red();
void get_red();
void reset_frame_red();
void move_for_red(int& get_direct, pacman pac);
void sort_for_red(vector<float> &distance, vector<int> &arrow);
SDL_Texture* red_texture;





private:
int h_frame_red;
int w_frame_red;
int x_frame_red;
int y_frame_red;
SDL_Rect redframes[6];
int redframe;


};
Red::Red()
{
    h_frame_red = 0;
    w_frame_red = 0;
    x_frame_red = 0;
    y_frame_red = 0;
    x = 310;
    y = 270;
    redframe = 0;
}
Red::~Red(){

}
void Red::get_red()
{

        SDL_Rect dest;
        SDL_QueryTexture(red_texture, NULL, NULL, &dest.w, &dest.h);
        h_frame_red = dest.h;
        w_frame_red = dest.w/6;
}
void Red::reset_frame_red()
{
    redframe =0;
}
void Red::init_frame_red()
{
    redframes[0].x = 0;
    redframes[0].y = 0;
    redframes[0].w = w_frame_red;
    redframes[0].h = h_frame_red;

    redframes[1].x = w_frame_red;
    redframes[1].y = 0;
    redframes[1].w = w_frame_red;
    redframes[1].h = h_frame_red;

    redframes[2].x = w_frame_red*2;
    redframes[2].y = 0;
    redframes[2].w = w_frame_red;
    redframes[2].h = h_frame_red;

    redframes[3].x = w_frame_red*3;
    redframes[3].y = 0;
    redframes[3].w = w_frame_red;
    redframes[3].h = h_frame_red;

    redframes[4].x = w_frame_red*4;
    redframes[4].y = 0;
    redframes[4].w = w_frame_red;
    redframes[4].h = h_frame_red;

    redframes[5].x = w_frame_red*5;
    redframes[5].y = 0;
    redframes[5].w = w_frame_red;
    redframes[5].h = h_frame_red;

}
void Red::render_frames_red(SDL_Renderer* renderer)
{
    while(redframe != 6) {

    SDL_Rect* current_redframe = &redframes[redframe];
    SDL_Rect renderquad = {x,y,w_frame_red,h_frame_red};
    SDL_RenderCopy(renderer,red_texture,current_redframe,&renderquad);
    SDL_RenderPresent(renderer);
    redframe++;
}
reset_frame_red();
}
void Red::sort_for_red(vector<float> &distance, vector<int> &arrow)
{
    for( int i=0;i<distance.size();i++)
    {
        for( int j=i;j<distance.size();j++)
        {
            if(distance[j] < distance[i]) {
                swap(distance[i],distance[j]);
                swap(arrow[i],arrow[j]);
            }
        }
    }
}
void Red::move_for_red(int &get_direct, pacman pac)
{
    vector<float> distance;
    vector<int> arrow;
    Direction direct[4]= {LEFT,UP,RIGHT,DOWN};

    for(int i=0;i<4;i++) {
        int a = x; int b = y;
        if(checkcollision(direct[i])) {
            travel_for_ghost(direct[i], a, b);
            float c = abs(pac.x-a);
            if(c>SCREEN_WIDTH/2) c = SCREEN_WIDTH -c;
            float kc = static_cast<float>(sqrt(pow(c,2)+pow((pac.y-b),2)));
            distance.push_back(kc);
            arrow.push_back(i);
        }
    }
    if(distance.size() == 1){
        travel_for_ghost(direct[arrow[0]],x,y);
        get_direct = arrow[0];
        return;
    }
    sort_for_red( distance, arrow);
    for(int i=0;i<arrow.size();i++) {
        if(arrow[i]!= (get_direct+2)%4) {
            travel_for_ghost(direct[arrow[i]],x,y);
            get_direct = arrow[i];
            return;
        }
    }
}






#endif // ORANGE_H
