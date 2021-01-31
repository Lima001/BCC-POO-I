#include "ponto.h"

#ifndef TRIANGULO_H
#define TRIANGULO_H

class Triangulo {
    public:
        Ponto p1;
        Ponto p2;
        Ponto p3;
        
        // Construtor Default
        Triangulo():
            p1(Ponto()),
            p2(Ponto()),
            p3(Ponto())
        {
        }

        // Construtor Base
        Triangulo(const Ponto &p1, const Ponto &p2, const Ponto &p3):
            p1(p1),
            p2(p2),
            p3(p3)
        {
        }

        // Construtor de Cópia
        Triangulo(const Triangulo &t):
            p1(t.p1),
            p2(t.p2),
            p3(t.p3)
        {    
        }

        // Construtor Move
        Triangulo(Triangulo &&t) noexcept{
            p1 = std::move(t.p1);
            p2 = std::move(t.p2);
            p3 = std::move(t.p3);
        }

        /*
            Métodos de sobrecarga de operadores!
        */
        friend std::ostream& operator<< (std::ostream &out, const Triangulo &t){
            out << t.p1 << "; " << t.p2<< "; " << t.p3;
            return out;
        }

        // Atribuição por Cópia
        Triangulo& operator= (Triangulo &t){
            p1 = std::move(t.p1);
            p2 = std::move(t.p2);
            p3 = std::move(t.p3);

            return *this;
        }

        // Atribuição Move
        Triangulo& operator= (Triangulo &&t) noexcept {
            if (&t == this){
			    return *this;
            }

            p1 = std::move(t.p1);
            p2 = std::move(t.p2);
            p3 = std::move(t.p3);

            return *this;
        }
};

#endif