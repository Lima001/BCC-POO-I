#include "vetor.h"
#include "circunferencia.h"
#include "aceleracao.h"

#ifndef OBJETO_H
#define OBJETO_H

/*!
    \file objeto.h
    \class Objeto
    \author Gabriel Eduardo Lima
    \date Última Modificação: 27/02/2002
    \brief Classe para Representação de um Obejto com forma
           de Circunferência capaz de movimentar-se
*/

class Objeto {
    private:
        static int contagem_id;             //!< Contador de id - Atributo da Classe para gerar automáticamente o id de cada Objeto

    public:
        int id;                             //!< Atributo de identificação única de cada Objeto
        float raio_circunferencia;          //!< Raio da circunferencia do Objeto
        float m;                            //!< Massa do Objeto
        Vetor r;                            //!< Vetor posição do Objeto
        Vetor v;                            //!< Vetor velocidade do Objeto
        Aceleracao a;                       //!< Aceleração do Objeto - Conjunto de Funções que definem aceleração nos eixos x e y

        //! Construtor Default
        /*!
            Inicializa o Objeto com todos os valor numéricos nulos, e
            faz uso dos construtores default das outras classes para
            criar os objetos membros em um estado padrão.

            @see Vetor
            @see Aceleracao
        */
        Objeto():
            raio_circunferencia(0),
            m(0),
            r(Vetor()),
            v(Vetor()),
            a(Aceleracao())
        {
            // Atualização do id automáticamente
            id = contagem_id++;
        }

        //! Construtor Base
        /*!
            Cria um Objeto conforme dados passados por parâmetro

            \param raio usado para inicializar o atributo \ref raio_circunferencia
            \param massa usado para inicializar o atributo \ref m
            \param posicao usado para inicializar o atributo \ref r
            \param movimento usado para inicializar o atributo \ref v
            \param aceleracao usado para inicializar o atributo \ref a.
                              Em caso de omissão do parâmetro, o atributo
                              é inicializado com um objeto \ref Aceleracao
                              construido com o método construtor default  
        */
        Objeto(float raio, float massa, const Vetor &posicao, const Vetor &movimento, const Aceleracao &aceleracao=Aceleracao()):
            m(massa),
            raio_circunferencia(raio),
            r(posicao),
            v(movimento),
            a(aceleracao)
        {
            // Atualização do id automáticamente
            id = contagem_id++;
        }

        //! Construtor de Cópia
        /*!
            Cria um novo objeto copiando as componentes de um Objeto informado.

            Observação: O \ref id não é copiado, uma vez que deve ser único para
            cada \ref Objeto do sistema.

            \param obj Referência constante para o \ref Objeto que será copiado
        */
        Objeto(const Objeto &obj):
            raio_circunferencia(obj.raio_circunferencia),
            m(obj.m),
            r(obj.r),
            v(obj.v),
            a(obj.a)
        {
            // Atualização do id automáticamente
            id = contagem_id++;
        }
        
        //! Construtor Move
        /*!
            Cria um novo objeto fazendo uso do recurso de movimentação. 
            Transfere de maneira eficiente os dados de um Objeto 
            para o novo objeto criado. A título de especificação,
            a operação de movimentação é chamada ao longo do processo
            para a atribuição Move dos atributos do tipo \ref Vetor.

            \param obj Referência rvalue de um \ref Objeto

            Para mais detalhe sobre o recurso, consultar documentação da linguagem
        */
        Objeto(Objeto &&obj) noexcept{
            // Atualização do id automáticamente
            id = contagem_id++;
            
            raio_circunferencia = obj.raio_circunferencia;
            m = obj.m;
            
            // Uso da atribuição Move implementada no Vetor para Otimização
            r = std::move(obj.r);
            v = std::move(obj.v); 
            a = std::move(obj.a);
        }
        
        //! Retorna a Circunferência do Objeto
        /*!
            A partir dos atributos \ref raio_circunferencia e \ref r
            é possível descrever um circunferência que representa a 
            forma geométrica do \ref Objeto .

            Esse método nada mais faz do que retorar um objeto \ref
            Circunferencia dessa representação.

            Importante principalmente para a renderização de um \ref Objeto 
            na tela.

            @see Renderizador
        */
        Circunferencia getCircunferencia(){
            return Circunferencia(raio_circunferencia, r.vetorToPonto());
        }
        
