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

// Função para definir aceleração nula
double f(double t){
    return 0;
}

int main(){
    // Definição de medidas de tempo - Importante para Integração e Movimentação dos Objetos
    double dt = 1/10.f;
    double t = 0;

    // Criação dos Objeto da simulação
    int qtd_objetos = 60;

    Objeto lista_objetos[qtd_objetos];
    Vetor posicao = Vetor(-400,0);

    for (int i=0; i<qtd_objetos; i++){
        lista_objetos[i] = Objeto(10, 10, posicao, Vetor(0,20), Aceleracao(f,f));
        posicao.x += 15;
    }

    // Declaração e Inicialização de objetos para manipulação da interface gráfica
    CorRGBA azul = CorRGBA(0,0,255);
    CorRGBA preto = CorRGBA(0,0,0);
    CorRGBA branco = CorRGBA();

    Controlador_SDL control;
    control = Controlador_SDL();
    control.inicializar();

    Relogio relogio = Relogio(control);
    
    Janela janela = Janela("Movimento Básico", 800, 600);
    janela.iniciarSurface();
    
    Renderizador render = Renderizador(janela.ptr_janela);
    
    // Definição da Matriz de Transformação para processo de Renderização
    render.transformacao = Matriz(3,3);
    render.transformacao[0][0] = 1;
    render.transformacao[0][1] = 0;
    render.transformacao[0][2] = 400;
    render.transformacao[1][0] = 0;
    render.transformacao[1][1] = -1;
    render.transformacao[1][2] = 300;
    render.transformacao[2][0] = 0;
    render.transformacao[2][1] = 0;
    render.transformacao[2][2] = 1;

    GerenciadorEvento gerenciador = GerenciadorEvento();

    PlanoCartesiano plano = PlanoCartesiano(20, 20, CorRGBA(0,0,0), CorRGBA(188,188,188),
                                            800, 600, Ponto(400,300));

    // Laço principal da Simulação
    bool executar = true;
    while (executar){
        // Registrar e interpretar Eventos
        gerenciador.registrarEvento();

        if (gerenciador.evento.tipo_evento == QUIT){
            executar = false;
            break;
        }
        else if (gerenciador.evento.tipo_evento == KEYDOWN){
            // Evento para inverter o sentido da velocidade
            if (gerenciador.evento.trigger == T_KP){
                for (int i=0; i<qtd_objetos; i++){
                    lista_objetos[i].v = lista_objetos[i].v * -1; 
                }
            }
        }

        // Renderizar fundo gráfico da Simulação
        janela.preencherFundo(branco);
        plano.desenharGrade(render);

        // Movimentar Objetos
        for (int i=0; i<qtd_objetos; i++){
            // Exibição do Objeto
            cout << lista_objetos[i] << endl;
            
            // Movimentação em si do objeto por Integração
            lista_objetos[i].movimentar(t,t+dt,dt);
            
            // Rendereização do Objeto - Circunferencia + Vetor velocidade
            render.desenhar_circunferencia(azul, lista_objetos[i].getCircunferencia());
            render.desenhar_vetor(preto, lista_objetos[i].v, lista_objetos[i].getCircunferencia().centro);
        }
        
        // Atualização do tempo da Simulação
        t += dt;
        
        // Atualização dos elementos gráficos para exibição dos resultados
        render.atualizar();
        janela.atualizar();
        
        // Controle de fps
        relogio.tick();
    }
    
    // Finalização SDL
    control.finalizar();

    return 0;
}