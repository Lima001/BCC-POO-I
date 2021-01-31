#ifndef DETECTOR_COLISAO_H
#define DETECTOR_COLISAO_H

#include <iostream>
#include <vector>
#include <utility>
#include <math.h>
#include "objeto.h"
#include "../Interface/renderizador.h"

using namespace std; 

class DetectorColisao {
    protected:
        int qtd_objetos;
        Objeto* ptr_lista_objetos;

    public:
        float escala;

        DetectorColisao(int qtd_objetos, Objeto* lista_objetos):
            qtd_objetos(qtd_objetos),
            ptr_lista_objetos(lista_objetos)
        {
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

        void verificar_colisao_borda(Renderizador &render, int largura, int altura){
            for (int i=0; i<qtd_objetos; i++){
                if (render.CircunferenciaisOutRender(ptr_lista_objetos[i],largura,altura)){
                    ptr_lista_objetos[i].v = ptr_lista_objetos[i].v * -1;
                }
            }
        }
};

#endif