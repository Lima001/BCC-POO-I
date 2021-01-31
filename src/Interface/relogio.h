#ifndef RELOGIO_H
#define RELOGIO_H

#include "controlador_SDL.h"

class Relogio{
    protected:
        
        Controlador_SDL control;
        int fps;
        Uint32 clock_inicio;

    public:

        Relogio(Controlador_SDL &control, int fps=60): 
            control(control), 
            fps(fps)
        {
            clock_inicio = 0;
        };

        void tick(){
            if ((1000 / fps) > SDL_GetTicks() - clock_inicio){
                SDL_Delay(1000 / fps - (SDL_GetTicks() - clock_inicio));
            }

            clock_inicio = SDL_GetTicks();
        }
};

#endif