#include "controlador_SDL.h"
#include "plano_cartesiano.h"


int main(){
    // Criação de objetos auxiliares e objeto PlanoCartesiano para teste de seus métodos

    Controlador_SDL control;
    CorRGBA branco, verde;

    branco = CorRGBA();
    verde = CorRGBA(0,255,0,255);

    control = Controlador_SDL();
    control.inicializar();
    
    Janela janela = Janela("Testando", 800, 600);
    janela.iniciarSurface();
    
    Renderizador render = Renderizador(janela.ptr_janela);

    // Definição de uma Matriz de Transformação para o objeto do tipo Renderizador
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

    // Criação de um PlanoCartesiano
    PlanoCartesiano plano = PlanoCartesiano(20,20,verde,branco,800,600,Ponto(400,300));
    plano.desenharGrade(render);

    render.atualizar();
    janela.atualizar();

    control.pausar(5000);
    control.finalizar();

    return 0;
}