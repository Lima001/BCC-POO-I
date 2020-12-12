#ifndef JANELA_H
#define JANELA_H

#include <SDL.h>
#include <iostream>
#include "cor_rgba.h"

class Janela {
    public:
        int largura;
        int altura;
        SDL_Window* ptr_janela = NULL;
        SDL_Surface* ptr_surface = NULL;

        Janela(const char titulo[], int largura, int altura){
            ptr_janela = SDL_CreateWindow(titulo,
                                          SDL_WINDOWPOS_CENTERED, 
                                          SDL_WINDOWPOS_CENTERED,
                                          largura,
                                          altura,
                                          0);

            if (ptr_janela == NULL) {
                std::cout << "Erro ao criar a Janela SDL - " << SDL_GetError() << std::endl;
            }
            else{
                Janela::largura = largura;
                Janela::altura = altura;
            }
        }

        ~Janela(){
            if (ptr_janela){
                SDL_DestroyWindow(ptr_janela);
            }
        }

        void iniciarSurface(){
            ptr_surface = SDL_GetWindowSurface(ptr_janela);
        }

        void preencherFundo(CorRGBA &cor){
            SDL_FillRect(ptr_surface, NULL, cor.getCor(ptr_surface));
        }

        void atualizar(){
            SDL_UpdateWindowSurface(ptr_janela);
        }
};

#endif