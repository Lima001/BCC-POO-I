#include "ponto.h"

#ifndef TRIANGULO_H
#define TRIANGULO_H

class Triangulo {
    protected:
        
        Ponto p1;
        Ponto p2;
        Ponto p3;

    public:
        
        Triangulo():
            p1(Ponto()),
            p2(Ponto()),
            p3(Ponto()){
        }

        Triangulo(Ponto p1, Ponto p2, Ponto p3):
            p1(p1),
            p2(p2),
            p3(p3){
        }

        Triangulo(const Triangulo &t):
            p1(t.p1),
            p2(t.p2),
            p3(t.p3){    
        }

        Ponto getPonto1(){
            return p1;
        }

        Ponto getPonto2(){
            return p2;
        }

        Ponto getPonto3(){
            return p3;
        }

        friend std::ostream& operator<< (std::ostream &out, const Triangulo &t){
            out << t.p1 << "; " << t.p2<< "; " << t.p3;
            return out;
        }

};

#endif