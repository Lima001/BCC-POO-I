#ifndef RENDERIZADOR_H
#define RENDERIZADOR_H

#include <SDL.h>
#include <iostream>
#include "cor_rgba.h"
#include "janela.h"
#include "../Base/circunferencia.h"
#include "../Base/vetor.h"
#include "../Base/ponto.h"
#include "../Base/retangulo.h"
#include "../Base/triangulo.h"
#include "../Base/objeto.h"

class Renderizador{
    protected:
        SDL_Renderer* ptr_renderizador = nullptr;
    
    public:

        Matriz Transformacao;
        
        Renderizador(SDL_Window* ptr_janela){
            ptr_renderizador = SDL_CreateRenderer(ptr_janela, -1, SDL_RENDERER_SOFTWARE);

            if (ptr_renderizador == nullptr) {
                std::cout << "Erro ao criar Renderizador: " << SDL_GetError() << std::endl; 
            }
        }

        ~Renderizador(){
            SDL_DestroyRenderer(ptr_renderizador);
        };

        void setCorDesenho(const CorRGBA &cor){
            SDL_SetRenderDrawColor(ptr_renderizador, cor.r, cor.g, cor.b, cor.a);
        }

        void limpar(const CorRGBA &cor){
            setCorDesenho(cor);
            SDL_RenderClear(ptr_renderizador);
        }

        void atualizar(){
            SDL_RenderPresent(ptr_renderizador);
        }

        void desenhar_ponto(const CorRGBA &cor, const Ponto &ponto){
            Matriz tmp = Transformacao * ponto.pontoToMatriz();

            setCorDesenho(cor);
            SDL_RenderDrawPoint(ptr_renderizador,
                                static_cast<int>(tmp[0][0]),
                                static_cast<int>(tmp[1][0]));
        }
        
        void desenhar_linha(const CorRGBA &cor, int xi, int yi, int xf, int yf){
            Matriz tmp = Matriz(3,2);
            tmp[0][0] = xi;
            tmp[0][1] = xf;
            tmp[1][0] = yi;
            tmp[1][1] = yf;
            tmp[2][0] = 1;
            tmp[2][1] = 1;

            tmp = Transformacao * tmp;

            setCorDesenho(cor);
            SDL_RenderDrawLine(ptr_renderizador, tmp[0][0], tmp[1][0], tmp[0][1], tmp[1][1]);
        }
        
        void desenhar_circunferencia(const CorRGBA &cor, const Circunferencia &circ){
            setCorDesenho(cor);

            Ponto* demarcacao = circ.gerarDemarcacao();
            Matriz tmp = Matriz(3,circ.precisao);

            for (int i=0; i<circ.precisao; i++){
                tmp[0][i] = demarcacao[i].x;
                tmp[1][i] = demarcacao[i].y;
                tmp[2][i] = 1;
            }

            tmp = Transformacao * tmp;

            for(int i=1; i<circ.precisao; i++){
                SDL_RenderDrawLine(ptr_renderizador,
                                    tmp[0][i-1],
                                    tmp[1][i-1],
                                    tmp[0][i],
                                    tmp[1][i]);
            }
            
            SDL_RenderDrawLine(ptr_renderizador,
                                tmp[0][circ.precisao-1], 
                                tmp[1][circ.precisao-1], 
                                tmp[0][0], 
                                tmp[1][0]);
        }
        
        void desenhar_triangulo(const CorRGBA &cor, const Triangulo &triangulo){
            desenhar_linha(cor, triangulo.p1.x, triangulo.p1.y, triangulo.p2.x, triangulo.p2.y);
            desenhar_linha(cor, triangulo.p1.x, triangulo.p1.y, triangulo.p3.x, triangulo.p3.y);
            desenhar_linha(cor, triangulo.p2.x, triangulo.p2.y, triangulo.p3.x, triangulo.p3.y);
        
        }
        
        void desenhar_retangulo(const CorRGBA &cor, const Retangulo &rect){
            desenhar_linha(cor, 
                            rect.inicio.x,
                            rect.inicio.y,
                            (rect.inicio.x + rect.largura),
                            rect.inicio.y);

            desenhar_linha(cor,
                            rect.inicio.x,
                            (rect.inicio.y + rect.altura),
                            (rect.inicio.x + rect.largura),
                            (rect.inicio.y + rect.altura));

            desenhar_linha(cor,
                            rect.inicio.x,
                            rect.inicio.y,
                            rect.inicio.x,
                            (rect.inicio.y + rect.altura));

            desenhar_linha(cor,
                            (rect.inicio.x + rect.largura),
                            rect.inicio.y,
                            (rect.inicio.x + rect.largura),
                            (rect.inicio.y + rect.altura));

        }

        void desenhar_vetor(const CorRGBA &cor, const Vetor &vetor, const Ponto &inicio){            
            float xi, xf, yi, yf; 
            
            const float  tam_setas = vetor.getModulo()/5;
            const float  angulo =  vetor.getAngulo();

            xi = static_cast<int>(inicio.x);
            yi = static_cast<int>(inicio.y);
            xf = static_cast<int>(xi + vetor.x);
            yf = static_cast<int>(yi + vetor.y);

            // Linha Principal
            desenhar_linha(cor, xi, yi, xf, yf);
            
            // Linha Secundária 1
            xi =  static_cast<int>(xf + cos(angulo + M_PI*3/4) * tam_setas);
            yi =  static_cast<int>(yf + sin(angulo + M_PI*3/4) * tam_setas);
            desenhar_linha(cor, xi, yi, xf, yf);

            // Linha Secundária 2
            xi = static_cast<int>(xf + cos(angulo + M_PI*5/4) * tam_setas);
            yi = static_cast<int>(yf + sin(angulo + M_PI*5/4) * tam_setas);
            desenhar_linha(cor, xi, yi, xf, yf);
        }
};

#endif