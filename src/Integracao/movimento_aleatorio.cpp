#include <iostream>
#include <stdlib.h>
#include <time.h>

#include "../Base/ponto.h"
#include "../Base/vetor.h"
#include "../Base/circunferencia.h"
#include "../Base/objeto.h"

#include "../Interface/controlador_SDL.h"
#include "../Interface/cor_rgba.h"
#include "../Interface/janela.h"
#include "../Interface/renderizador.h"
#include "../Interface/plano_cartesiano.h"
#include "../Interface/relogio.h"
#include "../Interface/gerenciador_evento.h"

using namespace std;

double f(double x){
    return 0;
}

Vetor gerarVetor(){
    switch (rand() % 7 + 1){
        case 1:
            return Vetor(10,10);

        case 2:
            return Vetor(0,10);

        case 3:
            return Vetor(10,0);

        case 4:
            return Vetor(-10,0);

        case 5:
            return Vetor(0,-10);

        case 6:
            return Vetor(-10,-10);

        case 7:
            return Vetor(0,0);
        
        default:
            return Vetor(0,0);
    }
}

int main(){
    
    double t = 0;
    double dt = 1/10.f;

    Objeto modelo = Objeto(10, 10, Vetor(0,0), Vetor(0,0), Aceleracao(f,f));
    
    int qtd_objetos = 50;
    Objeto lista_objetos[qtd_objetos];

    for (int i=0; i<qtd_objetos; i++){
        lista_objetos[i] = move(modelo);
    }
    
    Circunferencia circ;
    //cout << circ << endl;

    CorRGBA azul = CorRGBA(0,0,255);
    CorRGBA preto = CorRGBA(0,0,0);
    CorRGBA branco = CorRGBA();

    Controlador_SDL control;
    control = Controlador_SDL();
    control.inicializar();

    Relogio relogio = Relogio(control);
    
    Janela janela = Janela("Teste", 800, 600);
    janela.iniciarSurface();
    
    Renderizador render = Renderizador(janela.ptr_janela);

    render.Transformacao = Matriz(3,3);
    render.Transformacao[0][0] = 1;
    render.Transformacao[0][1] = 0;
    render.Transformacao[0][2] = 400;
    render.Transformacao[1][0] = 0;
    render.Transformacao[1][1] = -1;
    render.Transformacao[1][2] = 300;
    render.Transformacao[2][0] = 0;
    render.Transformacao[2][1] = 0;
    render.Transformacao[2][2] = 1;

    GerenciadorEvento gerenciador = GerenciadorEvento();

    PlanoCartesiano plano = PlanoCartesiano(20, 20, CorRGBA(0,0,0), CorRGBA(188,188,188),
                                            800, 600, Ponto(400,300));


    bool executar = true;
    while (executar){
        gerenciador.registrarEvento();

        if (gerenciador.evento.tipo_evento == QUIT){
            executar = false;
            break;
        }
        
        janela.preencherFundo(branco);
        plano.desenharGrade(render);

        for (int i=0; i<qtd_objetos; i++){
            lista_objetos[i].v = move(gerarVetor());
           
            lista_objetos[i].movimentar(t,t+dt,dt);
            
            circ = move(lista_objetos[i].getCircunferencia());
            
            render.desenhar_circunferencia(azul, circ);
            render.desenhar_vetor(preto, lista_objetos[i].v, circ.centro);
        }
        
        t += dt;

        render.atualizar();
        janela.atualizar();
        relogio.tick();
    }
    
    control.finalizar();

    return 0;
}