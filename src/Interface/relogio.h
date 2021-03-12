#ifndef RELOGIO_H
#define RELOGIO_H

#include "controlador_SDL.h"

/*!
    \file relogio.h
    \class Relogio
    \author Gabriel Eduardo Lima
    \date Última alteração: 28/02/2021
    \brief Classe responsável pelo controle dos FPS da aplicação gráfica
*/

class Relogio{
    protected:
        
        Controlador_SDL control;            //!< Objeto controlador - Permite o uso das funções SDL
        int fps;                            //!< Indica a quantidade de fps desejada pelo desenvolvedor
        Uint32 clock_inicio;                //!< Usado para controle de clock

    public:

        //! Construtor Default
        /*!
            Cria um objeto com os valores passados por parâmetro e inicializa
            o valor \ref clock_inicio como 0 para uso em outros métodos membros.

            Observação: Recomenda-se que seja criado apenas um objeto desse
            tipo para a aplicação, uma vez que não se faz necessário o uso
            de diversos objetos para controle do fps.

            \param control Referência constante para um objeto \ref Controlador_SDL.
                           Inicializa atributo de mesma nomenclatura
            
            \param fps Usado para inicializar parâmetro de mesma nomenclatura.
                       Em caso de omissão desse parâmetro, seu valor será
                       configurado para o mínimo de 60fps esperado para uma boa
                       aplicação gráfica
        */
        Relogio(Controlador_SDL &control, int fps=60): 
            control(control), 
            fps(fps){

            clock_inicio = 0;
        }

        //! Destrutor da Classe
        ~Relogio(){}

        //! Método usado para ajustar o fps da aplicação
        /*!
            Esse método cálcula a quantidade de fps atuais
            da aplicação e verifica se este é menor do que
            a quantidade prevista pela aplicação. Caso seje,
            fica responsável por acrescentar um delay condizente
            com a quantidade faltante de quadros por segundo.

            Observação: a cada execução do método, o valor
            de \ref clock_inicio é atualizado, uma vez que
            esse refere-se ao valor da execução no momento,
            e deve ser usado para comparação com o clock
            da aplicação em sua próxima iteração de loop
            principal.
        */  
        void tick(){
            if ((1000 / fps) > SDL_GetTicks() - clock_inicio){
                SDL_Delay(1000 / fps - (SDL_GetTicks() - clock_inicio));
            }

            clock_inicio = SDL_GetTicks();
        }
};

#endif