#ifndef LINHA_H
#define LINHA_H

#include "vetor.h"
/*!
    \file linha.h
    \class Linha
    \author Gabriel Eduardo Lima
    \date Última Modificação: 27/02/2001
    \brief Classe para Representação de um Segmento de reta no Plano Cartesiano
           Usada para definição de limites nos quais os objetos da simulação colidem,
           e principalmente para o cálculo da reflexão especular.
           
           @see DetectorColisao
           @see https://en.wikipedia.org/wiki/Specular_reflection
*/

class Linha {
    public:
        
        Ponto p1;               //!< ponto de Início do segmento de Reta
        Ponto p2;               //!< ponto de Fim do segmento de Reta
        Vetor normal;           //!< vetor normal a Linha direcionado ao Centro da Tela

        //! Construtor Default
        /*!
            Chamado quando nenhum parâmetro de ininicialização for informado.
            
            Cria um objeto com ambas atributos construídos usando o seu respectivo
            construtor Default. @see Vetor @see Ponto
        */
        Linha():
            p1(Ponto()), p2(Ponto()), normal(Vetor()){
        }


        //! Construtor Base
        /*!
            Cria um objeto a partir dos objetos \ref Ponto passados como parâmetro.
            Observação: Não é necessário/possível informar o \ref Vetor normal
            no processo de Construção e Inicialização do objeto, uma vez
            que esse atributo é automáticamente calculado pelo Método.

            A título de especificação, o cálculo de um vetor normal pode ser
            dado da seguinte forma: Considere a reta \em r definida
            pelo vetor diretor \f$ \vec{d} = (x,y) \f$. Pode-se definir
            um vetor normal a essa reta como \f$ \vec{n} = (-y,x) \f$
            
            \param p1 usado para inicializar atributo de mesmo nomenclatura
            \param p2 usado para inicializar atributo de mesmo nomenclatura
        */
        Linha(const Ponto &p1, const Ponto &p2):
            p1(p1), p2(p2){
            
            Vetor d = Vetor(p1,p2);                     // Vetor diretor da Reta/Segmento de Reta criado
            normal = Vetor(-d.y,d.x);                   // Cálculo do Vetor Normal
            normal = normal * (1.f/normal.getModulo()); // Tranformação do Vetor Normal em Unitário a fins de simplificação
        }

        //! Destrutor da Classe
        ~Linha(){}
};

#endif