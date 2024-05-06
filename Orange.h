#ifndef ORANGE_H
#define ORANGE_H
#include <vector>
#include <cmath>
#include "pacman.h"
#include "Monster.h"
#include "position.h"
#include "InitAndMap.h"
using namespace std;

class Orange: public Position {
public:
Orange();
~Orange();
void render_frames_cam(SDL_Renderer* renderer);
void init_frame_cam();
void get_cam();
void reset_frame_cam();
void move_for_ghost(int& get_direct, pacman &pac);
void sort_for_ghost(vector<float> &distance, vector<int> &arrow);
SDL_Texture* cam_texture;





private:
int h_frame_cam;
int w_frame_cam;
int x_frame_cam;
int y_frame_cam;
SDL_Rect orangeframes[6];
int camframe;


};
Orange::Orange()
{
    h_frame_cam = 0;
    w_frame_cam = 0;
    x_frame_cam = 0;
    y_frame_cam = 0;
    x = 270;
    y = 350;
    camframe = 0;
}
Orange::~Orange(){

}
void Orange::get_cam()
{

        SDL_Rect dest;
        SDL_QueryTexture(cam_texture, NULL, NULL, &dest.w, &dest.h);
        h_frame_cam = dest.h;
        w_frame_cam = dest.w/6;
}
void Orange::reset_frame_cam()
{
    camframe =0;
}
void Orange::init_frame_cam()
{
    orangeframes[0].x = 0;
    orangeframes[0].y = 0;
    orangeframes[0].w = w_frame_cam;
    orangeframes[0].h = h_frame_cam;

    orangeframes[1].x = w_frame_cam;
    orangeframes[1].y = 0;
    orangeframes[1].w = w_frame_cam;
    orangeframes[1].h = h_frame_cam;

    orangeframes[2].x = w_frame_cam*2;
    orangeframes[2].y = 0;
    orangeframes[2].w = w_frame_cam;
    orangeframes[2].h = h_frame_cam;

    orangeframes[3].x = w_frame_cam*3;
    orangeframes[3].y = 0;
    orangeframes[3].w = w_frame_cam;
    orangeframes[3].h = h_frame_cam;

    orangeframes[4].x = w_frame_cam*4;
    orangeframes[4].y = 0;
    orangeframes[4].w = w_frame_cam;
    orangeframes[4].h = h_frame_cam;

    orangeframes[5].x = w_frame_cam*5;
    orangeframes[5].y = 0;
    orangeframes[5].w = w_frame_cam;
    orangeframes[5].h = h_frame_cam;

}
void Orange::render_frames_cam(SDL_Renderer* renderer)
{
    while(camframe<6) {

    SDL_Rect* current_camframe = &orangeframes[camframe];
    SDL_Rect renderquad = {x,y,w_frame_cam,h_frame_cam};
    SDL_RenderCopy(renderer,cam_texture,current_camframe,&renderquad);
    SDL_RenderPresent(renderer);
    camframe++;
}
reset_frame_cam();
}
void Orange::sort_for_ghost(vector<float> &distance, vector<int> &arrow)
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
void Orange::move_for_ghost(int &get_direct, pacman &pac)
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
    sort_for_ghost( distance, arrow);
    for(int i=0;i<arrow.size();i++) {
        if(arrow[i]!= (get_direct+2)%4) {
            travel_for_ghost(direct[arrow[i]],x,y);
            get_direct = arrow[i];
            return;
        }
    }
}


#endif

