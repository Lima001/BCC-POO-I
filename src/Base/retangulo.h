#include <iostream>
#include "ponto.h"

#ifndef RETANGULO_H
#define RETANGULO_H

class Retangulo {
    public:
        Ponto inicio;
        float largura;
        float altura;
        
        // Construtor Default
        Retangulo():
            inicio(Ponto()), largura(0), altura(0){
        }

        // Construtor base
        Retangulo(const Ponto &inicio, float largura, float altura):
            inicio(inicio), largura(largura), altura(altura){
        }

        // Construtor de Cópia
        Retangulo(const Retangulo &rect):
            inicio(rect.inicio), largura(rect.largura), altura(rect.altura){
        }

        // Construtor Move
        Retangulo(Retangulo &&rect) noexcept{
            inicio = std::move(rect.inicio);
            largura = rect.largura;
            altura = rect.altura;
        }

        /*
            Métodos de sobrecarga de operadores!
        */
        friend std::ostream& operator<< (std::ostream &out, const Retangulo &rect){
            out << rect.inicio << "\n" << "[" << rect.largura << " X " << rect.altura << "]";
            return out;
        }

        // Atribuição por Cópia
        Retangulo& operator= (const Retangulo &rect){
            inicio = std::move(rect.inicio);
            largura = rect.largura;
            altura = rect.altura;

            return *this;
        }

        // Atribuição Move
        Retangulo& operator= (Retangulo &&rect) noexcept {
            if (&rect == this){
			    return *this;
            }

            inicio = std::move(rect.inicio);
            largura = rect.largura;
            altura = rect.altura;

            return *this;
        }
};

#endif