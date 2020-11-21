#ifndef RENDERIZADOR_H
#define RENDERIZADOR_H

#include <SDL.h>
#include <iostream>
#include "cor_rgba.h"
#include "janela.h"
#include "../Classes Básicas/circunferencia.h"
#include "../Classes Básicas/vetor.h"
#include "../Classes Básicas/ponto.h"
#include "../Classes Básicas/retangulo.h"
#include "../Classes Básicas/triangulo.h"

class Renderizador {
    protected:
        SDL_Renderer* ptr_renderizador = NULL;

    public:
        Renderizador(SDL_Window* ptr_janela){
            ptr_renderizador = SDL_CreateRenderer(ptr_janela, -1, SDL_RENDERER_SOFTWARE);
            if (ptr_renderizador == NULL) {
                std::cout << "Erro ao criar Renderizador: " << SDL_GetError() << std::endl; 
            }
        }

        ~Renderizador(){
            SDL_DestroyRenderer(ptr_renderizador);
        };

        void setCorDesenho(CorRGBA *cor){
            SDL_SetRenderDrawColor(ptr_renderizador, cor->get_r(), cor->get_g(), cor->get_b(), cor->get_a());
        }

        void limpar(CorRGBA *cor){
            setCorDesenho(cor);
            SDL_RenderClear(ptr_renderizador);
        };

        void atualizar(){
            SDL_RenderPresent(ptr_renderizador);
        };

        void desenhar_ponto(CorRGBA *cor, Ponto* ponto){
            setCorDesenho(cor);
            SDL_RenderDrawPoint(ptr_renderizador,
                                static_cast<int>(ponto->x),
                                static_cast<int>(ponto->y));
        }

        void desenhar_linha(CorRGBA *cor, int xi, int yi, int xf, int yf){
            setCorDesenho(cor);
            SDL_RenderDrawLine(ptr_renderizador, xi, yi, xf, yf);
        }

        void desenhar_circunferencia(CorRGBA *cor, Circunferencia *circ){
            setCorDesenho(cor);

            int pix, piy, pfx, pfy;
            Ponto* demarcacao = circ->getDemarcacao();

            for(int i=1; i<circ->getPrecisao(); i++){
                pix = static_cast<int>(demarcacao[i-1].x);
                piy = static_cast<int>(demarcacao[i-1].y);
                pfx = static_cast<int>(demarcacao[i].x);
                pfy = static_cast<int>(demarcacao[i].y);
                
                SDL_RenderDrawLine(ptr_renderizador, pix, piy, pfx, pfy);
            }

            pix = pfx;
            piy = pfy;
            pfx = demarcacao[0].x;
            pfy = demarcacao[0].y;
            
            SDL_RenderDrawLine(ptr_renderizador, pix, piy, pfx, pfy);
        }

        void desenhar_triangulo(CorRGBA *cor, Triangulo *triangulo){
            desenhar_linha( cor,
                            static_cast<int>(triangulo->getPonto1().x),
                            static_cast<int>(triangulo->getPonto1().y),
                            static_cast<int>(triangulo->getPonto2().x),
                            static_cast<int>(triangulo->getPonto2().y));

            desenhar_linha( cor,
                            static_cast<int>(triangulo->getPonto1().x),
                            static_cast<int>(triangulo->getPonto1().y),
                            static_cast<int>(triangulo->getPonto3().x),
                            static_cast<int>(triangulo->getPonto3().y));

            desenhar_linha( cor,
                            static_cast<int>(triangulo->getPonto2().x),
                            static_cast<int>(triangulo->getPonto2().y),
                            static_cast<int>(triangulo->getPonto3().x),
                            static_cast<int>(triangulo->getPonto3().y));
        }

        void desenhar_retangulo(CorRGBA *cor, Retangulo *rect){
            desenhar_linha( cor,
                            static_cast<int>(rect->getInicio().x),
                            static_cast<int>(rect->getInicio().y),
                            static_cast<int>(rect->getInicio().x + rect->getLargura()),
                            static_cast<int>(rect->getInicio().y));

            desenhar_linha( cor,
                            static_cast<int>(rect->getInicio().x),
                            static_cast<int>(rect->getInicio().y + rect->getAltura()),
                            static_cast<int>(rect->getInicio().x + rect->getLargura()),
                            static_cast<int>(rect->getInicio().y + rect->getAltura()));

            desenhar_linha( cor,
                            static_cast<int>(rect->getInicio().x),
                            static_cast<int>(rect->getInicio().y),
                            static_cast<int>(rect->getInicio().x),
                            static_cast<int>(rect->getInicio().y + rect->getAltura()));

            desenhar_linha( cor,
                            static_cast<int>(rect->getInicio().x + rect->getLargura()),
                            static_cast<int>(rect->getInicio().y),
                            static_cast<int>(rect->getInicio().x + rect->getLargura()),
                            static_cast<int>(rect->getInicio().y + rect->getAltura()));

        }
};

#endif