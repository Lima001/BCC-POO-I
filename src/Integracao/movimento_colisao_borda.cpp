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
    double dt = 1/5.f;
    double t = 0;

    int qtd_objetos = 2;
    Objeto lista_objetos[qtd_objetos];

    lista_objetos[0] = Objeto(10, 20, Vetor(0,0), Vetor(-25,-25), Aceleracao(f_const,f_const));
    lista_objetos[1] = Objeto(10, 50, Vetor(-100,100), Vetor(50,50), Aceleracao(f_const,f_const));

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

    DetectorColisao detector = DetectorColisao(qtd_objetos, lista_objetos);

    Linha lista_linhas[4];
    
    // Obrigatório seguir essa ordem!
    lista_linhas[0] = Linha(Ponto(-400,300), Ponto(400,300));   // Linha horizontal superior
    lista_linhas[1] = Linha(Ponto(-400,-300), Ponto(400,-300)); // Linha horizontal inferior
    lista_linhas[2] = Linha(Ponto(-400,300), Ponto(-400,-300)); // Linha vertical esquerda
    lista_linhas[3] = Linha(Ponto(400,300), Ponto(400,-300));   // Linha vertical direita
    detector.setInfoLinhas(4,lista_linhas);

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
                    lista_objetos[i].v = lista_objetos[i].v * 0; 
                }
            }
        }

        janela.preencherFundo(branco);
        plano.desenharGrade(render);

        for (int i=0; i<qtd_objetos; i++){
            render.desenhar_circunferencia(azul, lista_objetos[i].getCircunferencia());
            render.desenhar_vetor(preto, lista_objetos[i].v, lista_objetos[i].getCircunferencia().centro);
        }

        for (int i=0; i<qtd_objetos; i++){
            lista_objetos[i].movimentar(t,t+dt,dt);
        }

        detector.colisao_borda();
        detector.aplicar_colisao_teste();

        t += dt;

        render.atualizar();
        janela.atualizar();
        relogio.tick();
    }
    
    control.finalizar();

    return 0;
}