#include "controlador_SDL.h"
#include "renderizador.h"


int main(){
    
    Controlador_SDL control;
    CorRGBA branco, azul, verde, preto;

    branco = CorRGBA();
    azul = CorRGBA(0,0,255);
    preto = CorRGBA(0,0,0);

    control = Controlador_SDL();
    control.inicializar();

    Janela janela = Janela("Testando", 800, 600);
    janela.iniciarSurface();

    Ponto origem = Ponto(400,300);
    Renderizador render = Renderizador(janela.ptr_janela,origem,-1);

    janela.preencherFundo(branco);
    
    render.desenhar_linha(CorRGBA(0,255,0), -400,0,400,0);

    //render.escala = 2.f;

    render.desenhar_ponto(preto, Ponto(50,50));
    render.desenhar_ponto(CorRGBA(255,0,0), Ponto(-50,-50));
    render.desenhar_ponto(preto, Ponto(0,0));

    render.desenhar_circunferencia(azul, Circunferencia(50, Ponto(0,10)));

    render.desenhar_triangulo(preto, Triangulo(Ponto(-50,0), Ponto(50,0), Ponto(0,100)));

    render.desenhar_retangulo(preto, Retangulo(Ponto(0,50),25,25));

    render.desenhar_vetor(preto, Vetor(0,80), Ponto(0,0));
    
    render.atualizar();
    janela.atualizar();

    control.pausar(5000);
    control.finalizar();

    return 0;
}