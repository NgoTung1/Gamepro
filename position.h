#ifndef POSITION_H
#define POSITION_H
#include "InitAndMap.h"
#include "pacman.h"
#include "Monster.h"
#include <vector>

class Position{
public:
int x;
int y;
void travel(Direction direction);
bool checkcollision(Direction direction);
bool checkcollision_for_ghost(Direction direction);
void travel_for_ghost(Direction &direction, int &a, int &b);


};
//check trc 1 đơn vị
bool Position::checkcollision(Direction direction)
{
    switch(direction) {
    case UP: {
        if(mapp[(y-tile_size-wall_height)/tile_size][(x-wall_width)/tile_size] == '#') {
            return false;
        }
        break;
    }
    case DOWN: {
        if(mapp[(y+tile_size-wall_height)/tile_size][(x-wall_width)/tile_size] == '#') {
            return false;
        }
        break;
    }
    case LEFT: {
        if(mapp[(y-wall_height)/tile_size][(x-tile_size-wall_width)/tile_size] == '#') {
            return false;
        }
        break;
    }
    case RIGHT: {
        if(mapp[(y-wall_height)/tile_size][(x+tile_size-wall_width)/tile_size] == '#') {
            return false;
        }
        break;
    }
    }
    return true;
}
void Position::travel(Direction direction)
{
    switch(direction) {
    case LEFT: { if(checkcollision(direction)) x-=20;
    break;
    }
    case RIGHT: {if(checkcollision(direction)) x+=20;
    break;
    }
    case UP: { if(checkcollision(direction)) y-=20;
    break;
    }
    case DOWN: { if(checkcollision(direction)) y+=20;
    break;
    }
    }
}

void Position::travel_for_ghost(Direction &direction, int &a, int &b)
{
    switch(direction) {
    case LEFT: {  a-=20;
    break;
    }
    case RIGHT: { a+=20;
    break;
    }
    case UP: {  b-=20;
    break;
    }
    case DOWN: { b+=20;
    break;
    }
    }
}



#endif // POSITION_H
