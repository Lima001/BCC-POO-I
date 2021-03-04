#include <iostream>
#include <math.h>

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
    double dt = 1/100.f;
    double t = 0;

    Objeto lista_objetos[4];

    lista_objetos[0] = Objeto(20, 20, Vetor(-250,0), Vetor(500,0), Aceleracao(f_const,f_const));
    lista_objetos[1] = Objeto(50, 50, Vetor(250,0), Vetor(-10,-0), Aceleracao(f_const,f_const));
    
    lista_objetos[2] = Objeto(25, pow(10,20), Vetor(-375,0), Vetor(0,0), Aceleracao(f_const,f_const));
    lista_objetos[3] = Objeto(25, pow(10,20), Vetor(375,0), Vetor(0,0), Aceleracao(f_const,f_const));

    CorRGBA azul = CorRGBA(0,0,255);
    CorRGBA preto = CorRGBA(0,0,0);
    CorRGBA branco = CorRGBA();

    Controlador_SDL control;
    control = Controlador_SDL();
    control.inicializar();

    Relogio relogio = Relogio(control);
    
    Janela janela = Janela("Movimento CMUX", 800, 600);
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

    DetectorColisao detector = DetectorColisao(4, lista_objetos);

    bool executar = true;
    while (executar){
        gerenciador.registrarEvento();

        if (gerenciador.evento.tipo_evento == QUIT){
            executar = false;
            break;
        }

        janela.preencherFundo(branco);
        plano.desenharGrade(render);

        for (int i=0; i<4; i++){
            render.desenhar_circunferencia(azul, lista_objetos[i].getCircunferencia());
        }

        for (int i=0; i<4; i++){
            lista_objetos[i].movimentar(t,t+dt,dt);
        }

        detector.aplicar_colisao_cm();

        t += dt;

        render.atualizar();
        janela.atualizar();
        relogio.tick();
    }
    
    control.finalizar();

    return 0;
}