#ifndef GERENCIADOR_EVENTO_H
#define GERENCIADOR_EVENTO_H

#include <SDL.h>
#include "evento.h"

class GerenciadorEvento{
    public:
        Evento evento = Evento(NONE,T_NONE);

    protected:
        SDL_Event registro;
        
        void getEvento(){
            if (registro.type == SDL_QUIT){
                evento.tipo_evento = QUIT;
                evento.trigger = T_CLOSE;
            }
            
            else if (registro.type == SDL_KEYDOWN){
                switch(registro.key.keysym.sym){   
                    case SDLK_LEFT:
                        evento.tipo_evento = KEYDOWN;
                        evento.trigger = T_KLEFT;
                        break;
                    
                    case SDLK_DOWN:
                        evento.tipo_evento = KEYDOWN;
                        evento.trigger = T_KDOWN;
                        break;
                    
                    case SDLK_RIGHT:
                        evento.tipo_evento = KEYDOWN;
                        evento.trigger = T_KRIGHT;
                        break;
                    
                    case SDLK_UP:
                        evento.tipo_evento = KEYDOWN;
                        evento.trigger = T_KUP;
                        break;
                    
                    case SDLK_q:
                        evento.tipo_evento = KEYDOWN;
                        evento.trigger = T_KQ;
                        break;

                    case SDLK_p:
                        evento.tipo_evento = KEYDOWN;
                        evento.trigger = T_KP;
                        break;

                    case SDLK_a:
                        evento.tipo_evento = KEYDOWN;
                        evento.trigger = T_KA;
                        break;
                    
                    case SDLK_d:
                        evento.tipo_evento = KEYDOWN;
                        evento.trigger = T_KD;
                        break;

                    case SDLK_w:
                        evento.tipo_evento = KEYDOWN;
                        evento.trigger = T_KW;
                        break;

                    case SDLK_s:
                        evento.tipo_evento = KEYDOWN;
                        evento.trigger = T_KS;
                        break;
                    
                    default:
                        evento.tipo_evento = KEYDOWN;
                        evento.trigger = T_UNDEFINED;
                        break;
                }
            }
            else{
                evento.tipo_evento = UNDEFINED;
                evento.trigger = T_UNDEFINED;
            }
        }

    public:

        GerenciadorEvento(){}

        ~GerenciadorEvento(){}

       void registrarEvento(){
            if (SDL_PollEvent(&registro)){
                getEvento();
            }
            else{
                evento.tipo_evento = NONE;
                evento.trigger = T_NONE;
            }
        }
};

#endif