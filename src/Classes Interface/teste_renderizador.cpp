#include "controlador_SDL.h"
#include "renderizador.h"


int main(){
    
    Controlador_SDL control;
    CorRGBA branco, azul, verde, preto;

    branco = CorRGBA();
    azul = CorRGBA(0,0,255);
    verde = CorRGBA(0,255,0);
    preto = CorRGBA(0,0,0);

    control = Controlador_SDL();
    control.inicializar();

    Janela janela = Janela("Testando", 800, 600);
    janela.iniciarSurface();
    Renderizador render = Renderizador(janela.getJanela());

    janela.preencherFundo(&branco);
    render.desenhar_linha(&verde, 0,300,800,300);

    Ponto p1,p2,p3;
    p1 = Ponto(400,290);
    p2 = Ponto(400,300);
    p3 = Ponto(400,310);

    render.desenhar_ponto(&preto, &p1);
    render.desenhar_ponto(&preto, &p2);
    render.desenhar_ponto(&preto, &p3);

    Circunferencia circ = Circunferencia(50, Ponto(400,300));
    render.desenhar_circunferencia(&azul, &circ);
    
    Triangulo triangulo = Triangulo(Ponto(200.5,200), Ponto(100,400), Ponto(300,400));
    render.desenhar_triangulo(&preto, &triangulo);

    Retangulo rect = Retangulo(Ponto(10,10),25,25);
    render.desenhar_retangulo(&preto, &rect); 
    
    render.atualizar();
    janela.atualizar();

    control.pausar(5000);
    control.finalizar();

    return 0;
}