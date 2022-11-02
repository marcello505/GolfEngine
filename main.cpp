#include <SDL.h>
#include <SDL_mixer.h>

int main(int argc, char** argv)
{
    Mix_Chunk* music = Mix_LoadWAV("C:\\Users\\marce\\Git\\SPC-Project\\res\\grenade.mp3");

    while(Mix_PlayingMusic()){

    }

    return 0;
}
