#include <iostream>
#include <SDL.h>

#ifndef CONTROLADOR_SDL_H
#define CONTROLADOR_SDL_H

/*!
    \class Controlador_SDL
    \author Gabriel Eduardo Lima
    \date 1/1/1
    Classe Responsável pela Inicialização e Possibilitar a Operação da biblioteca SDL
*/

class Controlador_SDL {
    protected:
        bool inicializado; //!< Indicador de inicialização. Um valor True -> SDL Inicializado

    public:
        //! Construtor Default
        /*!
            Não é necessário a passagem de parâmetros!
        */
        Controlador_SDL(){};
        
        //! Destrutor da Classe
        ~Controlador_SDL(){}

        /*! Método utilizado para inicializar a biblioteca SDL e 
            permitir o uso de suas funcionalidades.

            Faz uso da Função SDL_Init() com a flag SDL_INIT_EVERYTHING
            para iniciar todos os modulos SDL. Os erros são capturados
            a partir do uso da função SDL_GetError().

            Caso ocorra algum erro durante o processo de inicialização, 
            uma mensagem é exibida no console informando o acontecido, bem
            como o erro retornado pelo SDL. Nesse caso, o atributo \ref inicializado
            receberá o valor booleano false.

            Caso o processo de inicialização seja bem sucedido, uma mensagem é exibida
            no console informando o usuário. Nesse caso, o atributo \ref inicializado
            receberá o valor booleano true.
        */
        void inicializar(){
            if (SDL_Init(SDL_INIT_EVERYTHING) < 0){
                std::cout << "Erro ao Iniciar SDL - " << SDL_GetError() << std::endl;
                inicializado = false;
            }
            else{
                std::cout << "SDL Inicializado...\n";
                inicializado = true;
            }   
        }

        /*! Método utilizado para pausar a execução do programa em uma
            determinada quantidade de tempo.

            Ao ser invocado, o método pausa a execução fazendo o uso
            da função SDL_Delay(), e exibe uma mensagem no console 
            informando o estado atual de pausa.

            \param milissegundos um inteiro informando o tempo em milissegundos
                                 em que a execução ficará pausada. 
        */
        void pausar(int milissegundos){
            std::cout << "SDL Pausado...\n";
            SDL_Delay(milissegundos);
        }

        /*! Método utilizado para finalizar a biblioteca SDL. Deve ser usado
            ao final do programa para garantir que todos os elementos sejam
            finalizados sem problemas.

            Ao ser invocado, o método chama a função de saída da bilbioteca
            SDL - SDL_Quit(), e exibe uma mensagem no console informando o
            ato de finalização.
        */
        void finalizar(){
            std::cout << "SDL Finalizado...\n";
            inicializado = false;
            SDL_Quit();
        }

        /*! Método utilizado para saber o status do controlador SDL.

            \return um boolenano referente ao atributo \ref inicializado
        */
        bool getInicializado(){
            return inicializado;
        }
};

#endif