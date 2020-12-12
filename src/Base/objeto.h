#include "vetor.h"
#include "circunferencia.h"

#ifndef OBJETO_H
#define OBJETO_H

class Objeto {
    public:
        float raio_circunferencia;
        Vetor posicao;
        Vetor movimento;

        Objeto():
            raio_circunferencia(0),
            posicao(Vetor()),
            movimento(Vetor())
        {
            
        }

        // Construtor Base
        Objeto(float raio, const Vetor posicao, const Vetor movimento):
            raio_circunferencia(raio),
            posicao(posicao),
            movimento(movimento){
        }

        // Construtor de Cópia
        Objeto(const Objeto &obj):
            raio_circunferencia(obj.raio_circunferencia),
            posicao(obj.posicao),
            movimento(obj.movimento)
        {
        }
        
        // Construtor Move
        Objeto(Objeto &&obj) noexcept{
            raio_circunferencia = obj.raio_circunferencia;
            posicao = std::move(obj.posicao);
            movimento = std::move(obj.movimento);
        }
        
        Circunferencia getCircunferencia(){
            return Circunferencia(raio_circunferencia, posicao.vetorToPonto());
        }
        
        void movimentar(float escala=1){
            posicao = posicao + movimento * escala;
        }

        /*
            Métodos de sobrecarga de operadores!
        */
        friend std::ostream& operator<< (std::ostream &out, Objeto &objeto){
            out << objeto.posicao.vetorToPonto();
            return out;
        }

        // Atribuição Move
        Objeto& operator= (Objeto &&obj) noexcept {
            if (&obj == this){
			    return *this;
            }

            raio_circunferencia = obj.raio_circunferencia;
            posicao = std::move(obj.posicao);
            movimento = std::move(obj.movimento);

            return *this;
        }

};

#endif