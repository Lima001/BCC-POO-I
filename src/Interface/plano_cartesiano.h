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
                                    origem.x,
                                    0,
                                    origem.x,
                                    altura_tela);

            render.desenhar_linha(cor_eixos,
                                    0,
                                    origem.y,
                                    largura_tela,
                                    origem.y);
        }

        void desenharGradeY(Renderizador &render){
            for (int i=origem.y; i>=0; i-=espacamento_y){
                render.desenhar_linha(cor_grade,
                                        0,
                                        i,
                                        largura_tela,
                                        i);
            }

            for (int i=origem.y; i<=altura_tela; i+=espacamento_y){
                render.desenhar_linha(cor_grade,
                                        0,
                                        i,
                                        largura_tela,
                                        i);
            }
        }
        
        void desenharGradeX(Renderizador &render){
            for (int i=origem.x; i>=0; i-=espacamento_x){
                render.desenhar_linha(cor_grade,
                                        i,
                                        0,
                                        i,
                                        altura_tela);
            }

            for (int i=origem.x; i<=largura_tela; i+=espacamento_x){
                render.desenhar_linha(cor_grade,
                                        i,
                                        0,
                                        i,
                                        altura_tela);
            }
        }

        void desenharGrade(Renderizador &render){
            Matriz tmp = render.Transformacao;
            render.Transformacao = std::move(Matriz(3,3));
            
            render.Transformacao[0][0] = 1;
            render.Transformacao[1][1] = 1;
            render.Transformacao[2][2] = 1;

            desenharGradeX(render);
            desenharGradeY(render);
            desenharEixo(render);

            render.Transformacao = std::move(tmp);
        }
};

#endif