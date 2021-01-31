#include <iostream>
#include "matriz.h"

#ifndef PONTO_H
#define PONTO_H

/*!
    \class Ponto
    \author Gabriel Eduardo Lima
    \date 11/11/2020
    Classe para Representação de um Ponto no Plano Cartesiano
*/

class Ponto {
    public:
        float x;        //!< Coordenada no eixo x
        float y;        //!< Coordenada no eixo y
    
        //! Construtor Default
        /*!
            Chamado quando nenhum parâmetro de ininicialização for informado.
            
            Cria um objeto com ambas as coordenadas configuradas para
            a origem do Plano Cartesiano (0,0)
        */
        Ponto(): 
            x(0), y(0){
        }

        //! Construtor Base
        /*!
            Cria um objeto com as coordenadas passadas como parâmetro
            \param x um float representando a Coordenada X
            \param y um float representando a Coordenada Y
        */
        Ponto(float x, float y): 
            x(x), y(y){
        }

        //! Construtor de Cópia
        /*!
            Cria um novo objeto copiando as coordenadas de um ponto informado 
            \param p uma referência constante para um Ponto
        */
        Ponto(const Ponto &p):
            x(p.x), y(p.y){
        }

        //! Construtor Move
        /*!
            Cria um novo objeto fazendo uso do recurso de movimentação. 
            Transfere de maneira eficiente os dados das coordenadas de um ponto 
            para o novo objeto criado. 
            \param p uma referência rvalue de um Ponto

            Para mais detalhe sobre o recurso, consultar documentação da linguagem. 
        */
        Ponto(Ponto &&p) noexcept{
            x = p.x;
            y = p.y;
        }

        //! Destrutor da Classe
        ~Ponto(){}

        /*!
            Transforma um ponto para sua representação em matriz

            Cria uma matriz 3x1, onde cada linha representa uma coordenada
            do ponto. Pelo fato desta classe representar apenas pontos no
            Plano, a coordenada z na matriz é representada por 1.

            Esse método é importante, uma vez que o ponto em sua forma
            de matriz pode ser usado para operações de transformação úteis
            ao processo de representação gráfica de figuras.

            \return uma \ref Matriz 3x1
        */
        Matriz pontoToMatriz()const{
            Matriz tmp = Matriz(3,1);
            tmp[0][0] = x;
            tmp[1][0] = y;
            tmp[2][0] = 1;

            return tmp;
        }

        // Métodos de Sobrecarga de Operadores

        friend std::ostream& operator<<(std::ostream &out, const Ponto &ponto){
            /*!
                Função amiga para ter acesso ao atributos protegidos da classe,
                visando sobscrita do operador << para apresentação de saída ao
                usuário.
                \return uma string no formato: (x,y)
            */
            
            out << "(" << ponto.x << ", " << ponto.y << ")";
            return out;
        }

        //! Atribuição por Cópia
        Ponto& operator=(const Ponto &p){
            /*!
                \param p uma referência constante de um Ponto
                \return Referência para o Ponto que Invocou o Método
            */
            x = p.x;
            y = p.y;
            
            return *this;
        }

        //! Atribuição por Movimentação
        Ponto& operator=(Ponto &&p) noexcept {
            /*!
                \param p uma referência rvalue de um Ponto
                \return Referência para o Ponto que Invocou o Método
            */

            /*
                Verifica se o parâmetro referencia o próprio objeto.
                Em caso de verdade, retorno a referência para o objeto
                atual. Em caso de falsidade, significa que a referência
                é para outro objeto e a movimentação dos atributos ocorre.
            */
            if (&p == this){
			    return *this;
            }

            x = p.x;
            y = p.y;

            return *this;
        }
};

#endif