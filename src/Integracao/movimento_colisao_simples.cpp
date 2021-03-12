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

// Função para definir aceleração nula
double f_const(double t){
    return 0;
}

int main(){
    // Definição de medidas de tempo - Importante para Integração e Movimentação dos Objetos
    double dt = 0.1f;
    double t = 0;

    // Criação dos Objeto da simulação
    Objeto lista_objetos[4];

    lista_objetos[0] = Objeto(10, 10, Vetor(0,-250), Vetor(0,15), Aceleracao(f_const,f_const));
    lista_objetos[1] = Objeto(10, 10, Vetor(0,250), Vetor(0,-15), Aceleracao(f_const,f_const));
    lista_objetos[2] = Objeto(10, 10, Vetor(-250,-250), Vetor(20,20), Aceleracao(f_const,f_const));
    lista_objetos[3] = Objeto(20, 10, Vetor(250,250), Vetor(-20,-20), Aceleracao(f_const,f_const));

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

    // Definição do motor de Colisão da Simulação - Aplica-se para todos os Objetos em lista_objetos
    DetectorColisao detector = DetectorColisao(4, lista_objetos);

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
                for (int i=0; i<4; i++){
                    lista_objetos[i].v = lista_objetos[i].v * -1; 
                }
            }
        }

        // Renderizar fundo gráfico da Simulação
        janela.preencherFundo(branco);
        plano.desenharGrade(render);


        // Rendereização do Objeto - Circunferencia + Vetor velocidade
        for (int i=0; i<4; i++){
            render.desenhar_circunferencia(azul, lista_objetos[i].getCircunferencia());
            render.desenhar_vetor(preto, lista_objetos[i].v, lista_objetos[i].getCircunferencia().centro);
        }

        // Movimentação dos Objetos por Integração
        for (int i=0; i<4; i++){
            lista_objetos[i].movimentar(t,t+dt,dt);
        }

        // Avaliação e aplicação do efeito de colisão simples
        detector.aplicar_colisao_simples();

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