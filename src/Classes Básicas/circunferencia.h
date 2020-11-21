#include <iostream>
#include <math.h>
#include "ponto.h"

#ifndef CIRCUNFERENCIA_H
#define CIRCUNFERENCIA_H

class Circunferencia {
    protected:
        
        int precisao;
        float raio;
        Ponto centro;
        Ponto *demarcacao;

    public:
        
        Circunferencia(float raio, Ponto centro, int precisao=40):
            raio(raio),
            centro(centro),
            precisao(precisao)
        {
            demarcacao = new Ponto[precisao];
            gerarDemarcacao();
        }

        ~Circunferencia(){
            delete [] demarcacao;
        }

        void gerarDemarcacao(){
            Ponto p = Ponto();
            float angulo = (360/precisao)*(M_PI/180.0f);

            for (int i=0; i<precisao; i++){
                p.x = centro.x + cos(angulo*i) * raio;
                p.y = centro.y + sin(angulo*i) * raio;
                demarcacao[i] = p;
            }
        }

        int getPrecisao(){
            return precisao;
        }

        Ponto* getDemarcacao(){
            return demarcacao;
        }
};

#endif