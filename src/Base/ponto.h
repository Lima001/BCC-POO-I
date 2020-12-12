#include <iostream>

#ifndef PONTO_H
#define PONTO_H

/**
* \class Ponto
* \author Gabriel Eduardo Lima
* \date 11/11/2020
* Classe para Representação de um Ponto no Plano Cartesiano
*/

class Ponto {
    public:
        float x;
        float y;
    
        // Construtor Default (Inicia o ponto na Origem do Plano Cartesiano)
        Ponto(): 
            x(0), 
            y(0)
        {
        }

        // Construtor Base
        // #Dúvida:
        //      Retirar e deixar apenas Move Constructor?
        Ponto(float x, float y): 
            x(x), 
            y(y)
        {
        }

        // Construtor de Cópia
        Ponto(const Ponto &p):
            x(p.x),
            y(p.y)
        {
        }

        // Construtor Move
        Ponto(Ponto &&p) noexcept{
            x = p.x;
            y = p.y;
        }

        /*
            Métodos de Sobrecarga de Operadores
        */

        friend std::ostream& operator<< (std::ostream &out, const Ponto &ponto){
            /*
            Função amiga para ter acesso ao atributos protegidos da classe,
            visando sobscrita do operador << para apresentação de saída ao
            usuário.
            */
            
            out << "(" << ponto.x << ", " << ponto.y << ")";
            return out;
        }

        // Atribuição Move
        Ponto& operator= (Ponto &&p) noexcept {
            if (&p == this){
			    return *this;
            }

            x = p.x;
            y = p.y;

            return *this;
        }
};

#endif