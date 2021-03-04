#include "ponto.h"

#ifndef TRIANGULO_H
#define TRIANGULO_H

/*!
    \file triangulo.h
    \class Triangulo
    \author Gabriel Eduardo Lima
    \date Última Modificação: 27/02/2001
    \brief Classe para Representação de um Triangulo
*/

class Triangulo {
    public:
        Ponto p1;    //!< Vértice 01 do triângulo;
        Ponto p2;    //!< Vértice 02 do triângulo;
        Ponto p3;    //!< Vértice 03 do triângulo;
        // A ordem em que os vertices são definidos não rerpesenta importância
        
        //! Construtor Default
        /*!
            Chamado quando nenhum parâmetro de ininicialização for informado.

            Cria um objeto do tipo \ref Triangulo com vértices nulo. Usar somente
            para declaração de variáveis. Não esquecer de modificar os atributos
            para fazer o correto uso do objeto.
        */
        Triangulo():
            p1(Ponto()), p2(Ponto()), p3(Ponto()){
        }

        //! Construtor Base
        /*!
            Cria um objeto com os objetos \ref Ponto passados como parâmetro.
                        
            \param p1 Referência constante a um \ref Ponto usado para inicializar o atributo de mesma nomenclatura
            \param p2 Referência constante a um \ref Ponto usado para inicializar o atributo de mesma nomenclatura
            \param p3 Referência constante a um \ref Ponto usado para inicializar o atributo de mesma nomenclatura
        */
        Triangulo(const Ponto &p1, const Ponto &p2, const Ponto &p3):
            p1(p1), p2(p2), p3(p3){
        }

        //! Construtor de Cópia
        /*!
            Cria um novo objeto copiando os pontos de um \ref Triangulo informado.

            \param t Referência constante para o \ref Triangulo que será copiado
        */
        Triangulo(const Triangulo &t):
            p1(t.p1), p2(t.p2), p3(t.p3){    
        }

        //! Construtor Move
        /*!
            Cria um novo objeto fazendo uso do recurso de movimentação 
            Transfere de maneira eficiente os dados dos vertices de um \ref Triangulo 
            para o novo objeto criado
            
            \param t Referência rvalue de um \ref Triangulo

            Para mais detalhe sobre o recurso, consultar documentação da linguagem
        */
        Triangulo(Triangulo &&t) noexcept{
            p1 = std::move(t.p1); p2 = std::move(t.p2); p3 = std::move(t.p3);
        }

        // Destrututor da Classe
        ~Triangulo(){}
        
        // Métodos de sobrecarga de operadores!

        //! Sobrecarga do Insertion Operator para Saída de Dados
        /*!
            \return string no formato: "Triangulo(Ponto(x1,y1),Ponto(x2,y2),Ponto(x3,y3))"
                    onde cada Ponto representa os atributos do objeto que invocou o operador
        */
        friend std::ostream& operator<< (std::ostream &out, const Triangulo &t){
            out << "Triangulo(" << t.p1 << "," << t.p2 << "," << t.p3 << ")";
            return out;
        }

        //! Atribuição por Cópia
        /*!
            Copia o valor dos atributos do \ref Triangulo passado por parâmetro
            para o \ref Triangulo que chamou a operação.

            \param t Referência constante do \ref Triangulo que deseja-se copiar
            \return Referência para o \ref Triangulo que invocou o operdador
        */
        Triangulo& operator= (Triangulo &t){
            // Uso da atribuição por movimentação implementada na classe Ponto
            p1 = std::move(t.p1);
            p2 = std::move(t.p2);
            p3 = std::move(t.p3);

            return *this;
        }

        //! Atribuição Move
        /*!
            \param t Referência rvalue de um \ref Triangulo
            \return Referência para o \ref Triangulo que invocou o operador
        */
        Triangulo& operator= (Triangulo &&t) noexcept {
            /*
                Verifica se o parâmetro referencia o próprio objeto.
                Em caso de verdade, retorno a referência para o objeto
                atual. Em caso de falsidade, significa que a referência
                é para outro objeto e a movimentação dos atributos ocorre.
            */
            if (&t == this){
			    return *this;
            }

            // Uso da atribuição por movimentação implementada na classe Ponto
            p1 = std::move(t.p1);
            p2 = std::move(t.p2);
            p3 = std::move(t.p3);

            return *this;
        }
};

#endif