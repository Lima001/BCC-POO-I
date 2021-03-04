#include <iostream>
#include <SDL.h>

#ifndef CONTROLADOR_SDL_H
#define CONTROLADOR_SDL_H

/*!
    \file controlador_SDL.h
    \class Controlador_SDL
    \author Gabriel Eduardo Lima
    \date Última alteração: 28/02/2021
    \brief Classe responsável pela inicialização e possibilitar a operação da biblioteca SDL
*/

class Controlador_SDL {
    protected:
        bool inicializado;          //!< Indicador de inicialização. Um valor True implica em SDL Inicializado

    public:
        //! Construtor Default e Base
        /*!
            Não é necessário a passagem de parâmetros!

            Cria um objeto do tipo \ref Controlador_SDL permitindo
            ao desenvolvedor a inicialização da biblioteca
            e por consequência o uso de todas as outras
            funcionalidades gráficas desenvolvidas usando os recursos
            dessa biblioteca.

            Observação: Recomenda-se que esse seja a primeira
            classe com um objeto para o uso dos recursos gráficos.
            Recomenda-se também que seja criado apenas um objeto desse
            tipo para a aplicação para evitar uso desnecessário de memória.
        */
        Controlador_SDL(){};
        
        //! Destrutor da Classe
        ~Controlador_SDL(){}

        //! Inicializa a biblioteca SDL
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

            Esse método deve ser obrigatoriamente chamado antes da execução dos
            recursos implementados por outras classes gráficas, causando em caso
            contrário erro na execução do programa.
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

        //! Pausa a aplicação SDL
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

        //! Finaliza a biblioteca SDL
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

        //! Retorna se a biblioteca foi ou não inicializada
        /*! Método utilizado para saber o status do controlador SDL.

            \return Boolenano referente ao atributo \ref inicializado
        */
        bool getInicializado(){
            return inicializado;
        }
};

#endif