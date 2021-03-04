#include <iostream>
#include "ponto.h"

#ifndef RETANGULO_H
#define RETANGULO_H

/*!
    \file retangulo.h
    \class Retangulo
    \author Gabriel Eduardo Lima
    \date Última Modificação: 27/02/2001
    \brief Classe para Representação de um Retângulo
*/


class Retangulo {
    public:
        Ponto inicio;       //!< Ponto de início do retângulo - Considerar ponto Superior Esquerdo da Figura
        float largura;      //!< Medida da Largura do retângulo
        float altura;       //!< Medida da Altura do retangulo
        
        //! Construtor Default
        /*!
            Chamado quando nenhum parâmetro de ininicialização for informado.

            Cria um objeto do tipo \ref Retangulo com perímetro nulo. Usar somente
            para declaração de variaveis. Não esquecer de modificar os atributos
            para fazer o correto uso do objeto.
        */
        Retangulo():
            inicio(Ponto()), largura(0), altura(0){
        }

        //! Construtor base
        /*!
            Cria um objeto a partir dos parâmetros informados.

            \param inicio Referência constante a um \ref Ponto usado para inicializar o atributo de mesma nomenclatura
            \param largura usado para inicializar o atributo de mesma nomenclatura
            \param float usado para inicializar o atributo de mesma nomenclatura
        */
        Retangulo(const Ponto &inicio, float largura, float altura):
            inicio(inicio), largura(largura), altura(altura){
        }

        //! Construtor de Cópia
        /*!
            Cria um novo objeto copiando os atributos de um \ref Retangulo informado.

            \param t Referência constante para o \ref Retangulo que deseja-se copiar
        */
        Retangulo(const Retangulo &rect):
            inicio(rect.inicio), largura(rect.largura), altura(rect.altura){
        }

        //! Construtor Move
        /*!
            Cria um novo objeto fazendo uso do recurso de movimentação 
            Transfere de maneira eficiente os dados de um \ref Retangulo 
            para o novo objeto criado
            
            \param t Referência rvalue de um \ref Retangulo

            Para mais detalhe sobre o recurso, consultar documentação da linguagem
        */
        Retangulo(Retangulo &&rect) noexcept{
            inicio = std::move(rect.inicio);
            largura = rect.largura;
            altura = rect.altura;
        }

        // Destrutor da Classe
        ~Retangulo(){}

        // Métodos de sobrecarga de operadores!
        
        //! Sobrecarga do Insertion Operator para Saída de Dados
        /*!
            \return string no formato: "Retangulo(Ponto(x,y),largura,altura)"
                    onde cada elemento refere-se aos valores dos atributos.
        */
        friend std::ostream& operator<< (std::ostream &out, const Retangulo &rect){
            out << rect.inicio << "\n" << "[" << rect.largura << " X " << rect.altura << "]";
            return out;
        }

        //! Atribuição por Cópia
        /*!
            Copia o valor dos atributos do \ref Retangulo passado por parâmetro
            para o \ref Retangulo que invocou o operador.

            \param rect Referência constante do \ref Retangulo que deseja-se copiar
            \return Referência para o \ref Retangulo que invocou o operador
        */
        Retangulo& operator= (const Retangulo &rect){
            // Uso da atribuição por movimentação implementada na classe Ponto
            inicio = std::move(rect.inicio);
            
            largura = rect.largura;
            altura = rect.altura;

            return *this;
        }

        //! Atribuição Move
        /*!
            \param rect Referência rvalue de um \ref Retangulo
            \return Referência para o \ref Retangulo que Invocou o operador
        */
        Retangulo& operator= (Retangulo &&rect) noexcept {
            /*
                Verifica se o parâmetro referencia o próprio objeto.
                Em caso de verdade, retorno a referência para o objeto
                atual. Em caso de falsidade, significa que a referência
                é para outro objeto e a movimentação dos atributos ocorre.
            */
            if (&rect == this){
			    return *this;
            }

            // Uso da atribuição por movimentação implementada na classe Ponto
            inicio = std::move(rect.inicio);
            
            largura = rect.largura;
            altura = rect.altura;

            return *this;
        }
};

#endif