#include <iostream>

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

double f(double t){
    return 0;
}

int main(){
    double dt = 1/10.f;
    double t = 0;

    int qtd_objetos = 60;

    Objeto lista_objetos[qtd_objetos];
    Vetor posicao = Vetor(-400,0);

    for (int i=0; i<qtd_objetos; i++){
        lista_objetos[i] = Objeto(10, 10, posicao, Vetor(0,20), Aceleracao(f,f));
        posicao.x += 15;
    }

    CorRGBA azul = CorRGBA(0,0,255);
    CorRGBA preto = CorRGBA(0,0,0);
    CorRGBA branco = CorRGBA();

    Controlador_SDL control;
    control = Controlador_SDL();
    control.inicializar();

    Relogio relogio = Relogio(control);
    
    Janela janela = Janela("Movimento Básico", 800, 600);
    janela.iniciarSurface();
    
    Renderizador render = Renderizador(janela.ptr_janela, Ponto(400,300), -1);

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
        else if (gerenciador.evento.tipo_evento == KEYDOWN){
            if (gerenciador.evento.trigger == T_KP){
                for (int i=0; i<qtd_objetos; i++){
                    lista_objetos[i].v = lista_objetos[i].v * -1; 
                }
            }
        }

        janela.preencherFundo(branco);
        plano.desenharGrade(render);

        for (int i=0; i<qtd_objetos; i++){
            cout << lista_objetos[i] << endl;
            lista_objetos[i].movimentar(t,t+dt,dt);
            
            render.desenhar_circunferencia(azul, lista_objetos[i].getCircunferencia());
            render.desenhar_vetor(preto, lista_objetos[i].v, lista_objetos[i].getCircunferencia().centro);
        }
        
        t += dt;
        
        render.atualizar();
        janela.atualizar();
        relogio.tick();
    }
    
    control.finalizar();

    return 0;
}