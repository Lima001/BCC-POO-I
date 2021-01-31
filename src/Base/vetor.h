#include <iostream>
#include <math.h>
#include "ponto.h"

#ifndef VETOR_H
#define VETOR_H

/*!
    \class Vetor
    \author Gabriel Eduardo Lima
    \date 11/11/2020
    Classe para Representação de um Vetor no Plano Cartesiano
*/

class Vetor {
    public:
        float x;        //!< Componente no eixo X - Constante Real que Múltiplica o vetor i
        float y;        //!< Componente no eixo Y - Constante Real que Múltiplica o vetor j

        //! Construtor Default
        Vetor():
            x(0), 
            y(0)
        {
        /*!
            Chamado quando nenhum parâmetro de ininicialização for informado.
            
            Cria um objeto com ambas as componentes configuradas para 0, resultando
            em um vetor nulo.
        */
        }

        //! Construtor Base a partir de Coordenadas
        Vetor(float x, float y):
            x(x),
            y(y)
        {
        /*!
            Cria um objeto com as componentes conforme valores passados por parâmetro
            
            \param x um float representando a Componente X
            \param y um float representando a Componente Y
        */
        }

        //! Construtor a partir de Pontos
        Vetor(const Ponto &inicio, const Ponto &fim): 
            x(fim.x - inicio.x),
            y(fim.y - inicio.y)
        {
        /*!
            Cria um objeto onde componentes calculadas a partir de
            dois pontos, sendo eles o ponto de Início e de Fim do vetor,
            inforamados por parâmetro.
        
            \param inicio uma referência constante a um objeto do tipo \ref Ponto
            \param fim uma referência constante a um objeto do tipo \ref Ponto
        */
        }

        //! Construtor de Cópia
        Vetor(const Vetor &vetor):
            x(vetor.x), 
            y(vetor.y)
        {
        /*!
            Cria um novo objeto copiando as componentes de um vetor informado.

            \param vetor uma referência constante para um Vetor
        */
        }

        //! Construtor Move
        Vetor (Vetor &&vetor) noexcept{
            /*!
                Cria um novo objeto fazendo uso do recurso de movimentação. 
                Transfere de maneira eficiente os dados das componentes de um vetor 
                para o novo objeto criado. 

                \param vetor uma referência rvalue de um Vetor

                Para mais detalhe sobre o recurso, consultar documentação da linguagem. 
            */
            x = vetor.x;
            y = vetor.y;
        }
        
        float getModulo() const{
             /*!
                Método para cálcular o módulo do objeto vetor.

                \return um número float 
            */
            return pow((x*x + y*y),(1.0/2));
        }

        float getAngulo() const{
            /*!
                Método para cálcular o angulo formado pelo Vetor
                em relação ao eixo x.
                
                \return um número float
            */
            return atan2(y,x);
        }

        const Ponto vetorToPonto(){
            /*!
                Método para obter uma formatação do Vetor
                para um \ref Ponto com coordenadas x e y
                respectivamente iguais ás componentes x e y
                
                \return um \ref Ponto 
            */
            return Ponto(x,y);
        }

        
        // Métodos de sobrecarga de operadores!
        friend std::ostream& operator<< (std::ostream &out, const Vetor &vetor){
            /*!
                Função amiga para ter acesso ao atributos protegidos da classe,
                visando sobscrita do operador << para apresentação de saída ao
                usuário.
                
                \return uma string no formato: xi + yj
            */
            out << vetor.x << "i +" << vetor.y << "j";
            return out;
        };

        Vetor operator+(const Vetor &vetor){
            /*!
                Soma de Vetores. Soma as componentes dos
                Vetores criando assim um novo objeto.

                \param vetor uma referência constante a um Vetor
                \return um objeto do tipo Vetor
            */
		    return Vetor(x + vetor.x, y + vetor.y);
	    }

        Vetor operator-(const Vetor &vetor){
            /*!
                Subtração de Vetores. Subtrai as componentes dos
                Vetores criando assim um novo objeto.

                \param vetor uma referência constante a um Vetor
                
                \return um objeto do tipo Vetor
            */
		    return Vetor(x - vetor.x, y - vetor.y);
	    }

        friend Vetor operator*(const float escalar, const Vetor &vetor){
            /*!
                Multiplicação de um Vetor por um escalar.
                Multiplica as componentes do Vetor por um escalar
                a esquerda da operação <b>*</b> criando assim um novo objeto.

                \param escalar um valor float constante
                \param vetor uma referência constante a um Vetor
               
                \return um objeto do tipo Vetor
            */
		    return Vetor(vetor.x * escalar, vetor.y * escalar);
	    }

        friend Vetor operator*(const Vetor &vetor, const float escalar){
            /*!
                Multiplicação de um Vetor por um escalar.
                Multiplica as componentes do Vetor por um escalar
                a direita da operação <b>*</b> criando assim um novo objeto.

                \param escalar um valor float constante
                \param vetor uma referência constante a um Vetor
               
                \return um objeto do tipo Vetor
            */
		    return Vetor(vetor.x * escalar, vetor.y * escalar);
	    }

        float operator*(const Vetor &vetor){
            /*!
                Produto Escalar de Vetores.
                
                Multiplica as componentes respesctivas dos Vetores, onde os
                valores do produto são somados e retornados.

                \param vetor uma referência constante a um Vetor
               
                \return um número int
            */
		    return ((x * vetor.x) + (y * vetor.y));
        }

        //! Atribuição por Cópia
        Vetor& operator=(const Vetor &vetor){
            /*!
                \param vetor uma referência constante de um Vetor
                \return Referência para o Vetor que Invocou o Método
            */
            x = vetor.x;
            y = vetor.y;

            return *this;
        }

        //! Atribuição Move
        Vetor& operator=(Vetor &&vetor) noexcept {
            /*!
                \param vetor uma referência rvalue de um Vetor
                \return Referência para o Vetor que Invocou o Método
            */

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