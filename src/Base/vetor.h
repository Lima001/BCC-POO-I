#include <iostream>
#include <math.h>
#include "ponto.h"

#ifndef VETOR_H
#define VETOR_H

/**
* \class Vetor
* \author Gabriel Eduardo Lima
* \date 11/11/2020
* Classe para Representação de um Vetor no Plano Cartesiano
*/

class Vetor {
    public:
        float x;
        float y;

        // Construtor Default
        Vetor():
            x(0), 
            y(0)
        {
        }

        // Construtor Base a partir de Coordenadas
        Vetor(float x, float y):
            x(x),
            y(y)
        {
        }

        // Construtor a partir de Pontos passados Por Referência Constante
        Vetor(const Ponto &inicio, const Ponto &fim): 
            x(fim.x - inicio.x),
            y(fim.y - inicio.y)
        {
        }

        // Construtor de Cópia
        Vetor(const Vetor &v):
            x(v.x), 
            y(v.y)
        {
        }

        // Construtor Move
        Vetor (Vetor &&vetor) noexcept{
            x = vetor.x;
            y = vetor.y;
        }
        
        float getModulo(){
            return pow((x*x + y*y),(1.0/2));
        }

        float getAngulo(){
            return atan2(y,x);
        }

        Ponto vetorToPonto(){
            return Ponto(x,y);
        }

        /*
            Métodos de sobrecarga de operadores!
        */
        friend std::ostream& operator<< (std::ostream &out, const Vetor &vetor){
            out << vetor.x << "i +" << vetor.y << "j";
            return out;
        };

        Vetor operator+(const Vetor &vetor){
		    return Vetor(x + vetor.x, y + vetor.y);
	    }

        Vetor operator-(const Vetor &vetor){
		    return Vetor(x - vetor.x, y - vetor.y);
	    }

        friend Vetor operator*(const float escalar, const Vetor &vetor){
		    return Vetor(vetor.x * escalar, vetor.y * escalar);
	    }

        friend Vetor operator*(const Vetor &vetor, const float escalar){
		    return Vetor(vetor.x * escalar, vetor.y * escalar);
	    }

        // Produto escalar entre dois vetores
        int operator*(const Vetor vetor){
		    return ((x * vetor.x) + (y * vetor.y));
        }

        // Atribuição Move
        Vetor& operator= (Vetor &&vetor) noexcept {
            if (&vetor == this){
			    return *this;
            }

            x = vetor.x;
            y = vetor.y;

            return *this;
        }
};

#endif