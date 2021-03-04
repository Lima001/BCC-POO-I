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

/*!
    \file renderizador.h
    \class Renderizador
    \author Gabriel Eduardo Lima
    \date Última alteração: 28/02/2021
    \brief Classe responsável pela abstração do processo de renderização de figuras
           na Área de renderização da janela
*/

class Renderizador{
    protected:
        SDL_Renderer* ptr_renderizador = nullptr;       //!< Ponteiro para o elemento Renderizador SDL que permite a chamada de funções de renderização
    
    public:

        Matriz Transformacao;                           //! Matriz 3x3 usada para Transformações Geométricas nas Figuras
        
        //! Construtor Default
        /*!
            Usado para inicializar um rederizador para um janela
            especificada por parâmetro. É nesse método que o
            Renderizador SDL é criado através da função SDL_CreateRenderer().
            A título de especificação, o Renderizador SDL é criado com a flag
            SDL_RENDERER_SOFTWARE. Para mais detalhes verifique a documentação
            da biblioteca SDL2.

            Observação: Em caso de problema no processo de criação do
            Renderizador SDL, uma mensagem de erro será disparada contendo
            o conteúdo retornado pela função SDL_GetError().

            \param ptr_janela Ponteiro para a Janela Gráfica SDL

            @see Janela
        */
        Renderizador(SDL_Window* ptr_janela){
            ptr_renderizador = SDL_CreateRenderer(ptr_janela, -1, SDL_RENDERER_SOFTWARE);

            if (ptr_renderizador == nullptr) {
                std::cout << "Erro ao criar Renderizador: " << SDL_GetError() << std::endl; 
            }
        }

        // Destrutor da Classe
        /*!
            Responsável por chamar a função SDL_DestroyRenderer()
            que destroi o Renderizador SDL criado.
        */
        ~Renderizador(){
            SDL_DestroyRenderer(ptr_renderizador);
        };

        //! Define uma cor para a renderização
        /*!
            Define a cor que deve ser usada para
            o processo de renderização. Uma vez configurada
            a cor será usada até que outra chamada seja realizada
            a esse mesmo método especificando uma nova cor.

            \param cor Referência constante para objeto do tipo \ref CorRGBA    
                       que especifica a cor de renderização
        */
        void setCorDesenho(const CorRGBA &cor){
            SDL_SetRenderDrawColor(ptr_renderizador, cor.r, cor.g, cor.b, cor.a);
        }

        //! Limpa a o Renderizador
        /*!
            Configura o Renderizador para um cor padrão e apaga
            qualquer renderização presente na Área de renderização
            da janela SDL.

            \param cor Referência constante para objeto do tipo \ref CorRGBA    
                       que especifica a cor de configuração do \ref Renderizador
        */
        void limpar(const CorRGBA &cor){
            setCorDesenho(cor);
            SDL_RenderClear(ptr_renderizador);
        }

        //! Atualiza o estado do Renderizador SDL
        /*!
            Esse método permite que as operações de renderização
            sejam passadas para a Área de renderização da Janela SDL.
            Caso esse método não seja chamado não será possível observar
            as ações de renderização desejadas pelo desenvolvedor.

            Observação: Recomenda-se a sua invocação ao final da definição
                        de todos os processos de renderização para evitar
                        chamadas desnecessárais. Além disso deve ser usado
                        em conjunto com o método de atualização presente
                        em \ref Janela .

            @see Janela
        */
        void atualizar(){
            SDL_RenderPresent(ptr_renderizador);
        }

