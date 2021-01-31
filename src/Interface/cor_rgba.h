#ifndef COR_RGBA_H
#define COR_RGBA_H

#include <iostream>
#include <SDL.h>

/*!
    \class CorRGBA
    \author Gabriel Eduardo Lima
    \date 1/1/1
    Classe Responsável por representar cores RGBA para uso em conjunto aos elementos gráficos
    da interface SDL.
*/

class CorRGBA {
    public:
        int r;          //!< Intensidade de vermelho - Min: 0; Max: 255
        int g;          //!< Intensidade de verde - Min: 0; Max: 255
        int b;          //!< Intensidade de azul - Min: 0; Max: 255
        int a;          //!< Canal Alfa - Min: 0; Max: 255

        //! Construtor Default
        /*!
            Chamado quando nenhum parâmetro de ininicialização for informado.
            
            Cria um objeto com todos os atributos configurados para o valor
            de máximo, resultando na cor branca padrão.
        */
        CorRGBA():
            r(255),
            g(255),
            b(255),
            a(255){
        }

        //! Construtor Base
        /*!
            Cria um objeto com os valores passados por parâmetro
            \param r um inteiro para configurar o atributo \ref r
            \param g um inteiro para configurar o atributo \ref g
            \param b um inteiro para configurar o atributo \ref b
            \param a um inteiro para configurar o atributo \ref a

            O parâmetro <b>a</b> pode ser omitido no processo de invocação
            do método. Nesse caso, o valor será configurado automáticamente
            para o seu máximo.
            
        */
        CorRGBA(int r, int g, int b, int a=255):
            r(r),
            g(g),
            b(b),
            a(a)
        {
        }

        Uint32 getCor(SDL_Surface* surface)const{
            /*!
                Função para receber a cor em um formato útil e compatível
                ao usado por funções da bliblioteca SDL.

                Faz uso da função SDL_MapRGB()

                \param surface um ponteiro para um objeto SDL_Surface
                \return a cor no formato Uint32
            */
            return SDL_MapRGB(surface->format,r,g,b);
        }

        // Métodos de sobrecarga de operadores

        friend std::ostream& operator<< (std::ostream &out, const CorRGBA &cor){
            /*!
                Função amiga para ter acesso ao atributos protegidos da classe,
                visando sobscrita do operador << para apresentação de saída ao
                usuário.
                \return uma string no formato: (r,g,b,a)
            */
            out << "(" << cor.r << ", " << cor.g << ", " << cor.b << ", " << cor.a <<  ")";
            return out;
        }
};

#endif