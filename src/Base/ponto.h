#include <iostream>
#include <fstream>
#include "matriz.h"

#ifndef PONTO_H
#define PONTO_H

/*!
    \file ponto.h
    \class Ponto
    \author Gabriel Eduardo Lima
    \date Última Modificação: 27/02/2001
    \brief Classe para Representação de um Ponto no Plano Cartesiano
*/

class Ponto {
    public:
        float x;        //!< Coordenada no eixo das abscissas
        float y;        //!< Coordenada no eixo das ordenadas
    
        //! Construtor Default
        /*!
            Chamado quando nenhum parâmetro de ininicialização for informado.
            
            Cria um objeto com ambas as coordenadas configuradas para
            a origem do Plano Cartesiano \f$ O(0,0)\f$.
        */
        Ponto(): 
            x(0), y(0){
        }

        //! Construtor Base
        /*!
            Cria um objeto com as coordenadas passadas como parâmetro.
            
            \param x usado para inicializar atributo de mesma nomenclatura
            \param y usado para inicializar atributo de mesma nomenclatura
        */
        Ponto(float x, float y): 
            x(x), y(y){
        }

        //! Construtor de Cópia
        /*!
            Cria um novo objeto copiando as coordenadas de um \ref Ponto informado.

            \param p Referência constante para o \ref Ponto que será copiado
        */
        Ponto(const Ponto &p):
            x(p.x), y(p.y){
        }

        //! Construtor Move
        /*!
            Cria um novo objeto fazendo uso do recurso de movimentação. 
            Transfere de maneira eficiente os dados das coordenadas de um \ref Ponto 
            para o novo objeto criado.
            
            \param p Referência rvalue para um \ref Ponto

            Para mais detalhe sobre o recurso, consultar documentação da linguagem
        */
        Ponto(Ponto &&p) noexcept{
            x = p.x;
            y = p.y;
        }

        //! Destrutor da Classe
        ~Ponto(){}

        //! Transforma um ponto para sua representação em \ref Matriz
        /*!
            Considere o ponto \f$ P(x,y)\f$. A representação em forma
            de matriz de \f$ P \f$ é dada como:

            \f[
                M = 
                \begin{bmatrix}
                        x \\
                        y \\
                        1
                \end{bmatrix}
            \f]

            Esse método é importante, uma vez que um ponto em sua forma
            de matriz pode ser usado para operações de transformação úteis
            ao processo de representação gráfica de figuras. Para mais detalhes
            @see Renderizador

            \return \ref Matriz 3x1 \f$ M \f$
        */
        Matriz pontoToMatriz() const{
            Matriz tmp = Matriz(3,1);
        
            tmp[0][0] = x;
            tmp[1][0] = y;
            tmp[2][0] = 1;

            return tmp;
        }

        // Métodos de Sobrecarga de Operadores

        //! Sobrecarga do Insertion Operator para Saída de Dados
        /*!
            \return string no formato: "Ponto(x,y)"
                    onde x e y são respectivamente os valores
                    dos atributos de mesmo nome do objeto
        */
        friend std::ostream& operator<<(std::ostream &out, const Ponto &ponto){
            out << "Ponto(" << ponto.x << "," << ponto.y << ")";
            return out;
        }

        //! Atribuição por Cópia
        /*!
            Copia o valor dos atributos do \ref Ponto passado por parâmetro
            para o \ref Ponto que invocou o operador.

            \param p Referência constante do \ref Ponto que deseja-se copiar
            \return Referência para o \ref Ponto que invocou o operador
        */
        Ponto& operator=(const Ponto &p){
            x = p.x;
            y = p.y;
            
            return *this;
        }

        //! Atribuição por Movimentação
        /*!
            \param p Referência rvalue de um \ref Ponto
            \return Referência para o \ref Ponto que Invocou o operador
        */
        Ponto& operator=(Ponto &&p) noexcept {
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