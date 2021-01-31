#include <iostream>
#include <math.h>
#include "ponto.h"

#ifndef CIRCUNFERENCIA_H
#define CIRCUNFERENCIA_H

class Circunferencia {
    public:
        int precisao;
        float raio;
        Ponto centro;
        Ponto* demarcacao;

        // Construtor Default
        Circunferencia():
            precisao(1),
            raio(0),
            centro(Ponto())
        {
            demarcacao = new Ponto[precisao];
            gerarDemarcacao();
        }

        // Construtor Base
        Circunferencia(float raio, const Ponto &centro, int precisao=60):
            raio(raio),
            centro(centro),
            precisao(precisao)
        {
            demarcacao = new Ponto[precisao];
            gerarDemarcacao();
        }

        // Destrutor
        ~Circunferencia(){
            // Liberar espaço dinâmicamente alocado
            delete [] demarcacao;
        }

        // Construtor de Cópia
        Circunferencia(const Circunferencia& circ):
            precisao(circ.precisao),
            raio(circ.raio),
            centro(circ.centro)
        {
            demarcacao = new Ponto[precisao];
            gerarDemarcacao();
        }

        // Construtor Move
        Circunferencia(Circunferencia &&circ) noexcept{
            precisao = circ.precisao;
            raio = circ.raio;
            centro = std::move(circ.centro);
            demarcacao = new Ponto[precisao];
            gerarDemarcacao();
        }

        void gerarDemarcacao(){
            Ponto p = Ponto();
            float angulo = (360/precisao)*(M_PI/180.0f);

            {2 0} x 
            {0 2.5} y

            for (int i=0; i<precisao; i++){
                p.x = centro.x + cos(angulo*i) * raio;
                p.y = centro.y + sin(angulo*i) * raio;
                demarcacao[i] = std::move(p);
            }
        }

        /*
            Métodos de sobrecarga de operadores!
        */
        friend std::ostream& operator<< (std::ostream &out, const Circunferencia &circ){
            out << "(x-(" << circ.centro.x << "))**2 " <<
                    "+ (y-(" << circ.centro.y << "))**2 = " << circ.raio << "**2"; 
            return out;
        }

        // Atribuição por Cópia
        Circunferencia& operator= (Circunferencia &circ){
            if (demarcacao != nullptr){
                delete [] demarcacao;
            }

            precisao = circ.precisao;
            raio = circ.raio;
            centro = std::move(circ.centro);
            demarcacao = new Ponto[precisao];
            gerarDemarcacao();

            return *this;
        }

        // Atribuição Move
        Circunferencia& operator= (Circunferencia &&circ) noexcept {
            if (&circ == this){
			    return *this;
            }

            if (demarcacao != nullptr){
                delete [] demarcacao;
            }

            precisao = circ.precisao;
            raio = circ.raio;
            centro = std::move(circ.centro);
            demarcacao = new Ponto[precisao];
            gerarDemarcacao();

            return *this;
        }
};

#endif