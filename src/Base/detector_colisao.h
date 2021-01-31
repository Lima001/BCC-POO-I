#ifndef DETECTOR_COLISAO_H
#define DETECTOR_COLISAO_H

#include <iostream>
#include <vector>
#include <utility>
#include <math.h>
#include "linha.h"
#include "objeto.h"

/*
    Observação!

    Os trechos de códigos comentados são referentes a testes realizados!
    Esses testes tratavam da colisão entre um objeto e uma linha, onde
    estava sendo analisado a possibilidade de usar o cálculo da distância
    entre ponto e reta. Esses códigos provavelmente não estarão na versão fina,
    porém serão adicionados a "extra" evidenciando as diferentes abordagens
    aplicadas ao trabalho.
*/

using namespace std; 

class DetectorColisao {
    protected:
        int qtd_objetos;
        Objeto* ptr_lista_objetos = nullptr;

        int qtd_linhas;
        Linha* ptr_lista_linhas = nullptr;

    public:

        DetectorColisao(int qtd_objetos, Objeto* lista_objetos):
            qtd_objetos(qtd_objetos), ptr_lista_objetos(lista_objetos){
        }

        ~DetectorColisao()
        {
        }

        void exibirObjetos(){
            for (int i=0; i<qtd_objetos; i++){
                cout << *(ptr_lista_objetos+i) << endl;
            }
        }

        vector<pair<Objeto*,Objeto*>> detectar(){
            vector<pair<Objeto*,Objeto*>> v;
            Objeto ob1, ob2;

            for (int i=0; i<(qtd_objetos-1); i++){
                for (int j=i+1; j<qtd_objetos; j++){
                    ob1 = *(ptr_lista_objetos+i);
                    ob2 = *(ptr_lista_objetos+j);

                    float distancia = pow((pow((ob1.r.x - ob2.r.x), 2) + pow((ob1.r.y - ob2.r.y), 2)),(1/2.f));

                    if (distancia <= (ob1.raio_circunferencia + ob2.raio_circunferencia)){
                        v.push_back(pair<Objeto*,Objeto*>(ptr_lista_objetos+i, ptr_lista_objetos+j));
                    }
                }
            }
            return v;
        }

        void aplicar_colisao_simples(){
            vector<pair<Objeto*,Objeto*>> colisoes = detectar();

            for(int i=0; i<colisoes.size(); i++){
                colisoes[i].first->v = colisoes[i].first->v *-1; 
                colisoes[i].second->v = colisoes[i].second->v *-1;
            }
        }

        // // Colisão com Conservação do Momento Bidimensional!
        void aplicar_colisao_teste(){
            vector<pair<Objeto*,Objeto*>> colisoes = detectar();
            
            Vetor v1, v2, r1, r2;
            float m1, m2;

            for(int i=0; i<colisoes.size(); i++){
                v1 = move(colisoes[i].first->v);
                r1 = move(colisoes[i].first->r);
                m1 = colisoes[i].first->m;

                v2 = move(colisoes[i].second->v);
                r2 = move(colisoes[i].second->r);
                m2 = colisoes[i].second->m;

                Vetor v1_ = v1 - ((2*m2)/(m1+m2)) * (((v1-v2)*(r1-r2)) * (1/pow((r1-r2).getModulo(),2))) * (r1-r2);
                Vetor v2_ = v2 - ((2*m1)/(m1+m2)) * (((v2-v1)*(r2-r1)) * (1/pow((r2-r1).getModulo(),2))) * (r2-r1);

                colisoes[i].first->v = move(v1_);
                colisoes[i].second->v = move(v2_);
            }
        }

        // Método em testes - Ainda não está completamente funcional!
        void colisao_borda(){
            Linha l;
            Objeto ob;
            Vetor v;
            Vetor r;

            for (int i=0; i<qtd_objetos; i++){
                ob = move(*(ptr_lista_objetos+i));
                v = move((ptr_lista_objetos+i)->v);
                r = move((ptr_lista_objetos+i)->r);
                
                
                for (int j=0; j<qtd_linhas; j++){
                    l = move(*(ptr_lista_linhas+j));
                    bool colidiu = false;
                    /*    
                    if (j==0){
                        if (r.y + ob.raio_circunferencia >= l.p1.y){
                            colidiu = true;
                        }
                    }
                    else if (j==1){
                        if (r.y - ob.raio_circunferencia <= l.p1.y){
                            colidiu = true;
                        }
                    }
                    else if(j==2){
                        if (r.x - ob.raio_circunferencia <= l.p1.x){
                            colidiu = true;
                        }
                    }
                    else{
                        if (r.x + ob.raio_circunferencia >= l.p1.x){
                            colidiu = true;
                        }
                    }

                    if (colidiu){
                        (ptr_lista_objetos+i)->v = v - 2*(v*l.normal)*l.normal;
                        break;
                    }
                    */
                    
                    float d = abs(l.a*r.x + l.b*r.y + l.c)/sqrt(l.a*l.a + l.b*l.b);
                    
                    // Em testes
                    if (d <= ob.raio_circunferencia){
                        (ptr_lista_objetos+i)->v = v - 2*(v*l.normal)*l.normal;
                    }
                }
            }
        }

        void setInfoLinhas(int qtd, Linha* lista_linhas){
            qtd_linhas = qtd;
            ptr_lista_linhas = lista_linhas;
        }
};

#endif