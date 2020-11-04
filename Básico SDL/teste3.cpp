// Adicionar `pkg-config --cflags --libs sdl2` para compilar

#include <SDL.h>
#include <iostream>

#define FPS 60                      // Definição de Frames Máximos por Segundo
#define LARGURA_TELA 800
#define ALTURA_TELA 600
#define TITULO_TELA "Básico SDL"
#define MOVIMENTO 5                 // Quantidade de deslocamento do retângulo

using namespace std;

int main(){

    if (SDL_Init(SDL_INIT_EVERYTHING) < 0){
        cout << "Erro ao Iniciar SDL - " << SDL_GetError() << endl;
        SDL_Quit();
    }

    SDL_Window* janela = NULL;
    SDL_Surface* tela = NULL;
    SDL_Renderer* renderizador = NULL;

    SDL_Rect retangulo;
    retangulo.x = 100;
    retangulo.y = 100;
    retangulo.w = 50;                 
    retangulo.h = 50;

    SDL_Event evento;

    janela = SDL_CreateWindow(TITULO_TELA, SDL_WINDOWPOS_CENTERED,
                              SDL_WINDOWPOS_CENTERED, LARGURA_TELA, ALTURA_TELA, 0);

    if (janela == NULL) {
        cout << "Erro ao criar a Janela SDL - " << SDL_GetError() << endl;
        return 1;
    }

    tela = SDL_GetWindowSurface(janela);

    renderizador = SDL_CreateRenderer(janela, -1, SDL_RENDERER_SOFTWARE);

    Uint32 branco = SDL_MapRGB(tela->format, 255, 255, 255);
    Uint32 azul = SDL_MapRGB(tela->format, 0, 0, 255);

    // Varíavel que armazena os milissegudos de execução
    Uint32 clock_inicial;

    bool executar = true;

    while (executar){
        
        // Armazena o milissigendo atual do incio do loop para calculos futuros
        clock_inicial = SDL_GetTicks();

        SDL_FillRect(tela, NULL, branco);

        SDL_SetRenderDrawColor(renderizador, 0, 0, 0, 0);
        SDL_RenderDrawLine(renderizador, 0, ALTURA_TELA/2, LARGURA_TELA, ALTURA_TELA/2);
        SDL_RenderDrawLine(renderizador, LARGURA_TELA/2, 0, LARGURA_TELA/2, ALTURA_TELA);

        // Altera a cor de desenho do renderizador para azul
        SDL_SetRenderDrawColor(renderizador, 0, 0, 255, 0);
        // Desenha o retângulo informado na tela
        SDL_RenderFillRect(renderizador, &retangulo);

        while (SDL_PollEvent(&evento)){
            
            if (evento.type == SDL_QUIT){
                executar = false;
                break;
            }
            // Verifica se o evento corresponde a uma teclas sendo pressionada
            else if (evento.type == SDL_KEYDOWN){
                
                // Verifica qual tecla foi pressionada
                // com intuito de locomover o retângulo conforme um padrão determinad
                switch (evento.key.keysym.sym){

                    case SDLK_LEFT:  retangulo.x-=MOVIMENTO; break;
                    case SDLK_RIGHT: retangulo.x+=MOVIMENTO; break;
                    case SDLK_UP:    retangulo.y-=MOVIMENTO; break;
                    case SDLK_DOWN:  retangulo.y+=MOVIMENTO; break;

                    /*
                    // Código para verificar posição do retângulo
                    // quando a tecla P for pressionada. Função: Testes!
                    case SDLK_p:     
                        cout << retangulo.x << ' ' << retangulo.y << endl; break;
                    */
                
                } break;
            }
        }
        
        SDL_RenderPresent(renderizador);

        SDL_UpdateWindowSurface(janela);

        // Limitação do FPS do loop de execução
        // Verifica se o tempo que a execução levou é maior
        // que o permitido em um segundo. Caso seja, atrasa
        // a execução no tempo que excedeu o máximo de FPS
        if ((1000 / FPS) > SDL_GetTicks() - clock_inicial){
            SDL_Delay(1000 / FPS - (SDL_GetTicks() - clock_inicial));
        }
    }

    SDL_DestroyRenderer(renderizador);
    SDL_DestroyWindow(janela);
    SDL_Quit();

    return 0;
}