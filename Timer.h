#ifndef TIMER_H
#define TIMER_H
class Timer{
public:
Timer();
void Start();
int get_ticks();
private:
int start;


};
Timer::Timer()
{
    start = 0;
}
void Timer::Start()
{
    start = SDL_GetTicks();
}
int Timer::get_ticks()
{
     return SDL_GetTicks() - start;
}
#endif // GAME_H
