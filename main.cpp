#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include "pacman.h"
#include "Monster.h"
#include <vector>

using namespace std;


void waitUntilKeyPressed()
{
    SDL_Event e;
    while (true) {
        if ( SDL_PollEvent(&e) != 0 &&
             (e.type == SDL_KEYDOWN || e.type == SDL_QUIT) )
            return;
        SDL_Delay(100);
    }
}

int main(int argc, char* argv[])
{

    Graphics graphics;
    graphics.init();

    graphics.render();
    graphics.presentScene();

    waitUntilKeyPressed();

    graphics.quit();
    return 0;

}


