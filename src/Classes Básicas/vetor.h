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
    protected:
    
        float x;
        float y;

    public:

        // Construtor default
        Vetor(): x(0), y(0){}

        Vetor(float x_, float y_):
            x(x_),
            y(y_){
        }

        Vetor(Ponto inicio, Ponto fim): 
            x(fim.x - inicio.x),
            y(fim.y - inicio.y){
        }

        // Construtor de Cópia
        Vetor(const Vetor &v): x(v.x), y(v.y){}

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

        friend Vetor operator*(const int escalar, const Vetor &vetor){
		    return Vetor(vetor.x * escalar, vetor.y * escalar);
	    }

        friend Vetor operator*(const Vetor &vetor, const float escalar){
		    return Vetor(vetor.x * escalar, vetor.y * escalar);
	    }

        // Produto escalar entre dois vetores
        int operator*(const Vetor vetor){
		    return ((x * vetor.x) + (y * vetor.y));
	    }

        //Adicionar produto vetorial!

        // Função para calcular e retornar o módulo do vetor
        float getModulo(){
            return pow((x*x + y*y),(1.0/2));
        }
};

#endif