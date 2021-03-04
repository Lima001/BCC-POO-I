#ifndef JANELA_H
#define JANELA_H

#include <SDL.h>
#include <iostream>
#include "cor_rgba.h"

/*!
    \file janela.h
    \class Janela
    \author Gabriel Eduardo Lima
    \date Última alteração: 28/02/2021
    \brief Classe responsável pela criação e controle da Janela gráfica
           e seus elementos associados
*/

class Janela {
    public:
        int largura;                           //!< Largura da janela a ser criada. Não deve ser alterado durante a aplicação
        int altura;                            //!< Altura da janela a ser criada. Não deve ser alterado durante a aplicação
        SDL_Window* ptr_janela = nullptr;      //!< Ponteiro para o objeto SDL_Window. Permite acesso a janela gráfica gerada por essa biblioteca
        SDL_Surface* ptr_surface = nullptr;    //!< Ponteiro para o objeto SDL_Surface. Permite acesso a área de renderização gerada por essa biblioteca

        //! Construtor Default
        /*!
            Usado para criar um objeto janela conforme parâmetros informados.
            Não incializa o ponteiro para SDL_Surface do objeto, sendo que esse deve
            ser inicializados somente através de seu métodos membros implementados,
            nas situações julgadas necessárias.

            Em caso de erros durante o processo de criação da janela gráfica pelo SDL,
            o erro será exibido conforme retorno da função SDL_GetError().

            \param titulo Uma string estilo C. É usado para criar a janela atavés da função SDL_CreateWindow() que solicita um título
            \param largura Inicializa atributo de mesma nomenclatura
            \param altura Inicializa atributo de mesma nomenclatura
        */
        Janela(const char titulo[], int largura, int altura){
            // Criação da Janela
            ptr_janela = SDL_CreateWindow(titulo,
                                          SDL_WINDOWPOS_CENTERED, 
                                          SDL_WINDOWPOS_CENTERED,
                                          largura,
                                          altura,
                                          0);

            // Verificar se a janela gráfica foi criada
            if (ptr_janela == nullptr) {
                std::cout << "Erro ao criar a Janela SDL - " << SDL_GetError() << std::endl;
            }
            else{
                Janela::largura = largura;
                Janela::altura = altura;
            }
        }

        //! Destrutor da Classe
        /*!
            Verifica se alguma janela gráfica foi construída
            a partir do SDL. Em caso de existência de algo
            do tipo, a janela é destruída por esse método.
        */
        ~Janela(){
            if (ptr_janela){
                SDL_DestroyWindow(ptr_janela);
            }
        }

        //! Inicializa a área de renderização gráfica da janela
        /*!
            Esse método é usado para inicializar o ponteiro
            \ref ptr_surface que permite acesso a área de 
            renderização gráfica da janela criada.

            Observação: Deve-se somente chamar esse método
            se a janela gráfica SDL já tiver sido criada, podendo
            resultar erro em caso contrário.
        */
        void iniciarSurface(){
            ptr_surface = SDL_GetWindowSurface(ptr_janela);
        }

        //! Define uma cor de fundo para a Área de renderização gráfica da janela
        /*!
            Método usado quando deseja-se resetar o gráfico da área de renderização
            usando-se da definição de uma cor de fundo padrão.

            \param cor Referência constante para um objeto \ref CorRGBA que será usado
                       para gerar a cor compreendida pelas funções SDL e que representa
                       a cor de fundo desejada pelo desenvolvedor
        */
        void preencherFundo(const CorRGBA &cor){
            SDL_FillRect(ptr_surface, NULL, cor.getCor(ptr_surface));
        }

        //! Atualiza a Área de Renderização
        /*!
            Esse método deve ser usado logo após todas
            as definições de renderização tiverem sido
            concluidas. Caso o método não seja chamado,
            não será possível observar os efeitos gráficos
            produzidos.
        */
        void atualizar(){
            SDL_UpdateWindowSurface(ptr_janela);
        }
};

#endif