#ifndef DETECTOR_COLISAO_H
#define DETECTOR_COLISAO_H

#include <iostream>
#include <vector>
#include <utility>
#include <math.h>
#include "linha.h"
#include "objeto.h"

/*!
    \file detector_colisao.h
    \class DetectorColisao
    \author Gabriel Eduardo Lima
    \date Última Modificação: 27/02/2002
    \brief Classe para Cálculo e Aplicação de Colisão entre objetos do tipo \ref Objeto
           e entre um \ref Objeto e uma \ref Linha
*/

using namespace std; 

class DetectorColisao {
    protected:
        int qtd_objetos;                        //!< Atributo de controle da quantidade de Objetos considerados no cálculo de colisão
        Objeto* ptr_lista_objetos = nullptr;    //!< Ponteiro para um Array de Objetos que podem sofrer a Colisão
        int qtd_linhas = 4;                     //!< Atributo de controle da quantidade de linhas considerados no cálculo de colisão
        Linha* ptr_lista_linhas = nullptr;      //!< Ponteiro para um Array de Linhas que aplicam a Colisão aos Objetos. A quantidade de objetos deve seguir o atributo qtd_linhas

    public:

        //! Construtor Default
        /*!
            Inicializa todos os atributos relacionados a colisão entre
            objetos do tipo \ref Objeto através dos valores informados por
            parâmetro. No que tange a inicialização de atributos relacionados
            a colisão entre \ref Objeto e \ref Linha, olhar o método membro
            \ref setInfoLinhas() .

            \param qtd_objetos usado para inicializar o atributo de mesma nomenclatura
            \param lista_objetos usado para inicializar o atributo \ref ptr_lista_objetos
        */
        DetectorColisao(int qtd_objetos, Objeto* lista_objetos):
            qtd_objetos(qtd_objetos), ptr_lista_objetos(lista_objetos){
        }

        //! Destrutor da Classe
        ~DetectorColisao(){}

        //! Exibe todos os objetos do tipo Objeto considerados no DetectorColisao
        /*!
            Itera sobre o ponteiro como um array e chama o método sobrecarregado
            do operador \b << para exibir as informações conforme definido em \ref Objeto .

            @see Objeto 
        */
        void exibirObjetos(){
            for (int i=0; i<qtd_objetos; i++){
                cout << *(ptr_lista_objetos+i) << endl;
            }
        }

        //! Detecta a colisão entre objetos do tipo Objeto
        /*!
            Cálcula se houve colisão entre algum Objeto com outro
            Objeto através da distância entre os centros e análise
            desse valor com o raio dos \ref Objeto. 
            
            Essa abordagem pode ser escrita da seguinte forma: Considera os pontos
            \f$ inicio(x1,y1) \f$ e \f$ P2(x2,y2) \f$ como sendo o centro
            dos respectivos Objeto Ob1 e Objeto Ob2, e considere \f$ r1 \f$
            e \f$ r2 \f$ sendo seus respectivos raios. A distãncia entre os
            centros \f$ d\f$ é dada por: 

            \f$ d = sqrt{(x2-x1)^2 + (y2-y1)^2} \f$, onde através da analise abaixo
            é possível concluir se houve ou não colisão.

            \li \f$ d > r1 +r2 \Rightarrow\f$ Não houve colisão
            \li \f$ d = r1 +r2 \Rightarrow\f$ Houve colisão em um Ponto
            \li \f$ d < r1 +r2 \Rightarrow\f$ Houve Colisão em mais de um Ponto

            \return A partir desse método é possível obter um vetor contendo um dupla de
                    Referências para Objeto que representam objetos que colidiram um com o outro. 
                    Esse dado pode ser usado para aplicação de regras após a colisão de objetos
        */
        vector<pair<Objeto*,Objeto*>> detectar(){
            // Criação do vetor que será retornado contendo os Objetos que colidiram
            vector<pair<Objeto*,Objeto*>> v;
            //Variáveis auxiliares
            Objeto ob1, ob2;

            // Percorrer o array de Objeto pegando um a um para analisar com os demais Objeto
            // a fim de verificar colisão
            for (int i=0; i<(qtd_objetos-1); i++){
                for (int j=i+1; j<qtd_objetos; j++){
                    ob1 = *(ptr_lista_objetos+i);
                    ob2 = *(ptr_lista_objetos+j);

                    // Cálculo da distância
                    float distancia = pow((pow((ob1.r.x - ob2.r.x), 2) + pow((ob1.r.y - ob2.r.y), 2)),(1/2.f));

                    // Caso houve colisão, adicionar referências para os Objeto no vetor de retorno
                    if (distancia <= (ob1.raio_circunferencia + ob2.raio_circunferencia)){
                        v.push_back(pair<Objeto*,Objeto*>(ptr_lista_objetos+i, ptr_lista_objetos+j));
                    }
                }
            }
            return v;
        }

