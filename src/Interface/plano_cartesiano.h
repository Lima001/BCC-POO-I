#ifndef PLANO_CARTESIANO_H
#define PLANO_CARTESIANO_H

#include <SDL.h>
#include "renderizador.h"


class PlanoCartesiano {
    protected:
        
        int espacamento_x;
        int espacamento_y;
        int largura_tela;
        int altura_tela;
        Ponto origem;
        CorRGBA cor_eixos;
        CorRGBA cor_grade;

    public:

        PlanoCartesiano(int espacamento_x, int espacamento_y, const CorRGBA &cor_eixos, 
                        const CorRGBA &cor_grade, int largura_tela, int altura_tela,
                        const Ponto &origem=Ponto()):
                
                espacamento_x(espacamento_x),
                espacamento_y(espacamento_y),
                largura_tela(largura_tela),
                altura_tela(altura_tela),
                origem(origem),
                cor_eixos(cor_eixos),
                cor_grade(cor_grade){
            }

        void desenharEixo(Renderizador &render){
            render.desenhar_linha(cor_eixos,
                                  -origem.x,
                                  0,
                                  largura_tela-origem.x,
                                  0);

            render.desenhar_linha(cor_eixos,
                                  0,
                                  -origem.y,
                                  0,
                                  altura_tela-origem.y);
        }

        void desenharGradeY(Renderizador &render){
            for (int i=-origem.y; i<=altura_tela-origem.y; i+=espacamento_x){
                
                render.desenhar_linha(cor_grade,
                                      -origem.x,
                                      i,
                                      largura_tela-origem.x,
                                      i);
            }
        }
        
        void desenharGradeX(Renderizador &render){
            for (int i=-origem.x; i<=largura_tela-origem.x; i+=espacamento_y){
                
                render.desenhar_linha(cor_grade,
                                      i,
                                      -origem.y,
                                      i,
                                      altura_tela-origem.y);
            }
        }

        void desenharGrade(Renderizador &render){
            desenharGradeX(render);
            desenharGradeY(render);
            desenharEixo(render);
        }
};

#endif