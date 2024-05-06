#ifndef TIMER_H
#define TIMER_H
class Timer{
public:
Timer();
void Start();
void Reset();
void Restart();
void Stop();
void Pause();
void Unpause();
int get_ticks();
bool isStarted();
bool isPaused();
private:
int start;
int pause;

bool is_paused;
bool is_started;


};
Timer::Timer()
{
    start = 0;
    pause = 0;
    is_paused = false;
    is_started = false;
}
void Timer::Start()
{
    is_started = true;
    is_paused = false;
    start = SDL_GetTicks();
}
void Timer::Stop()
{
    is_started = false;
    is_paused = false;
}
void Timer::Pause()
{
    if(is_started == true && is_paused == false) {
        is_paused = true;
        pause = SDL_GetTicks() - start;
    }
}
void Timer::Unpause()
{
    if(is_paused == true) {
        is_paused = false;
        start = SDL_GetTicks() - pause;
        pause = 0;
    }
}
int Timer::get_ticks()
{
    if(is_started == true) {
        if(is_paused == true) {
            return pause;
        }
        else return SDL_GetTicks() - start;
    }
    return 0;
}
bool Timer::isStarted()
{
    return is_started;
}
bool Timer::isPaused()
{
    return is_paused;
}
#endif // GAME_H
