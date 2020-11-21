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
        CorRGBA cor_eixos;
        CorRGBA cor_grade;

    private:

        void desenharEixo(Renderizador *render){
            render->desenhar_linha( &cor_eixos,
                                    0,
                                    altura_tela/2,
                                    largura_tela,
                                    altura_tela/2);

            render->desenhar_linha( &cor_eixos,
                                    largura_tela/2,
                                    0,
                                    largura_tela/2,
                                    altura_tela);
        }

        void desenharGradeX(Renderizador *render){
            for (int i=altura_tela/2; i<=altura_tela; i+=espacamento_x){
                render->desenhar_linha( &cor_grade,
                                        0,
                                        i,
                                        largura_tela,
                                        i);
                
                render->desenhar_linha( &cor_grade,
                                        0,
                                        i- altura_tela/2,
                                        largura_tela,
                                        i- altura_tela/2);
            }
        }
        
        void desenharGradeY(Renderizador *render){
            for (int i=largura_tela/2; i<=largura_tela; i+=espacamento_y){
                render->desenhar_linha( &cor_grade,
                                        i,
                                        0,
                                        i,
                                        altura_tela);
                
                render->desenhar_linha( &cor_grade,
                                        i- largura_tela/2,
                                        0,
                                        i- largura_tela/2,
                                        altura_tela);
            }
        }

    public:

        PlanoCartesiano(int espacamento_x, int espacamento_y, CorRGBA cor_eixos, CorRGBA cor_grade,
                            int largura_tela, int altura_tela):
            
            espacamento_x(espacamento_x),
            espacamento_y(espacamento_y),
            largura_tela(largura_tela),
            altura_tela(altura_tela),
            cor_eixos(cor_eixos),
            cor_grade(cor_grade){
        }

        void desenharGrade(Renderizador *render){
            desenharGradeX(render);
            desenharGradeY(render);
            desenharEixo(render);
        }
};

#endif