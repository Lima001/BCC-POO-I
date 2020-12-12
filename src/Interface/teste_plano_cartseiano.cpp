#include "controlador_SDL.h"
#include "plano_cartesiano.h"


int main(){
    
    Controlador_SDL control;
    CorRGBA branco, verde;

    branco = CorRGBA();
    verde = CorRGBA(0,255,0,255);

    control = Controlador_SDL();
    control.inicializar();
    
    Janela janela = Janela("Testando", 800, 600);
    janela.iniciarSurface();
    
    Renderizador render = Renderizador(janela.ptr_janela);

    PlanoCartesiano plano = PlanoCartesiano(20,20,verde,branco,800,600);
    plano.desenharGrade(render);

    render.atualizar();
    janela.atualizar();

    control.pausar(5000);
    control.finalizar();

    return 0;
}