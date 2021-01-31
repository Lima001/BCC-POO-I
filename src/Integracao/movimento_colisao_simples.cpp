#include <iostream>

#include "../Base/ponto.h"
#include "../Base/vetor.h"
#include "../Base/circunferencia.h"
#include "../Base/objeto.h"
#include "../Base/detector_colisao.h"

#include "../Interface/controlador_SDL.h"
#include "../Interface/cor_rgba.h"
#include "../Interface/janela.h"
#include "../Interface/renderizador.h"
#include "../Interface/plano_cartesiano.h"
#include "../Interface/relogio.h"
#include "../Interface/gerenciador_evento.h"

using namespace std;

double f_const(double t){
    return 0;
}

int main(){
    double dt = 1.f;
    double t = 0;

    Objeto lista_objetos[4];

    lista_objetos[0] = Objeto(10, 10, Vetor(0,-250), Vetor(0,15), Aceleracao(f_const,f_const));
    lista_objetos[1] = Objeto(10, 10, Vetor(0,250), Vetor(0,-15), Aceleracao(f_const,f_const));
    lista_objetos[2] = Objeto(10, 10, Vetor(-250,-250), Vetor(20,20), Aceleracao(f_const,f_const));
    lista_objetos[3] = Objeto(20, 10, Vetor(250,250), Vetor(-20,-20), Aceleracao(f_const,f_const));

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

    DetectorColisao detector = DetectorColisao(4, lista_objetos);

    bool executar = true;
    while (executar){
        gerenciador.registrarEvento();

        if (gerenciador.evento.tipo_evento == QUIT){
            executar = false;
            break;
        }
        else if (gerenciador.evento.tipo_evento == KEYDOWN){
            if (gerenciador.evento.trigger == T_KP){
                for (int i=0; i<4; i++){
                    lista_objetos[i].v = lista_objetos[i].v * -1; 
                }
            }
        }

        janela.preencherFundo(branco);
        plano.desenharGrade(render);

        for (int i=0; i<4; i++){
            render.desenhar_circunferencia(azul, lista_objetos[i].getCircunferencia());
            render.desenhar_vetor(preto, lista_objetos[i].v, lista_objetos[i].getCircunferencia().centro);
        }

        for (int i=0; i<4; i++){
            lista_objetos[i].movimentar(t,t+dt,dt);
        }

        detector.aplicar_colisao_simples();
        detector.verificar_colisao_borda(render,800,600);

        t += dt;

        render.atualizar();
        janela.atualizar();
        relogio.tick();
    }
    
    control.finalizar();

    return 0;
}