#include "cor_rgba.h"

using namespace std;

int main(){

    CorRGBA preto, branco, amarelo;

    preto = CorRGBA(0,0,0);
    branco = CorRGBA(255,255,255);
    amarelo = CorRGBA(255,255,0);

    cout << preto << endl;
    cout << branco << endl;
    cout << amarelo << endl;
    cout << amarelo.get_r() << " ";
    cout << amarelo.get_g() << " ";
    cout << amarelo.get_b() << endl;

    return 0;
}