        //! Aplicar Regra de Colisão Simples
        /*!
            Esse método aplica uma regra de colisão básica
            e não condizente com os casos da realidade. Deve
            ser usada com muito cuidado e em contextos específico.s

            Através desse método, após a detecção dos objetos do
            tipo \ref Objeto através do método \ref detectar() aplica-se
            a seguinte regra: Todo \ref Objeto que colidiu terá o sentido de
            sua velocidade invertida em ambos os eixos.
        */
        void aplicar_colisao_simples(){
            vector<pair<Objeto*,Objeto*>> colisoes = detectar();

            for(int i=0; i<colisoes.size(); i++){
                colisoes[i].first->v = colisoes[i].first->v *-1; 
                colisoes[i].second->v = colisoes[i].second->v *-1;
            }
        }

        //! Aplicar Colisão com Conservação do Momento Bidimensional
        /*!
            Esse método aplica uma regra de colisão mais complexa
            que simula a realidade de um sistema elástico.

            Através desse método, após a detecção dos objetos do
            tipo \ref Objeto através do método \ref detectar() aplica-se
            a regra da colisão elástica Bidimensional. 
            
            Para mais detalhes @see https://en.wikipedia.org/wiki/Elastic_collision
        */
        void aplicar_colisao_cm(){
            // Detecção das Colisões
            vector<pair<Objeto*,Objeto*>> colisoes = detectar();
            
            // Declaração de Variáveis Auxiliares
            Vetor v1, v2, r1, r2;
            float m1, m2;

            // Iteração sobre o vetor para acessar as duplas de Objetos que colidiram entre si
            for(int i=0; i<colisoes.size(); i++){
                // Dados do primeiro Objeto da dupla de Colisão
                v1 = move(colisoes[i].first->v);
                r1 = move(colisoes[i].first->r);
                m1 = colisoes[i].first->m;

                // Dados do segundo Objeto da dupla de Colisão
                v2 = move(colisoes[i].second->v);
                r2 = move(colisoes[i].second->r);
                m2 = colisoes[i].second->m;

                // Cálculo do novo vetor Velocidade através do cálculo vetorial de colisão bidimensional 
                // entre dois Objetos
                Vetor v1_ = v1 - ((2*m2)/(m1+m2)) * (((v1-v2)*(r1-r2)) * (1/pow((r1-r2).getModulo(),2))) * (r1-r2);
                Vetor v2_ = v2 - ((2*m1)/(m1+m2)) * (((v2-v1)*(r2-r1)) * (1/pow((r2-r1).getModulo(),2))) * (r2-r1);

                // Alteração das velocidades dos Objeto pelo novo valor calculador
                colisoes[i].first->v = move(v1_);
                colisoes[i].second->v = move(v2_);
            }
        }

