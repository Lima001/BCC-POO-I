// Adicionar `pkg-config --cflags --libs sdl2` para compilar

#include <SDL.h>    // Inclusão da biblioteca
#include <iostream> 

using namespace std;

int main(){

    //Variáveis que determinam caracteristicas da tela
    int largura_tela = 800;
    int altura_tela = 600;
    char titulo[] = "Basico SDL";

    
    SDL_Window* janela = NULL; // Variável que apontará para a janela criada pelo SDL
    SDL_Surface* tela = NULL;  // Variável que apontará para a tela ("onde podemos desenhar")

    SDL_Event evento;          // Variável que guardará os eventos registrados pelo SDL

    bool executar = true;     // Variável do loop de execuação principal


    /*
        Inicializa toda biblioteca e verifica se o processo ocorreu
        sem erros. Em caso de erros, Imprime uma mensagem indicando
        o erro identificado e finaliza a biblioteca.
    */
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0){
        cout << "Erro ao Iniciar SDL - " << SDL_GetError() << endl;
        SDL_Quit();
    }
    
    //Cria a Janela usando SDL_CreateWindow()
    janela = SDL_CreateWindow(
        titulo,
        SDL_WINDOWPOS_CENTERED, //Posição X da janela em relação a tela do computador
        SDL_WINDOWPOS_CENTERED, //Posição Y da janela em relação a tela do computador
        largura_tela,
        altura_tela,
        0                       // Flags - Nesse caso não foi usada nenhuma
    );

    // Verifica se houve exito no processo de criação da janela
    if (janela == NULL) {
        cout << "Erro ao criar a Janela SDL - " << SDL_GetError() << endl;
        return 1;
    }

    tela = SDL_GetWindowSurface(janela); // Cria a tela SDL a partir da Janela

    // Definição de Cores - Tipo Inteiro Positivo de 32 Bits - 8 bits para cada componente RGB

    Uint32 branco = SDL_MapRGB(
        tela->format,   // Usar pixels do formato da nossa tela (format está em tela)
        255, 255, 255   // Valores RGB
    );

    // Loop principal da execução
    while (executar){

        // Pega eventos pendentes e atribui a variável evento
        while (SDL_PollEvent(&evento)){
            
            // Verifica se o evento é de saída
            if (evento.type == SDL_QUIT){
                // Parar o loop de execução principal
                executar = false;
                break;
            }
        }
        /*
            Preenche Uma área Retângular com uma Cor.
            Nesse caso, vamos preencher a tela inteira
            declarando o retângulo (2º Parâmetro) como NULL
        */
        SDL_FillRect(tela, NULL, branco);
        
        SDL_UpdateWindowSurface(janela); // Atualiza o estado da janela
    }

    //SDL_Delay(10000); // Usar para pausar a execução

    SDL_DestroyWindow(janela); // Destroi a janela passada 
    SDL_Quit();                // Finaliza a biblioteca

    return 0;
}