        //! Movimenta o Objeto alterando possivelmente sua velocidade e posição
        /*!
            Esse método deve ser usado quando deseja-se calcular o movimento
            realizado pelo Objeto em um determinado intervalo de tempo.

            Os cálculos são realizados através da Implementação de um Integrador de Euler,
            onde de maneira resumida pode-se calcular a velocidade através da integração
            da aceleração em um intervalo de tempo, bem como calcular a posição do Objeto
            usando-se da integração da velocidade do objeto

            \param ti tempo incial do Intervalo
            \param tf tempo final do Intervalo
            \param dt delta tempo -> diferença tf-ti

            Para mais detalhes acessar: @see https://en.wikipedia.org/wiki/Euler_method
        */
        void movimentar(double ti, double tf, double dt){
            // Uso do Integrador de Euler

            // Definição da quantidade de passos, bem como o incremento em cada passo
            int n_passos = 10000;
            double h =  (1.f/n_passos) / (1.f/dt);
            
            // Armazenamento dos dados da posição e velocidade inciais em cada eixo
            double r0_x = r.x;
            double r0_y = r.y;
            double v0_x = v.x;
            double v0_y = v.y;

            // Integração da Velocidade e da Posição
            for (ti; ti<tf; ti+=h){
                v0_x = v0_x + h*(a.func_x(ti));
                v0_y = v0_y + h*(a.func_y(ti));

                r0_x = r0_x + h*(v0_x);
                r0_y = r0_y + h*(v0_y);
            }

            // Atualização da Velocidade com o valor calculado por Integração
            v.x = v0_x;
            v.y = v0_y;

            // Atualização da Posição com o valor calculado por Integração
            r.x = r0_x;
            r.y = r0_y;
        }


        // Métodos de sobrecarga de operadores!


        //! Sobrecarga do Insertion Operator para Saída de Dados
        /*!
            \return uma string no formato: "Objeto(raio_circunferencia,massa,r,v,a)"
                    onde cada elemento refere-se ao valor dos respectivos atributos
                    do objeto
        */
        friend std::ostream& operator<< (std::ostream& out, Objeto &objeto){
            out << "Objeto("
                << objeto.raio_circunferencia << ";"
                << objeto.m << ";"
                << objeto.r << ";"
                << objeto.v << ";"
                << objeto.a << ")";

            return out; 
        }

        //! Atribuição por Cópia
        /*!
            Copia todos os atributos de um \ref Objeto passado como
            parâmetro para o \ref Objeto atual. Observe que a partir
            desse momento, o \ref Objeto atual torna-se "praticamente"
            o mesmo \ref Objeto copiado, tendo o mesmo id. Por essa 
            razão não recomenda-se realizar a Atribuição por cópia
            e manter os dois Objetos na Simulação, uma vez que implicações
            no que tange a aplicação de colisão a partir do id pode gerar
            resultados inesperados.

            Caso seja necessária uma "cópia" mais superficial onde somente
            os atributos gerais como raio, massa e atributos numéricos sejam
            copiados para o Objeto, recomenda-se o uso da Atribuição por Movimentação,
            implementada já nessa classe.

            \param obj Referência constante do \ref Objeto que será Copiado
            \return Referência para o \ref Objeto que invocou o operador
        */
        Objeto& operator= (Objeto &obj){
            id = obj.id;
            raio_circunferencia = obj.raio_circunferencia;
            m = obj.m;
            
            // Uso da atribuição por movimentação implementada na classe Ponto
            r = std::move(obj.r);
            v = std::move(obj.v);
            a = std::move(obj.a);

            return *this;
        }
        
        ///! Atribuição Move
        /*!
            Movimenta todos os atributos de um \ref Objeto passado como
            parâmetro para o \ref Objeto atual. Nesse caso cada objeto
            terá o seu \ref id único mantido e apenas os atibutos mais
            gerais são copiados.

            \param obj Referência constante do \ref Objeto que será Copiado
            \return Referência para o \ref Objeto que invocou o operador
        */
        Objeto& operator= (Objeto &&obj) noexcept {
            /*
                Verifica se o parâmetro referencia o próprio objeto.
                Em caso de verdade, retorno a referência para o objeto
                atual. Em caso de falsidade, significa que a referência
                é para outro objeto e a movimentação dos atributos ocorre.
            */
            if (&obj == this){
			    return *this;
            }
            
            raio_circunferencia = obj.raio_circunferencia;
            m = obj.m;
            
            // Uso da atribuição por movimentação implementada na classe Ponto
            r = std::move(obj.r);
            v = std::move(obj.v);
            a = std::move(obj.a);

            return *this;
        }

};

// Inicializar a contagem a partir de 0
int Objeto::contagem_id = 0;

#endif