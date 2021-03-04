#include "controlador_SDL.h"
#include "janela.h"

int main(){
    // Criação de objetos auxiliares e objeto Janela para teste de seus métodos

    Controlador_SDL control;
    CorRGBA branco, azul, verde;

    branco = CorRGBA();
    azul = CorRGBA(0,0,255);
    verde = CorRGBA(0,255,0);

    control = Controlador_SDL();
    control.inicializar();

    Janela janela = Janela("Testando", 800, 600);
    janela.iniciarSurface();

    control.pausar(2000);
    janela.preencherFundo(branco);
    janela.atualizar();
    control.pausar(2000);
    janela.preencherFundo(azul);
    janela.atualizar();
    control.pausar(2000);
    janela.preencherFundo(verde);
    janela.atualizar();
    control.pausar(2000);

    return 0;
}