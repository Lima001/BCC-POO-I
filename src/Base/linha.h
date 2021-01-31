#ifndef LINHA_H
#define LINHA_H

#include "vetor.h"

/*
    Observação!

    Os trechos de códigos comentados são referentes a testes realizados!
    Esses testes tratavam da colisão entre um objeto e uma linha, onde
    estava sendo analisado a possibilidade de usar o cálculo da distância
    entre ponto e reta. Esses códigos provavelmente não estarão na versão fina,
    porém serão adicionados a "extra" evidenciando as diferentes abordagens
    aplicadas ao trabalho.
*/

class Linha {
    public:
        Ponto p1;
        Ponto p2;
        Vetor normal;
        float a;
        float b;
        float c;

        Linha():
            p1(Ponto()), p2(Ponto()), normal(Vetor()){
        }

        Linha(const Ponto &p1, const Ponto &p2):
            p1(p1), p2(p2){
            
            Vetor d = Vetor(p1,p2);
            normal = Vetor(-d.y,d.x);
            normal = normal * (1.f/normal.getModulo());

            a = -(p2.y-p1.y)/(p2.x-p1.x);
            b = 1;
            c = a*p1.x - p1.y;

            if (std::isinf(a)){
                a = 1;
                b = 0;
                c = -p1.x;
            }
        }

        ~Linha(){}

};

#endif