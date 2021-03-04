#include "linha.h"

using namespace std;

int main(){

    // Criação de objetos para a criação de uma Linha
    Ponto p1 = Ponto(1,0); 
    Ponto p2 = Ponto(0,1/2.f);

    Linha l = Linha(p1,p2);

    // Testes com o vetor normal da Linha
    cout << l.normal << endl;
    cout << l.normal * Vetor(p1,p2) << endl;

    return 0;
}