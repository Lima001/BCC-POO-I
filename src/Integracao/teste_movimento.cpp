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

int main(){
    Objeto lista_objetos[4];

    lista_objetos[0] = Objeto(10, Vetor(0,0), Vetor(20,20));
    lista_objetos[1] = Objeto(10, Vetor(0,0), Vetor(0,20));
    lista_objetos[2] = Objeto(10, Vetor(0,0), Vetor(-20,-20));
    lista_objetos[3] = Objeto(10, Vetor(0,0), Vetor(0,-20));
    
    Circunferencia circ;
    //cout << circ << endl;

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
                for (int i=0; i<=3; i++){
                    lista_objetos[i].movimento = lista_objetos[i].movimento * -1; 
                }
            }
        }
        
        janela.preencherFundo(branco);
        plano.desenharGrade(render);

        for (int i=0; i<=3; i++){
            lista_objetos[i].movimentar(static_cast<double>(1)/10);
            
            circ = move(lista_objetos[i].getCircunferencia());
            
            render.desenhar_circunferencia(azul, circ);
            render.desenhar_vetor(preto, lista_objetos[i].movimento, circ.centro);
        }
        
        render.atualizar();
        janela.atualizar();
        relogio.tick();
    }
    
    control.finalizar();

    return 0;
}