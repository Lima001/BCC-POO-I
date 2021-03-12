#ifndef ACELERACAO_H
#define ACELERACAO_H

#include <iostream>
#include <fstream>

/*!
    \file aceleracao.h
    \class Acelerecao
    \author Gabriel Eduardo Lima
    \date Última Modificação: 27/02/2001
    \brief Classe usada para Definir as leis de aceleração que regem a movimentação
           de um \ref Objeto tanto no sentido vertical quanto horizontal
*/

class Aceleracao {
    public:

        double (*func_x)(double) = nullptr;         //!< Ponteiro para uma função do tipo double function(double) - Usado para calcular a aceleração no eixo x
        double (*func_y)(double) = nullptr;         //!< Ponteiro para uma função do tipo double function(double) - Usado para calcular a aceleração no eixo y

        //! Construtor Default
        /*!
            Chamado quando nenhum parâmetro de ininicialização for informado.
            
            Cria um objeto com os atributos não modificados. Isso significa
            que os ponteiros estarão configurados como \c nullptr. Esse 
            construtor deve ser somente usado quando deseja-se declarar
            uma variável que serve de referência a um objeto \ref Aceleração,
            onde a configuração de seus atributos será realizada posteriormente.

            Objetos gerados por esse construtor não estão aptos a serem usados
            como parâmetro em classes que fazem seu uso!
        */
        Aceleracao(){};

        //! Construtor Base
        /*!
            Cria um objeto com os ponteiros configurados para apontar
            para o endereço de funções passados como parâmetro.
            
            \param \double (*func_x_)(double) usado para inicializar double (*func_x)(double)
            \param \double (*func_y_)(double) usado para inicializar double (*func_y)(double)
        */
        Aceleracao(double (*func_x_)(double), double (*func_y_)(double)){
            func_x = func_x_;
            func_y = func_y_;
        }

        //! Construtor de Cópia
        /*!
            Cria um novo objeto copiando os enedereços das funções de um objeto
            Aceleração informado.

            \param aceleracao Referência constante para a \ref Aceleração que será copiado
        */
        Aceleracao(const Aceleracao &aceleracao):
            func_x(aceleracao.func_x),
            func_y(aceleracao.func_x){
        }

        //! Construtor Move
        /*!
            Cria um novo objeto fazendo uso do recurso de movimentação 
            Transfere de maneira eficiente os endereços de um objeto 
            para o novo objeto criado.
            
            \param aceleracao Referência rvalue para uma \ref Aceleracao

            Para mais detalhe sobre o recurso, consultar documentação da linguagem
        */
        Aceleracao(Aceleracao &&aceleracao) noexcept{
            func_x = aceleracao.func_x;
            func_y = aceleracao.func_y;
        }

        //! Destrutor da Classe
        ~Aceleracao(){};

        // Sobrecarga de Operadores

        //! Atribuição por Cópia
        /*!
            Copia o valor dos atributos da \ref Aceleracao passado por parâmetro
            para a que invocou o operador.

            \param aceleracao Referência constante da \ref Aceleracao que deseja-se copiar
            \return Referência para a \ref Aceleracao que invocou o operador
        */
        Aceleracao& operator= (Aceleracao &aceleracao){
            func_x = aceleracao.func_x;
            func_y = aceleracao.func_y;

            return *this;
        }
        
        //! Atribuição por Movimentação
        /*!
            \param aceleracao Referência rvalue de um \ref Aceleracao
            \return Referência para o objeto \ref Aceleracao que invocou o operador
        */
        Aceleracao& operator= (Aceleracao &&aceleracao) noexcept {
            if (&aceleracao == this){
			    return *this;
            }

            func_x = aceleracao.func_x;
            func_y = aceleracao.func_y;

            return *this;
        }

        //! Sobrecarga do Insertion Operator para Saída de Dados
        /*!
            \return string no formato: "Acelerecao(endereco_funcao_x,endereco_funcao_y)"
                    onde endereco_funcao_[x/y] referem-se ao endereços da memória
                    das respectivas funções que os ponteiros apontam
        */
        friend std::ostream& operator<< (std::ostream &out, const Aceleracao &a){
            out << "Aceleracao(" << &a.func_x << "," << &a.func_y << ")";
            return out;
        };
};

#endif