#ifndef GERENCIADOR_EVENTO_H
#define GERENCIADOR_EVENTO_H

#include <SDL.h>
#include "evento.h"

/*!
    \file gerenciador_evento.h
    \class GerenciadorEvento
    \author Gabriel Eduardo Lima
    \date Última alteração: 28/02/2021
    \brief Classe Responsável pelo processamento dos
           objetos do tipo \ref Evento
*/

class GerenciadorEvento{
    public:
        Evento evento = Evento(NONE,T_NONE);        //!< Usado para armazenar o objeto Evento que está sendo processado no momento

    protected:
        SDL_Event registro;                         //!< Usado para registrar os eventos gerados pelo SDL para futura intepretação
        
        //! Interpreta o evento gerado pela biblioteca SDL
        /*!
            Uma vez o evento tendo sido armazenado no registro, esse
            pode ser interpretado visando gerar uma forma mais amigável
            de apresentação ao desenvolvedor.

            A intepretação do evento pode ser verificada no atributo \ref evento.
            Observe que cada vez que um evento for interpretado esse atributo será alterado,
            o que implica o acesso somente ao evento específico. Após interpretação de outro
            evento da fila de eventos, não será possível resgatar os eventos anteriores.

            A título de especificação, os eventos serão interpretados da seguinte forma:

            \li SDL_QUIT - Resulta um \ref Evento do TipoEvento QUIT e Trigger T_CLOSE
            \li SDL_KEYDOWN - Resulta um \ref Evento do TipoEvento KEYDOWN e Trigger referente
                a tecla Pressionada e definida em Trigger. Caso a tecla não esteja em definida,
                gera um Trigger T_UNDEFINED
                
            Caso qualquer outro evento seja gerado, tem-se como resultante o Evento
            do TipoEvento UNDEFINED e Trigger T_UNDEFINED.

            Observação: No que tange a reutilização de códigos, o desenvolvedor
            pode facilmente adicionar interpretações necessárias a sua aplicação
            através da modificação desse método e da alteração (se necessária)
            das estruturas TipoEvento e Trigger definidos em \ref Evento conforme
            contexto da aplicação. @see Evento
        */
        void getEvento(){
            if (registro.type == SDL_QUIT){
                evento.tipo_evento = QUIT;
                evento.trigger = T_CLOSE;
            }
            
            else if (registro.type == SDL_KEYDOWN){
                switch(registro.key.keysym.sym){   
                    case SDLK_LEFT:
                        evento.tipo_evento = KEYDOWN;
                        evento.trigger = T_KLEFT;
                        break;
                    
                    case SDLK_DOWN:
                        evento.tipo_evento = KEYDOWN;
                        evento.trigger = T_KDOWN;
                        break;
                    
                    case SDLK_RIGHT:
                        evento.tipo_evento = KEYDOWN;
                        evento.trigger = T_KRIGHT;
                        break;
                    
                    case SDLK_UP:
                        evento.tipo_evento = KEYDOWN;
                        evento.trigger = T_KUP;
                        break;
                    
                    case SDLK_q:
                        evento.tipo_evento = KEYDOWN;
                        evento.trigger = T_KQ;
                        break;

                    case SDLK_p:
                        evento.tipo_evento = KEYDOWN;
                        evento.trigger = T_KP;
                        break;

                    case SDLK_a:
                        evento.tipo_evento = KEYDOWN;
                        evento.trigger = T_KA;
                        break;
                    
                    case SDLK_d:
                        evento.tipo_evento = KEYDOWN;
                        evento.trigger = T_KD;
                        break;

                    case SDLK_w:
                        evento.tipo_evento = KEYDOWN;
                        evento.trigger = T_KW;
                        break;

                    case SDLK_s:
                        evento.tipo_evento = KEYDOWN;
                        evento.trigger = T_KS;
                        break;
                    
                    default:
                        evento.tipo_evento = KEYDOWN;
                        evento.trigger = T_UNDEFINED;
                        break;
                }
            }
            else{
                evento.tipo_evento = UNDEFINED;
                evento.trigger = T_UNDEFINED;
            }
        }

    public:

        //! Construtor Default
        /*!
            Não necessita de passagem de parâmetros.
        */
        GerenciadorEvento(){}

        // Destrutor da Classe
        ~GerenciadorEvento(){}

        //! Registra e Interpreta os eventos captados
        /*!
            Registra os eventos da fila de eventos observada
            pelo SDL e permite que esses sejam intepretados
            e gerem um objeto do tipo \ref Evento através
            do método membro \ref getEvento() que será
            armazenado no atributo \ref evento .

            Caso nenhum evento esteja na fila de eventos,
            o atributo que armazena esses eventos é 
            resetado para o seu estado padrão.

            @see Evento
        */
       void registrarEvento(){
            // Captura de eventos da fila de eventos
            if (SDL_PollEvent(&registro)){
                // Interpretação do evento
                getEvento();
            }
            else{
                evento.tipo_evento = NONE;
                evento.trigger = T_NONE;
            }
        }
};

#endif