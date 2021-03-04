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

    // Criação de um PlanoCartesiano
    PlanoCartesiano plano = PlanoCartesiano(20,20,verde,branco,800,600,Ponto(400,300));
    plano.desenharGrade(render);

    render.atualizar();
    janela.atualizar();

    control.pausar(5000);
    control.finalizar();

    return 0;
}