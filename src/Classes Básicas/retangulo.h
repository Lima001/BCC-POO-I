#include <iostream>
#include "ponto.h"

#ifndef RETANGULO_H
#define RETANGULO_H

class Retangulo {
    protected:
        
        Ponto inicio;
        float largura;
        float altura;

    public:
        
        Retangulo(): inicio(Ponto()), largura(0), altura(0){}

        Retangulo(const Retangulo &rect):
            inicio(rect.inicio),
            largura(rect.largura),
            altura(rect.altura){
        }

        Retangulo(Ponto inicio, float largura, float altura):
            inicio(inicio),
            largura(largura),
            altura(altura){
        }

        Ponto getInicio(){
            return inicio;
        }

        float getLargura(){
            return largura;
        }

        float getAltura(){
            return altura;
        }

        friend std::ostream& operator<< (std::ostream &out, const Retangulo &rect){
            out << rect.inicio << "\n" << "[" << rect.largura << " X " << rect.altura << "]";
            return out;
        }
};

#endif