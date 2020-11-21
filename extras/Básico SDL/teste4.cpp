// Adicionar `pkg-config --cflags --libs sdl2` para compilar
#include <SDL.h>
#include <iostream>
#include <math.h>

#define PRECISAO 40

using namespace std;

struct ponto{
    int x, y;
};

struct circunferencia{
    ponto centro;
    int raio;
    /* 
        Array que guarda pontos da circunferência
        para que retas possam ser traçadas e formar
        uma circunferência. 
        
        Observação: Quanto maior for a quantidade escolhida,
        mais preciso a circunferência tende a ficar graficamente.
    */
    ponto demarcacao[PRECISAO];
    // int precisao;    // Define a quantidade de pontos a serem usados na demarcacao
};

void calcularDemarcacao(circunferencia *c){
    /*
        Acha pontos pertencentes a circunferência para
        que possamos desenhar o contorno dessa circunferẽncia
        futuramente com a função desenharBordaCircunferencia();
    */
    
    ponto p;
    // Calcular angulo a partir da variável de precisão
    float angulo = 360/PRECISAO;
    // Necessário Otimizar para não ser necessário tantos cálculos
    for (int i=0; i<PRECISAO; i++){
        p.x = c->centro.x + cos((angulo*i) * (M_PI/180.0f))*c->raio;
        p.y = c->centro.y + sin((angulo*i) * (M_PI/180.0f))*c->raio;
        c->demarcacao[i] = p;
    }
}

void desenharPontosCircunferencia(circunferencia *c, SDL_Renderer *renderizador){
    /*
        Desenha os pontos de demarcação de uma dada circunferencia.
        Permite averiguar os resultados da demarcação estão corretos
        de maneira gráfica.  
    */
    SDL_SetRenderDrawColor(renderizador, 0, 0, 255, 0);
    
    for (int i=0; i<PRECISAO; i++){
        SDL_RenderDrawPoint(renderizador, c->demarcacao[i].x, c->demarcacao[i].y);
    }
}

void desenharBordaCircunferencia(circunferencia *c, SDL_Renderer *renderizador){
    /*
        Resposnável por desenhar a circunferencia com base nos
        pontos de demarcação.
    */
    
    int pix, piy, pfx, pfy;

    SDL_SetRenderDrawColor(renderizador, 0, 0, 255, 0);

    for(int i=1; i<PRECISAO; i++){
        pix = c->demarcacao[i-1].x;
        piy = c->demarcacao[i-1].y;
        pfx = c->demarcacao[i].x;
        pfy = c->demarcacao[i].y;
        
        SDL_RenderDrawLine(renderizador, pix, piy, pfx, pfy);
    }

    pix = pfx;
    piy = pfy;
    pfx = c->demarcacao[0].x;
    pfy = c->demarcacao[0].y;
    
    SDL_RenderDrawLine(renderizador, pix, piy, pfx, pfy);
}

int main(){

    const int FPS = 60;
    const int LARGURA_TELA = 800;
    const int ALTURA_TELA = 600;
    
    char titulo_tela[] = "Básico SDL";

    ponto centro;
    centro.x = LARGURA_TELA/2;
    centro.y = ALTURA_TELA/2;

    circunferencia circ;
    circ.centro = centro;
    circ.raio = 50;
    calcularDemarcacao(&circ);

    int movimento = 5;              // Deslocamento circunferencia

    if (SDL_Init(SDL_INIT_EVERYTHING) < 0){
        cout << "Erro ao Iniciar SDL - " << SDL_GetError() << endl;
        SDL_Quit();
    }

    SDL_Window* janela = NULL;
    SDL_Surface* tela = NULL;
    SDL_Renderer* renderizador = NULL;

    SDL_Event evento;

    janela = SDL_CreateWindow(titulo_tela, SDL_WINDOWPOS_CENTERED,
                              SDL_WINDOWPOS_CENTERED, LARGURA_TELA, ALTURA_TELA, 0);

    if (janela == NULL) {
        cout << "Erro ao criar a Janela SDL - " << SDL_GetError() << endl;
        return 1;
    }

    tela = SDL_GetWindowSurface(janela);

    renderizador = SDL_CreateRenderer(janela, -1, SDL_RENDERER_SOFTWARE);

    Uint32 branco = SDL_MapRGB(tela->format, 255, 255, 255);

    Uint32 clock_inicial;

    bool executar = true;

    while (executar){
        clock_inicial = SDL_GetTicks();

        SDL_FillRect(tela, NULL, branco);

        SDL_SetRenderDrawColor(renderizador, 0, 0, 0, 0);
        SDL_RenderDrawLine(renderizador, 0, ALTURA_TELA/2, LARGURA_TELA, ALTURA_TELA/2);
        SDL_RenderDrawLine(renderizador, LARGURA_TELA/2, 0, LARGURA_TELA/2, ALTURA_TELA);

        /*
            Chamada dos Métodos para desenhar a circunferência;
        */
        // desenharPontosCircunferencia(&circ, renderizador);
        desenharBordaCircunferencia(&circ, renderizador);

        while (SDL_PollEvent(&evento)){
            
            if (evento.type == SDL_QUIT){
                executar = false;
                break;
            }
            /*
                Detectar entrada via teclado para movimentar a circunferência
            */
            else if (evento.type == SDL_KEYDOWN){
                /*
                    Detectar qual tecla foi pressionada para
                    aí poder modificar a posição do centro da
                    circunferência, alterando assim a sua posição
                */
                switch (evento.key.keysym.sym){

                    /*
                        Chamar função calcularDemarcacao();
                        Necessário recalcular as demarcações!
                        Como o centro não é mais o mesmo, as
                        'bordas' também já não são mais as mesmas.
                    */
                    case SDLK_LEFT:
                        circ.centro.x-=movimento;
                        calcularDemarcacao(&circ); 
                        break;

                    case SDLK_RIGHT: 
                        circ.centro.x+=movimento;
                        calcularDemarcacao(&circ);
                        break;
                    
                    case SDLK_UP:
                        circ.centro.y-=movimento;
                        calcularDemarcacao(&circ);
                        break;
                    
                    case SDLK_DOWN:
                        circ.centro.y+=movimento;
                        calcularDemarcacao(&circ);
                        break;

                } break;
            }
        }
        
        SDL_RenderPresent(renderizador);

        SDL_UpdateWindowSurface(janela);

        if ((1000 / FPS) > SDL_GetTicks() - clock_inicial){
            SDL_Delay(1000 / FPS - (SDL_GetTicks() - clock_inicial));
        }
    }

    SDL_DestroyRenderer(renderizador);
    SDL_DestroyWindow(janela);
    SDL_Quit();

    return 0;
}