        //! Detectar e Aplicar Colisão com as Bordas da Janela
        /*!
            Esse método detecta quando um \ref Objeto colide com uma \ref Linha,
            e aplica a regra de reflexão especular. Uma linha por sua vez pode ser usada como
            indicador das extremidas da Janela Gráfica e por isso pode-se calcular a colisão com as Bordas.

            Observação: Devido ao fato da movimentação de um objeto poder fazer com que
            esse transponha os limites definidos pelas linhas, antes de aplicar a reflexão
            especular ocorre um reposicionamento do \ref Objeto na posição exata da colisão em um ponto
            com a \ref Linha .

            A título de especificação, o cálculo de reposicionamento pode ser analisado da
            seguinte forma, considerando os seguintes elementos:

            \li \f$ \vec{r}\f$: vetor posição do Objeto
            \li \f$ \vec{v}\f$: vetor velocidade do Objeto
            \li \f$ \vec{n}\f$: vetor normal a linha com a qual o Objeto colidiu e transpassou
            \li \f$ \alpha\f$: ângulo entre \f$\vec{v}\f$ e \f$\vec{n}\f$
            \li \f$ d\f$: Distância entre o ponto mais externo da Circunferencia em relação a linha que colidiu
            \li \f$ t: \tan{\alpha}\f$
            \li \f$ \vec{c}\f$: Vetor para Reposicionamento

            Para saber quem é a Vetor para Reposicionamento deve-se seguir:

            \li Caso a Circunferencia transpassar a linha horizontal superior \f$ \vec{c} = -(d*t,d)\f$
            \li Caso a Circunferencia transpassar a linha horizontal inferior \f$ \vec{c} = (d*t,d)\f$
            \li Caso a Circunferencia transpassar a linha vertical esquerda \f$ \vec{c} = (d,d*t)\f$
            \li Caso a Circunferencia transpassar a linha horizontal direita, \f$ \vec{c} = -(d,d*t)\f$


            O reposicionamento ocorre simplesmente atraveś de:
            \f$ \vec{r} =  \vec{r} - \vec{c}\f$

            Para mais detalhes @see https://en.wikipedia.org/wiki/Specular_reflection
        */
        void aplicar_colisao_borda(){
            // Declaração de Variáveis Auxiliares
            Linha l;
            Objeto ob;
            Vetor v, r, normal;
            float raio;

            // Iteração sobre os Objeto
            for (int i=0; i<qtd_objetos; i++){
                // Dados do Objeto sendo considerado atualmente. Uso da atribuição por movimentação implementada na classe Ponto
                ob = move(*(ptr_lista_objetos+i));
                v = move((ptr_lista_objetos+i)->v);
                r = move((ptr_lista_objetos+i)->r);
                
                raio = (ptr_lista_objetos+i)->raio_circunferencia;
                
                // Iteração sobre as Linhas que representam as Bordas da Janela
                for (int j=0; j<qtd_linhas; j++){
                    // Variáveis Auxiliares
                    l = move(*(ptr_lista_linhas+j));                // objeto Linha considerado para o Cálculo
                    normal = move((ptr_lista_linhas+j)->normal);    // Vetor normal a Linha
                    
                    bool colidiu = false;               // Flag de colisão
                    
                    // Distância entre o Ponto mais Externo da Circunferencia em relação a Linha
                    float d;

                    /* 
                        Verificação se o Objeto colidiu com a Linha para cálculo da distância d,
                        e aplicação futura do efeito de reflexão especular
                    */    
                    if (j==0){
                        if (r.y + ob.raio_circunferencia >= l.inicio.y){
                            colidiu = true;
                            d = r.y + raio - l.inicio.y;
                        }
                    }
                    else if (j==1){
                        if (r.y - ob.raio_circunferencia <= l.inicio.y){
                            colidiu = true;
                            d = abs(r.y - raio - l.inicio.y);
                        }
                    }
                    else if(j==2){
                        if (r.x - ob.raio_circunferencia <= l.inicio.x){
                            colidiu = true;
                            d = abs(r.x - raio - l.inicio.x);
                        }
                    }
                    else{
                        if (r.x + ob.raio_circunferencia >= l.inicio.x){
                            colidiu = true;
                            d = r.x + raio - l.inicio.x;
                        }
                    }

                    // Verificação de existência colisão
                    if (colidiu){
                        
                        // Cálculo do ângulo formado entre o Vetor normal da Linha e o Vetor Velocidade do Objeto
                        float angulo = acos(1.f * (v * normal) / (v.getModulo() * normal.getModulo()));

                        // Cálculo do Vetor Reposicionamento, conforme descrito anteriormente
                        Vetor reposicionamento;
                        if (j == 0 || j == 1)
                            reposicionamento = Vetor(d*tan(angulo), d);
                        else
                            reposicionamento = Vetor(d, d*tan(angulo));

                        // Soma/Subtração do Vetor reposicionamento ao Vetor posição do Objeto
                        if (j == 0 || j == 3)
                            (ptr_lista_objetos+i)->r = (ptr_lista_objetos+i)->r - reposicionamento;
                        else
                            (ptr_lista_objetos+i)->r = (ptr_lista_objetos+i)->r + reposicionamento;

                        // Aplicação da reflexão especular através de cálculo vetorial
                        (ptr_lista_objetos+i)->v = v - 2*(v*l.normal)*l.normal;
                    }
                }
            }
        }

        //! Configura os atributos relacionados aos objetos do tipo \ref Linha
        /*!
            Esse método deve ser usado para configurar as \ref Linha que apliacrão
            colisão com os \ref Objeto .

            \param qtd utilziado para configurar o atributo \ref qtd_linhas
            \param lista_linhas utilziado para configurar o atributo \ref ptr_lista_linhas
        */
        void setInfoLinhas(Linha* lista_linhas){
            ptr_lista_linhas = lista_linhas;
        }
};

#endif