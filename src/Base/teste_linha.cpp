#include "linha.h"

using namespace std;

int main(){

    Ponto p1 = Ponto(1,0); 
    Ponto p2 = Ponto(0,1/2.f);

    Linha l = Linha(p1,p2);

    cout << l.normal << endl;
    cout << l.normal * Vetor(p1,p2) << endl;
    cout << l.a << endl;
    cout << l.b << endl;
    cout << l.c << endl;

    return 0;
}