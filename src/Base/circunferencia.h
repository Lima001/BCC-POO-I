#include <iostream>
#include <math.h>
#include "ponto.h"

#ifndef CIRCUNFERENCIA_H
#define CIRCUNFERENCIA_H

/*!
    \file circunferencia.h
    \class Circunferencia
    \author Gabriel Eduardo Lima
    \date Última Modificação: 27/02/2002
    \brief Classe para Representação de uma Circunferência.
           É a forma considerada como padrão para os objetos \ref Objeto
           da simulação
*/

class Circunferencia {
    public:
        int precisao;                       //!< Definição da quantidade de pontos usados para gerar a demarcação da circunferência 
        float raio;                         //!< Raio da Circunferência
        Ponto centro;                       //!< Centro da Circunferência
        Ponto* demarcacao = nullptr;        //!< Ponteiro que guarda as demarcações da circunferência - Usado para representação Gráfica. Por padrão é configurado para nullptr

        //! Construtor Default
        /*!
            Chamado quando nenhum parâmetro de ininicialização for informado.
            
            Cria um objeto com os valores numéricos ( \ref raio e \ref precisao) configurados para 0;
            Define como centro a Origem do Plano Cartesiano e \b não gera \ref demarcacao!
            Deve ser usado somente para declarar variáveis que serão configuradas posteriormente.

            \warning Deve-se cuidar com o fato da \ref demarcacao não ser inicializada na chamada
                     desse construtor. Observado isso, no momento de configuração do objeto
                     deve-se incocar o método membro \ref gerarDemarcacao() para alocar espaço
                     na memória para o uso correto do atributo
        */
        Circunferencia():
            precisao(0), raio(0), centro(Ponto()){
        }

        //! Construtor Base
        /*!
            Cria um objeto \ref Circunferencia com os atributos configurados conforme
            informado por parâmetro.

            Observação: A demarcação é gerada automáticamente ao chamar esse método.
            Tenha cuidado para a alocação de memória dinâmica automática.

            \param raio usado para inicializar o atributo de memsma nomenclatura
            \param centro usado para inicializar o atributo de memsma nomenclatura
            \param precisao usado para inicializar o atributo de memsma nomenclatura.
                            Em caso de omissão do valor, esse atributo será configurado
                            para um valor de \b 60, permitindo que a \ref demarcacao seja gerada
                            com um mínimo de qualidade julgada necessária
        */
        Circunferencia(float raio, const Ponto &centro, int precisao=60):
            raio(raio), centro(centro), precisao(precisao){

            gerarDemarcacao();        
        }

        //! Destrutor da Classe
        /*!
            Como destaque deve-se observar que esse método está
            encarregado de desalocar os espaços de memória dinamicamente
            alocados para a construção da \ref demarcacao da \ref Circunferencia
        */
        ~Circunferencia(){
            // Liberar espaço que foi dinâmicamente alocado quando existir ocorrência desse
            if (demarcacao != nullptr)
                delete [] demarcacao;
        }

        //! Construtor de Cópia
        /*!
            Cria um novo objeto copiando todos os atributos de uma \ref Circunferencia informada.
            Deve-se esclarecer que nesse caso, a demarcacao da circunferencia também será
            "copiada" uma vez que o método \ref gerarDemarcacao() é chamado após inicialização
            dos atributos básicos.

            \param circ Referência constante para a \ref Circunferência que será copiado
        */
        Circunferencia(const Circunferencia& circ):
            precisao(circ.precisao), raio(circ.raio), centro(circ.centro){
            
            gerarDemarcacao();
        }

        //! Construtor Move
        /*!
            Cria um novo objeto fazendo uso do recurso de movimentação. 
            Transfere de maneira eficiente os dados de uma \ref Circunferencia 
            para o novo objeto criado. Da mesma forma que ocorre no
            Construtor por cópia, a demarcacao da \ref Circunferencia também
            será "copiada" através de cálculo ao final da inicialização dos
            outros atributos básicos.

            \param circ Referência rvalue de uma \ref Circunferencia

            Para mais detalhe sobre o recurso, consultar documentação da linguagem
        */
        Circunferencia(Circunferencia &&circ) noexcept{
            precisao = circ.precisao;
            raio = circ.raio;
            
            // Uso da atribuição por movimentação implementada na classe Ponto
            centro = std::move(circ.centro);
            
            gerarDemarcacao();
        }