        //! Solicita ao \ref Renderizador que um \ref Ponto seja desenhado
        /*!
            Dada uma cor e um ponto, esse será desenhado conforme
            especificado por suas coordenadas transformadas pela
            \ref Matriz de \ref Transformação .

            \param cor Referência constante para objeto do tipo \ref CorRGBA que define a cor da renderização do ponto
            \param ponto Referência constante para objeto do tipo \ref Ponto que será renderizador

            @see Ponto
        */
        void desenhar_ponto(const CorRGBA &cor, const Ponto &ponto){
            Matriz tmp = Transformacao * ponto.pontoToMatriz();

            setCorDesenho(cor);
            SDL_RenderDrawPoint(ptr_renderizador,
                                static_cast<int>(tmp[0][0]),
                                static_cast<int>(tmp[1][0]));
        }
        
        //! Solicita ao \ref Renderizador que uma linha seja desenhada
        /*!
            Dada uma cor e um as posições de inicio e fim de uma linha,
            essa será desenhada conforme os parâmetros transformados pela
            Matriz de \ref Transformação .

            \param cor Referência constante para objeto do tipo \ref CorRGBA que define a cor da renderização da linha
            \param xi coordenada x do ponto inicial da Linha
            \param yi coordenada y do ponto inicial da Linha
            \param xf coordenada x do ponto final da Linha
            \param yf coordenada y do ponto final da Linha
        */
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
        
        //! Solicita ao \ref Renderizador que uma \ref Circunferencia seja desenhada
        /*!
            Dada uma cor e uma circunferência, essa será desenhado conforme
            especificado por suas coordenadas de centro e demarcacao transformadas pela
            Matriz de \ref Transformação .

            \param cor Referência constante para objeto do tipo \ref CorRGBA que define a cor da renderização do ponto
            \param circ Referência constante para objeto do tipo \ref Circunferencia que será renderizador

            @see Circunferencia
        */
        void desenhar_circunferencia(const CorRGBA &cor, const Circunferencia &circ){
            setCorDesenho(cor);

            Ponto* demarcacao = circ.demarcacao;
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
        
        //! Solicita ao \ref Renderizador que um \ref Triangulo seja desenhada
        /*!
            Dada uma cor e um triângulo, essa será desenhado conforme
            especificado por seus vértices transformados pela
            Matriz de \ref Transformação

            \param cor Referência constante para objeto do tipo \ref CorRGBA que define a cor da renderização do ponto
            \param triangulo Referência constante para objeto do tipo \ref Triangulo que será renderizador

            @see Triangulo
        */
        void desenhar_triangulo(const CorRGBA &cor, const Triangulo &triangulo){
            desenhar_linha(cor, triangulo.p1.x, triangulo.p1.y, triangulo.p2.x, triangulo.p2.y);
            desenhar_linha(cor, triangulo.p1.x, triangulo.p1.y, triangulo.p3.x, triangulo.p3.y);
            desenhar_linha(cor, triangulo.p2.x, triangulo.p2.y, triangulo.p3.x, triangulo.p3.y);
        
        }
        
        //! Solicita ao \ref Renderizador que um \ref Retangulo seja desenhada
        /*!
            Dada uma cor e um retângulo, essa será desenhado conforme
            especificado por seus vértices calculados
            a partir do Ponto inicial e das medidas de altura e largura transformados pela
            Matriz de \ref Transformação .

            \param cor Referência constante para objeto do tipo \ref CorRGBA que define a cor da renderização do ponto
            \param triangulo Referência constante para objeto do tipo \ref Triangulo que será renderizador
        
            @see Retangulo
        */
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

        //! Solicita ao \ref Renderizador que um \ref Vetor seja desenhada
        /*!
            Dada uma cor e um vetor, esse será desenhado conforme
            especificado por suas coordenadas a partir de um
            ponto de início informado e será transformado pela
            Matriz de \ref Transformação .

            \param cor Referência constante para objeto do tipo \ref CorRGBA que define a cor da renderização do ponto
            \param vetor Referência constante para objeto do tipo \ref Vetor que será renderizador
            \param inicio Referência constante para objeto do tipo \ref Ponto que define o ponto de início 
                          para renderização do Vetor, observado que esse é armazenado pela classe \ref Vetor
                          como sempre em relação a Origem do plano cartesiano

        */
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