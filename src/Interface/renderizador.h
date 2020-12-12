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

class Renderizador {
    protected:
        SDL_Renderer* ptr_renderizador = NULL;
        Ponto origem;
        int sentido_y;

    public:
        Renderizador(SDL_Window* ptr_janela, Ponto origem=Ponto(), int sentido=1):
            origem(origem),
            sentido_y(sentido)
        {
            ptr_renderizador = SDL_CreateRenderer(ptr_janela, -1, SDL_RENDERER_SOFTWARE);

            if (ptr_renderizador == NULL) {
                std::cout << "Erro ao criar Renderizador: " << SDL_GetError() << std::endl; 
            }
        }

        ~Renderizador(){
            SDL_DestroyRenderer(ptr_renderizador);
        };

        void setCorDesenho(CorRGBA &cor){
            SDL_SetRenderDrawColor(ptr_renderizador, cor.r, cor.g, cor.b, cor.a);
        }

        void limpar(CorRGBA &cor){
            setCorDesenho(cor);
            SDL_RenderClear(ptr_renderizador);
        }

        void atualizar(){
            SDL_RenderPresent(ptr_renderizador);
        }

        void desenhar_ponto(CorRGBA &cor, Ponto &ponto){
            setCorDesenho(cor);
            SDL_RenderDrawPoint(ptr_renderizador,
                                static_cast<int>(ponto.x),
                                static_cast<int>(ponto.y));
        }

        void desenhar_linha(CorRGBA &cor, int xi, int yi, int xf, int yf){
            xi += origem.x;
            yi = origem.y + (sentido_y * yi);
            xf += origem.x;
            yf = origem.y + (sentido_y * yf);

            setCorDesenho(cor);
            SDL_RenderDrawLine(ptr_renderizador, xi, yi, xf, yf);
        }

        void desenhar_circunferencia(CorRGBA &cor, Circunferencia *circ){
            setCorDesenho(cor);

            int pix, piy, pfx, pfy;

            for(int i=1; i<circ->precisao; i++){
                pix = static_cast<int>(origem.x + circ->demarcacao[i-1].x);
                piy = static_cast<int>(origem.y + (sentido_y * circ->demarcacao[i-1].y));
                pfx = static_cast<int>(origem.x + circ->demarcacao[i].x);
                pfy = static_cast<int>(origem.y + (sentido_y * circ->demarcacao[i].y));
                
                SDL_RenderDrawLine(ptr_renderizador, pix, piy, pfx, pfy);
            }

            pix = pfx;
            piy = pfy;
            pfx = origem.x + circ->demarcacao[0].x;
            pfy = origem.y + (sentido_y * circ->demarcacao[0].y);
            
            SDL_RenderDrawLine(ptr_renderizador, pix, piy, pfx, pfy);
        }

        void desenhar_circunferencia(CorRGBA &cor, Circunferencia &circ){
            setCorDesenho(cor);

            int pix, piy, pfx, pfy;

            for(int i=1; i<circ.precisao; i++){
                pix = static_cast<int>(origem.x + circ.demarcacao[i-1].x);
                piy = static_cast<int>(origem.y + (sentido_y * circ.demarcacao[i-1].y));
                pfx = static_cast<int>(origem.x + circ.demarcacao[i].x);
                pfy = static_cast<int>(origem.y + (sentido_y * circ.demarcacao[i].y));
                
                SDL_RenderDrawLine(ptr_renderizador, pix, piy, pfx, pfy);
            }

            pix = pfx;
            piy = pfy;
            pfx = origem.x + circ.demarcacao[0].x;
            pfy = origem.y + (sentido_y * circ.demarcacao[0].y);
            
            SDL_RenderDrawLine(ptr_renderizador, pix, piy, pfx, pfy);
        }

        void desenhar_triangulo(CorRGBA &cor, Triangulo &triangulo){
            desenhar_linha(cor,
                           static_cast<int>(origem.x + triangulo.p1.x),
                           static_cast<int>(origem.y + (sentido_y * triangulo.p1.y)),
                           static_cast<int>(origem.x + triangulo.p2.x),
                           static_cast<int>(origem.y + (sentido_y * triangulo.p2.y)));

            desenhar_linha(cor,
                           static_cast<int>(origem.x + triangulo.p1.x),
                           static_cast<int>(origem.y + (sentido_y * triangulo.p1.y)),
                           static_cast<int>(origem.x + triangulo.p3.x),
                           static_cast<int>(origem.y + (sentido_y * triangulo.p3.y)));

            desenhar_linha(cor,
                           static_cast<int>(origem.x + triangulo.p2.x),
                           static_cast<int>(origem.y + (sentido_y * triangulo.p2.y)),
                           static_cast<int>(origem.x + triangulo.p3.x),
                           static_cast<int>(origem.y + (sentido_y * triangulo.p3.y)));
        }

        void desenhar_retangulo(CorRGBA &cor, Retangulo &rect){
            desenhar_linha(cor,
                           static_cast<int>(origem.x + rect.inicio.x),
                           static_cast<int>(origem.y + (sentido_y * rect.inicio.y)),
                           static_cast<int>(origem.x + rect.inicio.x + rect.largura),
                           static_cast<int>(origem.y + (sentido_y * rect.inicio.y)));

            desenhar_linha(cor,
                           static_cast<int>(origem.x + rect.inicio.x),
                           static_cast<int>(origem.y + (sentido_y * (rect.inicio.y + rect.altura))),
                           static_cast<int>(origem.x + rect.inicio.x + rect.largura),
                           static_cast<int>(origem.y + (sentido_y * (rect.inicio.y + rect.altura))));

            desenhar_linha(cor,
                           static_cast<int>(origem.x + rect.inicio.x),
                           static_cast<int>(origem.y + (sentido_y * rect.inicio.y)),
                           static_cast<int>(origem.x + rect.inicio.x),
                           static_cast<int>(origem.y + (sentido_y * (rect.inicio.y + rect.altura))));

            desenhar_linha(cor,
                           static_cast<int>(origem.x + rect.inicio.x + rect.largura),
                           static_cast<int>(origem.y + (sentido_y * rect.inicio.y)),
                           static_cast<int>(origem.x + rect.inicio.x + rect.largura),
                           static_cast<int>(origem.y + (sentido_y * (rect.inicio.y + rect.altura))));

        }

        void desenhar_vetor(CorRGBA &cor, Vetor &vetor, Ponto inicio){            
            float xi, xf, yi, yf, tam_setas, angulo;
            
            tam_setas = vetor.getModulo()/5;
            angulo =  vetor.getAngulo();

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