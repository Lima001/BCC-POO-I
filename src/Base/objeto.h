#include "vetor.h"
#include "circunferencia.h"
#include "aceleracao.h"

#ifndef OBJETO_H
#define OBJETO_H

class Objeto {
    private:
        static int contagem_id;

    public:
        int id;
        float raio_circunferencia;
        float m;
        Vetor r;
        Vetor v;
        Aceleracao a;

        Objeto():
            raio_circunferencia(0),
            m(0),
            r(Vetor()),
            v(Vetor()),
            a(Aceleracao())
        {
            id = contagem_id++;
        }

        // Construtor Base
        Objeto(float raio, float massa, const Vetor posicao, const Vetor movimento, const Aceleracao aceleracao):
            m(massa),
            raio_circunferencia(raio),
            r(posicao),
            v(movimento),
            a(aceleracao)
        {
            id = contagem_id++;
        }

        // Construtor de Cópia
        Objeto(const Objeto &obj):
            raio_circunferencia(obj.raio_circunferencia),
            m(obj.m),
            r(obj.r),
            v(obj.v),
            a(obj.a)
        {
            id = contagem_id++;
        }
        
        // Construtor Move
        Objeto(Objeto &&obj) noexcept{
            id = contagem_id++;
            raio_circunferencia = obj.raio_circunferencia;
            m = obj.m;
            r = std::move(obj.r);
            v = std::move(obj.v);
            a = std::move(obj.a);
        }
        
        Circunferencia getCircunferencia(){
            return Circunferencia(raio_circunferencia, r.vetorToPonto());
        }
        
        void movimentar(double ti, double tf, double dt){
            // Uso do Integrador de Euler

            int n_passos = 10000;
            double h =  (1.f/n_passos) / (1.f/dt);
            double r0_x = r.x;
            double r0_y = r.y;
            double v0_x = v.x;
            double v0_y = v.y;

            for (ti; ti<tf; ti+=h){
                v0_x = v0_x + h*(a.func_x(ti));
                v0_y = v0_y + h*(a.func_y(ti));

                r0_x = r0_x + h*(v0_x);
                r0_y = r0_y + h*(v0_y);
            }

            v.x = v0_x;
            v.y = v0_y;

            r.x = r0_x;
            r.y = r0_y;
        }

        /*
            Métodos de sobrecarga de operadores!
        */
        friend std::ostream& operator<< (std::ostream &out, Objeto &objeto){
            out << objeto.id << ": " <<
                    objeto.r.vetorToPonto() << "; " << 
                    objeto.v.vetorToPonto();
            
            return out;
        }

        // Atribuição por Cópia
        Objeto& operator= (Objeto &obj){
            id = obj.id;
            raio_circunferencia = obj.raio_circunferencia;
            m = obj.m;
            r = std::move(obj.r);
            v = std::move(obj.v);
            a = std::move(obj.a);

            return *this;
        }
        
        // Atribuição Move
        Objeto& operator= (Objeto &&obj) noexcept {
            if (&obj == this){
			    return *this;
            }
            
            raio_circunferencia = obj.raio_circunferencia;
            m = obj.m;
            r = std::move(obj.r);
            v = std::move(obj.v);
            a = std::move(obj.a);

            return *this;
        }

};

int Objeto::contagem_id = 0;

#endif