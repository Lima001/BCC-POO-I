// Adicionar `pkg-config --cflags --libs sdl2` para compilar

#include <SDL.h>    // Inclusão da biblioteca
#include <iostream> 

using namespace std;

void mover_retangulo_horizontal(SDL_Rect &retangulo, int limite, int deslocamento){
    /*
        Altera a posição x de um retângulo em uma unidade de deslocamento
        definida por parâmetro até atingir certo limite.
    */

    if (retangulo.x <= limite) retangulo.x += deslocamento;

    return;
}

int main(){

    int largura_tela = 800;
    int altura_tela = 600;
    char titulo[] = "Basico SDL";

    
    SDL_Window* janela = NULL;
    SDL_Surface* tela = NULL;
    SDL_Renderer* renderizador = NULL; // Variável que apontará para elemento responsável pela renderização

    SDL_Rect retangulo;                // Define um retângulo 
    // Define caracteristicas deste retângulos
    retangulo.x = 100;                 // Posição X
    retangulo.y = 100;                 // Posição Y
    retangulo.w = 50;                  // Largura
    retangulo.h = 50;                  // Altura

    SDL_Event evento;

    bool executar = true;

    if (SDL_Init(SDL_INIT_EVERYTHING) < 0){
        cout << "Erro ao Iniciar SDL - " << SDL_GetError() << endl;
        SDL_Quit();
    }
    
    janela = SDL_CreateWindow(
        titulo,
        SDL_WINDOWPOS_CENTERED, 
        SDL_WINDOWPOS_CENTERED, 
        largura_tela,
        altura_tela,
        0                       
    );

    if (janela == NULL) {
        cout << "Erro ao criar a Janela SDL - " << SDL_GetError() << endl;
        return 1;
    }

    tela = SDL_GetWindowSurface(janela);
    
    renderizador = SDL_CreateRenderer(
        janela,                  // Janela SDL
        -1,                      // Index Drive de renderização (-1: automático - Primeiro que suportar as flags)
        SDL_RENDERER_SOFTWARE    // Flags para renderização
    );

    Uint32 branco = SDL_MapRGB(
        tela->format,
        255, 255, 255
    );

    Uint32 azul = SDL_MapRGB(
        tela->format,
        0, 0, 255
    );

    while (executar){

        while (SDL_PollEvent(&evento)){
            
            if (evento.type == SDL_QUIT){
                executar = false;
                break;
            }
        }

        SDL_FillRect(tela, NULL, branco);
        SDL_FillRect(tela, &retangulo, azul); //Preenche o retângulo com a cor azul

        // Chamada de função própria
        mover_retangulo_horizontal(
            retangulo, 
            largura_tela - retangulo.w,
            5
        );

        // Desenhar Eixo X e Y do plano Cartesiano
        SDL_SetRenderDrawColor(
            renderizador,      // Renderizador
            0, 0, 0, 0     // RGBA
        );

        SDL_RenderDrawLine(
            renderizador,    // Renderizador
            0,                 // X inícial da Linha
            altura_tela/2,     // Y inicial da Linha
            largura_tela,      // X final da Linha
            altura_tela/2      // Y final da Linha
        );

        SDL_RenderDrawLine(renderizador, largura_tela/2, 0, largura_tela/2, altura_tela);
        
        SDL_RenderPresent(renderizador);    // Informa para renderizar os desenhos na tela
        
        SDL_UpdateWindowSurface(janela);
    }

    SDL_DestroyRenderer(renderizador); // Destroi o renderizador passado por parâmetro
    SDL_DestroyWindow(janela);
    SDL_Quit();

    return 0;
}