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

// Função para definir aceleração nula
double f_const(double t){
    return 0;
}

int main(){
    // Definição de medidas de tempo - Importante para Integração e Movimentação dos Objetos
    double dt = 1/20.f;
    double t = 0;

    // Criação dos Objeto da simulação
    int qtd_objetos = 2;
    Objeto lista_objetos[qtd_objetos];

    //lista_objetos[0] = Objeto(10, 20, Vetor(0,0), Vetor(0,20), Aceleracao(f_const,f_const));
    lista_objetos[0] = Objeto(10, 20, Vetor(0,0), Vetor(-25,-25), Aceleracao(f_const,f_const));
    lista_objetos[1] = Objeto(10, 50, Vetor(-100,100), Vetor(50,50), Aceleracao(f_const,f_const));

    // Declaração e Inicialização de objetos para manipulação da interface gráfica
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

    // Definição da Matriz de Transformação para processo de Renderização
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

    // Definição do motor de Colisão da Simulação - Aplica-se para todos os Objetos em lista_objetos
    DetectorColisao detector = DetectorColisao(qtd_objetos, lista_objetos);

    // Definição das linhas que aplicarão colisão na Simulação calculada pelo DetectorColisao
    Linha lista_linhas[4];
    
    // Obrigatório seguir essa ordem!
    lista_linhas[0] = Linha(Ponto(-400,300), Ponto(400,300));   // Linha horizontal superior
    lista_linhas[1] = Linha(Ponto(-400,-300), Ponto(400,-300)); // Linha horizontal inferior
    lista_linhas[2] = Linha(Ponto(-400,300), Ponto(-400,-300)); // Linha vertical esquerda
    lista_linhas[3] = Linha(Ponto(400,300), Ponto(400,-300));   // Linha vertical direita
    detector.setInfoLinhas(4,lista_linhas);

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
            // Evento para definir velocidade como nula
            if (gerenciador.evento.trigger == T_KP){
                for (int i=0; i<qtd_objetos; i++){
                    lista_objetos[i].v = lista_objetos[i].v * 0; 
                }
            }
        }

        // Renderizar fundo gráfico da Simulação
        janela.preencherFundo(branco);
        plano.desenharGrade(render);

        // Rendereização do Objeto - Circunferencia + Vetor velocidade
        for (int i=0; i<qtd_objetos; i++){
            render.desenhar_circunferencia(azul, lista_objetos[i].getCircunferencia());
            render.desenhar_vetor(preto, lista_objetos[i].v, lista_objetos[i].getCircunferencia().centro);
        }

        // Movimentação dos Objetos por Integração
        for (int i=0; i<qtd_objetos; i++){
            lista_objetos[i].movimentar(t,t+dt,dt);
        }

        // Avaliação e aplicação do efeito de colisão com conservação de movimento + colisão com borda
        detector.aplicar_colisao_borda();
        detector.aplicar_colisao_cm();

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