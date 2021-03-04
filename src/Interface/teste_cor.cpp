#include "cor_rgba.h"

using namespace std;

int main(){
    // Declaração e Criação de objetos
    CorRGBA preto, branco, amarelo;

    preto = CorRGBA(0,0,0);
    branco = CorRGBA(255,255,255);
    amarelo = CorRGBA(255,255,0);

    // Exibição dos objetos do tipo CorRGBA
    cout << preto << endl;
    cout << branco << endl;
    cout << amarelo << endl;
    cout << amarelo.r << " ";
    cout << amarelo.g << " ";
    cout << amarelo.b << endl;

    return 0;
}