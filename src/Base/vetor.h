#include <iostream>
#include <math.h>
#include "ponto.h"

#ifndef VETOR_H
#define VETOR_H

/*!
    \file vetor.h
    \class Vetor
    \author Gabriel Eduardo Lima
    \date Última Modificação: 27/02/2002
    \brief Classe para Representação de um Vetor no Plano Cartesiano
*/

class Vetor {
    public:
        float x;        //!< Componente no eixo das Abscissas
        float y;        //!< Componente no eixo das Ordenadas

        //! Construtor Default
        /*!
            Chamado quando nenhum parâmetro de ininicialização for informado.
            
            Cria um objeto com ambas as componentes configuradas para 0, resultando
            em um vetor nulo.
        */
        Vetor():
            x(0), y(0){
        }

        //! Construtor Base a partir de Coordenadas
        /*!
            Cria um objeto com as componentes conforme valores passados por parâmetro.
            
            \param x usado para inicializar atributo de mesmo nomenclatura
            \param y usado para inicializar atributo de mesmo nomenclatura
        */
        Vetor(float x, float y):
            x(x), y(y){
        }

        //! Construtor a partir de pontos
        /*!
            Cria um objeto onde as componentes são calculadas a partir de
            dois pontos, sendo eles o ponto de Início e de Fim do vetor,
            inforamados por parâmetro.

            O cálculo do vetor dá-se da seguinte forma: Considere os Pontos 
            \f$ I(xi,yi) \f$ e \f$ F(xf,yf) \f$ representando respectivamente
            os parâmetros inicio e fim. As componentes do vetor dá-se da forma:
            \f$ \vec{v} = (xf-xi, yf-yi) \f$.
        
            \param inicio Referência constante a um \ref Ponto
            \param fim Referência constante a um \ref Ponto
        */
        Vetor(const Ponto &inicio, const Ponto &fim): 
            x(fim.x - inicio.x), y(fim.y - inicio.y){
        }

        //! Construtor de Cópia
        /*!
            Cria um novo objeto copiando as componentes de um vetor informado.

            \param vetor Referência constante para o \ref Vetor que será copiado
        */
        Vetor(const Vetor &vetor):
            x(vetor.x), y(vetor.y){
        }

        //! Construtor Move
        /*!
            Cria um novo objeto fazendo uso do recurso de movimentação. 
            Transfere de maneira eficiente os dados das componentes de um vetor 
            para o novo objeto criado.

            \param vetor Referência rvalue de um \ref Vetor

            Para mais detalhe sobre o recurso, consultar documentação da linguagem
        */
        Vetor (Vetor &&vetor) noexcept{
            x = vetor.x;
            y = vetor.y;
        }

        // Destrutor da Classe
        ~Vetor(){}
        
        //! Método para cálcular o módulo do objeto \ref Vetor
        /*!
            Cálculo efetuado através de: \f$ |v| = \sqrt{x^2 + y^2}\f$.

            \return O valor do módulo \f$|v|\f$
        */
        float getModulo() const{
            return pow((x*x + y*y),(1.0/2));
        }

        //! Método para cálcular o ângulo formado pelo vetor em relação ao eixo x.
        /*!
            Cálculo efetuado através de \f$\alpha = \arctan{(y/x)}\f$. 
            
            \return O ângulo \f$\alpha\f$ em Radianos
        */
        float getAngulo() const{
            return atan2(y,x);
        }

        //! Transforma um \ref Vetor para sua representação em \ref Ponto
        /*!
            Considere o vetor \f$ \vec{v} = (x,y) \f$. Diz-se que
            sua representação em como um ponto pode ser dada por 
            \f$ P(x,y) \f$.
            
            \return \ref Ponto conforme P
        */
        const Ponto vetorToPonto(){
            return Ponto(x,y);
        }

