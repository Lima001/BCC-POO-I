#ifndef PLANO_CARTESIANO_H
#define PLANO_CARTESIANO_H

#include <SDL.h>
#include "renderizador.h"

/*!
    \file plano_cartesiano.h
    \class PlanoCartesiano
    \author Gabriel Eduardo Lima
    \date Última alteração: 28/02/2021
    \brief Classe responsável pela representação gráfica do Plano Cartesiano
*/

class PlanoCartesiano {
    protected:
        
        int espacamento_x;          //!< Distância entre as retas paralelas ao eixo x
        int espacamento_y;          //!< Distância entre as retas paralelas ao eixo y
        int largura_tela;           //!< Largura da tela para desenhar o plano dentro dos limites da aplicação
        int altura_tela;            //!< Altura da tela para desenhar o plano dentro dos limites da aplicação
        Ponto origem;               //!< Ponto de Origem do Plano Cartesiano na Tela
        CorRGBA cor_eixos;          //!< Cor dos eixos das abscissas e das ordenadas
        CorRGBA cor_grade;          //!< Cor das retas paralelas aos eixos das abscissas e das ordenadas

    public:

        //! Construtor Default
        /*!
            Cria um objeto com os atributos conforme valores especificados
            via parâmetro.

            \param espacamento_x inicializa o atributo de mesma nomenclatura
            \param espacamento_y inicializa o atributo de mesma nomenclatura
            \param cor_eixos inicializa o atributo de mesma nomenclatura
            \param cor_grade inicializa o atributo de mesma nomenclatura
            \param largura_tela inicializa o atributo de mesma nomenclatura
            \param altura_tela inicializa o atributo de mesma nomenclatura
            \param origem inicializa o atributo de mesma nomenclatura. Caso
                          seja omitido, será considerado como origem o Ponto(0,0)
                          da Tela
        */
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

        //! Destrutor da Classe
        ~PlanoCartesiano(){}

        //! Desenha os Eixos do Plano Cartesiano
        /*!
            \param render Referência constante para objeto do tipo \ref Renderizador
                          que será usado para o processo de renderização.

            @see Renderizador
        */
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

        //! Desenha as retas paralelas ao Eixo y
        /*!
            \param render Referência constante para objeto do tipo \ref Renderizador
                          que será usado para o processo de renderização.

            @see Renderizador
        */
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
        
        //! Desenha as retas paralelas ao Eixo x
        /*!
            \param render Referência constante para objeto do tipo \ref Renderizador
                          que será usado para o processo de renderização.

            @see Renderizador
        */
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

        //! Desenha as retas paralelas aos Eixos x e y do Plano, bem como os Próprios Eixos 
        /*!
            Faz uso dos métodos membros responsáveis pela renderização de cada
            elemento específico do Plano Cartesiano.

            \param render Referência constante para objeto do tipo \ref Renderizador
                          que será usado para o processo de renderização

            @see Renderizador
        */
        void desenharGrade(Renderizador &render){
            /*
                Criação de uma Matriz de Transformação temporária para armazenar
                a Matriz atual de Transformação usada pelo Renderizador, visto que
                para o plano cartesiano deve-se consdiderar coordenadas padrão da
                janela gráfica, algo que pode ter sido alterado para o processo
                de renderização gráfica do Sistema
            */
            Matriz tmp = render.transformacao;
            
            // Uso do recurso de Atribuição por Movimentação implementado na classe Matriz
            render.transformacao = std::move(Matriz(3,3));
            
            // Definição de uma Matriz Identidade 3x3
            render.transformacao[0][0] = 1;
            render.transformacao[1][1] = 1;
            render.transformacao[2][2] = 1;

            desenharGradeX(render);
            desenharGradeY(render);
            desenharEixo(render);

            // Uso do recurso de Atribuição por Movimentação implementado na classe Matriz
            // Faz com que a Matriz de Transformação volte ao seu valor anterior a renderiazção do Plano
            render.transformacao = std::move(tmp);
        }
};

#endif