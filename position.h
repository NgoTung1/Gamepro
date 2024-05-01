#ifndef POSITION_H
#define POSITION_H
#include "pacman.h"
#include "Monster.h"
#include <vector>

class Position{
public:
int x;
int y;
void travel(Direction direction);
bool checkcollision(Direction direction);
void travel_for_ghost(Direction direction, int &a, int &b);


};
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
    case LEFT: { if(checkcollision(direction)) x-=tile_size;
    break;
    }
    case RIGHT: {if(checkcollision(direction)) x+=tile_size;
    break;
    }
    case UP: { if(checkcollision(direction)) y-=tile_size;
    break;
    }
    case DOWN: { if(checkcollision(direction)) y+=tile_size;
    break;
    }
    }
}
void Position::travel_for_ghost(Direction direction, int &a, int &b)
{
    switch(direction) {
    case LEFT: {  a-=tile_size;
    break;
    }
    case RIGHT: { a+=tile_size;
    break;
    }
    case UP: {  b-=tile_size;
    break;
    }
    case DOWN: { b+=tile_size;
    break;
    }
    }
}




#endif // POSITION_H
