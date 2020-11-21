#include <iostream>
#include <SDL.h>

#ifndef Controlador_SDL_H
#define Controlador_SDL_H

class Controlador_SDL {
    protected:

        bool inicializado;

    public:

        Controlador_SDL(){};

        void inicializar(){
            if (SDL_Init(SDL_INIT_EVERYTHING) < 0){
                std::cout << "Erro ao Iniciar SDL - " << SDL_GetError() << std::endl;
                inicializado = false;
            }
            else{
                std::cout << "SDL Inicializado...\n";
                inicializado = true;
            }   
        }

        void pausar(int milissegundos){
            std::cout << "SDL Pausado...\n";
            SDL_Delay(milissegundos);
        }

        void finalizar(){
            std::cout << "SDL Finalizado...\n";
            SDL_Quit();
        }

        bool getInicializado(){
            return inicializado;
        }
};

#endif