        //! Transforma um \ref Vetor para sua representação em \ref Matriz
        /*!
            Considere o vetor \f$ \vec{v} = (x,y) \f$. A representação em forma
            de matriz de \f$ v \f$ é dada como:

            \f[
                M = 
                \begin{bmatrix}
                        x \\
                        y \\
                        1
                \end{bmatrix}
            \f]	
            
            \return \ref Matriz 3x1 M
        */
        Matriz vetorToMatriz(){
            Matriz tmp = Matriz(3,1);
            
            tmp[0][0] = x;
            tmp[1][0] = y;
            tmp[2][0] = 1;

            return tmp;
        }
        
        //! Sobrecarga do Insertion Operator para Saída de Dados
        /*!
            \return uma string no formato: "Vetor(x,y)"
                    onde x e y são respectivamentes os valores
                    dos atributos de mesmo nome do objeto
        */
        friend std::ostream& operator<< (std::ostream &out, const Vetor &vetor){
            out << "Vetor(" << vetor.x << "," << vetor.y << ")";
            return out;
        };

        //! Soma de vetores
        /*!
            Soma as respectivas componentes dos vetores criando assim um 
            novo objeto \ref Vetor.

            \param vetor Referência constante ao Vetor referente a parcela direita da Operação
            \return Vetor resultante da Operação
        */
        Vetor operator+(const Vetor &vetor){
		    return Vetor(x + vetor.x, y + vetor.y);
	    }

        //! Subtração de Vetores
        /*!
            Subtrai as respectivas componentes dos vetores criando assim um novo objeto
            \ref Vetor.

            \param vetor Referência constante a um \ref Vetor referente a parcela direita da Operação
            \return \ref Vetor resultante da Operação
        */
        Vetor operator-(const Vetor &vetor){
		    return Vetor(x - vetor.x, y - vetor.y);
	    }

        //! Multiplicação de um \ref Vetor por um escalar.
        /*!
            Cria um novo objeto do tipo \ref Vetor através da
            multiplicação entre as componentes de um \ref Vetor
            por um escalar a esquerda da operação \b * .

            \param escalar valor \c float constante
            \param vetor Referência constante ao \ref Vetor base para a Multplicação
            \return \ref Vetor resultante da Operação
        */
        friend Vetor operator*(const float escalar, const Vetor &vetor){
		    return Vetor(vetor.x * escalar, vetor.y * escalar);
	    }

        //! Multiplicação de um \ref Vetor por um escalar.
        /*!
            Cria um novo objeto do tipo \ref Vetor através da
            multiplicação entre as componentes de um \ref Vetor
            por um escalar a direita da operação \b * .

            \param escalar valor \c float constante
            \param vetor Referência constante ao \ref Vetor base para a Multplicação
            \return \ref Vetor resultante da Operação
        */
        friend Vetor operator*(const Vetor &vetor, const float escalar){
		    return Vetor(vetor.x * escalar, vetor.y * escalar);
	    }

        //! Produto escalar de vetores.
        /*! 
            Multiplica as respesctivas componentes dos vetores,
            sendo que os valores resultantes desses produtos 
            são somados e retornados.

            \param vetor Referência constante a um \ref Vetor
            \return O resutlado \c float da Operação
        */
        float operator*(const Vetor &vetor){
		    return ((x * vetor.x) + (y * vetor.y));
        }

        //! Atribuição por Cópia
        /*!
            \param vetor Referência constante do \ref Vetor que será Copiado
            \return Referência para o \ref Vetor que Invocou o operador
        */
        Vetor& operator=(const Vetor &vetor){
            x = vetor.x;
            y = vetor.y;

            return *this;
        }

        //! Atribuição Move
        /*!
            \param vetor Referência rvalue do Vetor Base para a operação
            \return Referência para o \ref Vetor que Invocou o operador
        */
        Vetor& operator=(Vetor &&vetor) noexcept {
            /*
                Verifica se o parâmetro referencia o próprio objeto.
                Em caso de verdade, retorno a referência para o objeto
                atual. Em caso de falsidade, significa que a referência
                é para outro objeto e a movimentação dos atributos ocorre.
            */
            if (&vetor == this){
			    return *this;
            }

            x = vetor.x;
            y = vetor.y;

            return *this;
        }
};

#endif