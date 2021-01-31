#ifndef EVENTO_H
#define EVENTO_H

#include <iostream>

enum TipoEvento{
    QUIT,
    KEYDOWN,
    KEYUP,
    UNDEFINED,
    NONE
};

enum Trigger{
    T_NONE,
    T_UNDEFINED,
    T_CLOSE,
    T_KQ,
    T_KP,
    T_KW,
    T_KS,
    T_KA,
    T_KD,
    T_KLEFT,
    T_KDOWN,
    T_KRIGHT,
    T_KUP
};

class Evento{
    public:

        TipoEvento tipo_evento;
        Trigger trigger;

        Evento(TipoEvento te, Trigger tr):
            tipo_evento(tipo_evento),
            trigger(tr)
        {    
        };
        
        ~Evento(){}

        friend std::ostream& operator<< (std::ostream &out, const Evento &evento){
            out << "(" << evento.tipo_evento << ", " << evento.trigger << ")";
            return out;
        };
};

#endif