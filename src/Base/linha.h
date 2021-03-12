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
        
        Ponto inicio;            //!< ponto de Início do segmento de Reta
        Ponto fim;               //!< ponto de Fim do segmento de Reta
        Vetor normal;            //!< vetor normal a Linha direcionado ao Centro da Tela

        //! Construtor Default
        /*!
            Chamado quando nenhum parâmetro de ininicialização for informado.
            
            Cria um objeto com ambas atributos construídos usando o seu respectivo
            construtor Default. @see Vetor @see Ponto
        */
        Linha():
            inicio(Ponto()), fim(Ponto()), normal(Vetor()){
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
            
            \param inicio usado para inicializar atributo de mesmo nomenclatura
            \param fim usado para inicializar atributo de mesmo nomenclatura
        */
        Linha(const Ponto &inicio, const Ponto &fim):
            inicio(inicio), fim(fim){
            
            Vetor d = Vetor(inicio,fim);                     // Vetor diretor da Reta/Segmento de Reta criado
            normal = Vetor(-d.y,d.x);                   // Cálculo do Vetor Normal
            normal = normal * (1.f/normal.getModulo()); // Tranformação do Vetor Normal em Unitário a fins de simplificação
        }

        //! Destrutor da Classe
        ~Linha(){}

        //! Construtor de Cópia
        /*!
            Cria um novo objeto copiando os pontos e vetor de uma Linha informado.

            \param l Referência constante para o \ref Linha que será copiado
        */
        Linha(const Linha &l):
            inicio(l.inicio), fim(l.fim), normal(l.normal){    
        }

        //! Construtor Move
        /*!
            Cria um novo objeto fazendo uso do recurso de movimentação. 
            Transfere de maneira eficiente os atributos de uma \ref Linha 
            para o novo objeto criado.
            
            \param l Referência rvalue para uma \ref Linha

            Para mais detalhe sobre o recurso, consultar documentação da linguagem
        */
        Linha(Linha &&l) noexcept{
            // Uso do recurso de movimentatção implementado em outras classes
            inicio = std::move(l.inicio);
            fim = std::move(l.fim);
            normal = std::move(l.normal);
        };

        // Sobrecarga de operadores


        //! Sobrecarga do Insertion Operator para Saída de Dados
        /*!
            \return string no formato: "Linha(Ponto(x1,y1),Ponto(x2,y2),Vetor(x,y))"
                    onde os Pontos e o Vetor são respectivamente os valores
                    dos atributos de mesmo nome do objeto e são exibidos
                    conforme sua implementação. @see Ponto @see Vetor
        */
        friend std::ostream& operator<<(std::ostream &out, const Linha &linha){
            out << "Linha(" << linha.inicio << "," << linha.fim << "," << linha.normal << ")";
            return out;
        }

        //! Atribuição por Cópia
        /*!
            Copia o valor dos atributos da \ref Linha passado por parâmetro
            para a \ref Linha que invocou o operador.

            \param l Referência constante da \ref Linha que deseja-se copiar
            \return Referência para a \ref Linha que invocou o operador
        */
        Linha& operator=(const Linha &l){
            inicio = l.inicio;
            fim = l.fim;
            normal = l.normal;

            return *this;
        }

        //! Atribuição por Movimentação
        /*!
            \param l Referência rvalue de uma \ref Linha
            \return Referência para a \ref Linha que Invocou o operador
        */
        Linha& operator=(Linha &&l) noexcept {
            /*
                Verifica se o parâmetro referencia o próprio objeto.
                Em caso de verdade, retorno a referência para o objeto
                atual. Em caso de falsidade, significa que a referência
                é para outro objeto e a movimentação dos atributos ocorre.
            */
            if (&l == this){
			    return *this;
            }

            // Uso do recurso de movimentatção implementado em outras classes
            inicio = std::move(l.inicio);
            fim = std::move(l.fim);
            normal = std::move(l.normal);

            return *this;
        }
};

#endif