        //! Método usado para criar a demarcacao da Circunferencia
        /*!
            A demarcacao de uma \ref Circunferencia pode ser entendido como
            os pontos que fazem parte daquela circunferência. Conhecer
            esses pontos permitem que a circunferência seja desenhada
            por um objeto \ref Renderizador.

            A demarcacao é gerada de maneira estática e será sempre referente
            ao estado da \ref Circunferencia quando o método foi invocado. Isso
            siginifica que mudanças em qualquer outro atributo de um
            objeto \ref Circunferencia não alterará a demarcacao e essa manterá o
            seu último estado.

            Em caso de mudanças nos atributos de um objeto Circunferencia,
            recomenda-se analisar se existe a necessidade de manter uma
            demarcacao para esse objeto, uma vez que caso não seja necessário
            é possível economizar recursos como tempo e memória

            Outro aspecto é a Criação de objetos \ref Circunferencia. Conforme
            é possível ver na documentação desses Métodos, a demarcacao não
            é gerada automática para fins de otimização. Dessa forma deve-se
            estar atento para a chamada ao atributo demarcacao que pode ser
            um \c nullptr 
        */
        void gerarDemarcacao(){
            /* 
                Caso a demarcacao já existe, essa deve ser apagada para alocar
                a quantidade exata de memória, evitando uso de espaços de memória
                não pertencentes ao reservado para a demarcacao
            */
            if (demarcacao != nullptr){
                delete[] demarcacao;
                demarcacao = nullptr;
            }

            // Alocação dinâmica de memória para o atributo
            demarcacao = new Ponto[precisao];

            // Variável auxiliar
            Ponto p = Ponto();

            // Angulo entre os pontos da demarcacao
            float angulo = (360/precisao)*(M_PI/180.0f);

            for (int i=0; i<precisao; i++){
                p.x = centro.x + cos(angulo*i) * raio;
                p.y = centro.y + sin(angulo*i) * raio;
                
                // Uso da atribuição por movimentação implementada na classe Ponto
                demarcacao[i] = std::move(p);
            };
        }

        
        // Métodos de sobrecarga de operadores!
        
        //! Sobrecarga do Insertion Operator para Saída de Dados
        /*!
            \return uma string no formato: "Circunferencia(precisao,raio,Ponto(x,y))"
                    onde Ponto refere-se ao \ref centro da \ref Circunferencia
        */
        friend std::ostream& operator<< (std::ostream &out, const Circunferencia &circ){
            out << "Circunferencia(" << circ.precisao << "," << circ.raio << "," << circ.centro << ")";
            return out;
        }

        //! Atribuição por Cópia
        /*!
            Copia os atributos de uma Circunferência para a \ref Circunferencia que
            chamou a operação. 
            
            Observação: a \ref demarcacao não copiada e a \ref Circunferencia que incovou o
            método tem esse atributo configurado para \c nullptr e a memória desalocada.

            \param circ Referência constante da \ref Circunferencia que será Copiada
            \return Referência para a \ref Circunferencia que invocou o operador
        */
        Circunferencia& operator= (Circunferencia &circ){
            // Desalocar a memória da demarcacao visando resetar esse atributo ao estado padrão
            if (demarcacao != nullptr){
                delete [] demarcacao;
            }

            precisao = circ.precisao;
            raio = circ.raio;

            // Uso da atribuição por movimentação implementada na classe Ponto
            centro = std::move(circ.centro);
            
            // Configuração padrão do atributo demarcacao - Ponteiro Nulo
            demarcacao = nullptr;

            return *this;
        }

        //! Atribuição Move
        /*!
            Observação: a demarcacao não é movida e a Circunferencia que incovou o
            método tem esse atributo configurado para \c nullptr e a memória desalocada.

            \param vetor Referência rvalue do \ref Circunferencia base para a operação
            \return Referência para o \ref Circunferencia que invocou o operador
        */
        Circunferencia& operator= (Circunferencia &&circ) noexcept {
            /*
                Verifica se o parâmetro referencia o próprio objeto.
                Em caso de verdade, retorno a referência para o objeto
                atual. Em caso de falsidade, significa que a referência
                é para outro objeto e a movimentação dos atributos ocorre.
            */
            if (&circ == this){
			    return *this;
            }

            // Desalocar a memória da demarcacao visando resetar esse atributo ao estado padrão
            if (demarcacao != nullptr){
                delete [] demarcacao;
            }

            precisao = circ.precisao;
            raio = circ.raio;

            // Uso da atribuição por movimentação implementada na classe Ponto
            centro = std::move(circ.centro);
            
            // Configuração padrão do atributo demarcacao - Ponteiro Nulo
            demarcacao = nullptr;

            return *this;
        }
};

#endif