#ifndef WHITE_H
#define WHITE_H
#include "Monster.h"
#include "position.h"
#include "InitAndMap.h"
#include "Orange.h"
#include "pacman.h"
class White:public Position {
public:
White();
~White();
Position position_white;
void render_frames_white(SDL_Renderer* renderer);
void init_frame_white();
void get_white();
void reset_frame_white();
void move_for_white(int& get_direct, pacman &pac);
void sort_for_white(vector<float> &distance, vector<int> &arrow);
SDL_Texture* white_texture;




private:
int h_frame_white;
int w_frame_white;
int x_frame_white;
int y_frame_white;
SDL_Rect whiteframes[6];
int whiteframe;


};
White::White()
{
    h_frame_white = 0;
    w_frame_white = 0;
    x_frame_white = 0;
    y_frame_white = 0;
    x = 310;
    y = 350;
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
    SDL_Rect renderquad = {x,y,w_frame_white,h_frame_white};
    SDL_RenderCopy(renderer,white_texture,current_whiteframe,&renderquad);
    SDL_RenderPresent(renderer);
    whiteframe++;
}
reset_frame_white();
}
void White::sort_for_white(vector<float> &distance, vector<int> &arrow)
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
void White::move_for_white(int &get_direct, pacman &pac)
{
    vector<float> distance;
    vector<int> arrow;
    Direction direct[4]= {LEFT,UP,RIGHT,DOWN};

    for(int i=0;i<4;i++) {
        int a = x; int b = y;

            travel_for_ghost(direct[i], a, b);
            float c = abs(pac.x-a);
            if(c>SCREEN_WIDTH/2) c = SCREEN_WIDTH -c;
            float kc = static_cast<float>(sqrt(pow(c,2)+pow((pac.y-b),2)));
            distance.push_back(kc);
            arrow.push_back(i);

    }
    if(distance.size() == 1){
        travel_for_ghost(direct[arrow[0]],x,y);
        get_direct = arrow[0];
        return;
    }
    sort_for_white( distance, arrow);
    for(int i=0;i<arrow.size();i++) {
        if(arrow[i]!= (get_direct+2)%4) {
            travel_for_ghost(direct[arrow[i]],x,y);
            get_direct = arrow[i];
            return;
        }
    }
}



#endif

