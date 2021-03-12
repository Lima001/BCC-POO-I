#include "controlador_SDL.h"
#include "renderizador.h"


int main(){
    // Testes referente a renderiazção de figuras usando a classe Renderizador

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

    Renderizador render = Renderizador(janela.ptr_janela);

    // Definição de uma Matriz de Transformação para o processo de Renderização
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

    janela.preencherFundo(CorRGBA(25,25,25));

    // Chamada aos métodos do Renderizador
    render.desenhar_ponto(azul, Ponto(50,50));
    render.desenhar_ponto(CorRGBA(255,0,0), Ponto(-50,-50));
    render.desenhar_ponto(verde, Ponto(0,0));

    render.desenhar_linha(CorRGBA(0,255,0), -400,0,400,0);
    
    render.desenhar_circunferencia(azul, Circunferencia(50, Ponto(0,10), 180));

    render.desenhar_triangulo(branco, Triangulo(Ponto(-50,0), Ponto(50,0), Ponto(0,100)));

    render.desenhar_retangulo(branco, Retangulo(Ponto(0,150),25,25));
    
    // Alteração da Matriz de Transformação para mudança no processo de renderização
    render.transformacao[0][0] = 2/10.f;
    render.transformacao[1][1] = -2/10.f;
    render.desenhar_vetor(branco, Vetor(60,80), Ponto(0,0));
    
    render.atualizar();
    janela.atualizar();

    control.pausar(20000);
    control.finalizar();

    return 0;
}