#ifndef COR_RGBA_H
#define COR_RGBA_H

#include <iostream>
#include <SDL.h>

/*!
    \file cor_rgba.h
    \class CorRGBA
    \author Gabriel Eduardo Lima
    \date Última modificação: 28/02/2021
    \brief Classe responsável por representar cores RGBA para uso em conjunto aos elementos gráficos
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
            Cria um objeto com os valores passados por parâmetro.

            \param r um inteiro para configurar o atributo de mesma nomenclatura
            \param g um inteiro para configurar o atributo de mesma nomenclatura
            \param b um inteiro para configurar o atributo de mesma nomenclatura
            \param a um inteiro para configurar o atributo de mesma nomenclatura

            O parâmetro \b a pode ser omitido no processo de invocação
            do método. Nesse caso, o valor será configurado automáticamente
            para o seu máximo (255).
            
        */
        CorRGBA(int r, int g, int b, int a=255):
            r(r),
            g(g),
            b(b),
            a(a)
        {
        }

        //! Retorna a cor RGBA
        /*!
            Método para receber a cor em um formato útil e compatível
            ao usado por funções da bliblioteca SDL.

            Faz uso da função SDL_MapRGB().

            \param surface um ponteiro para um objeto SDL_Surface
            \return cor no formato \c Uint32
            */
        Uint32 getCor(SDL_Surface* surface)const{
            return SDL_MapRGB(surface->format,r,g,b);
        }

        // Métodos de sobrecarga de operadores

        //! Sobrecarga do Insertion Operator para Saída de Dados
        /*!
            \return string no formato: "Cor(r,g,b,a)"
                    onde cada elemento refere-se aos valores
                    dos respectivos atributos do objeto
        */
        friend std::ostream& operator<< (std::ostream &out, const CorRGBA &cor){
            out << "Cor(" << cor.r << ", " << cor.g << ", " << cor.b << ", " << cor.a <<  ")";
            return out;
        }
};

#endif