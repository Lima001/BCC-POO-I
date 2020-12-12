#include "ponto.h"

using namespace std;

int main(){
    Ponto p1 = Ponto(10.1, 20.3);
    Ponto p2 = Ponto(20, 50);
    Ponto p3 = Ponto(-100.01, 200.10);
    Ponto p4 = p2;                      //Construtor de Cópia

    cout << "Pontos:\n";
    cout << p1 << endl;
    cout << p2 << endl;
    cout << p3 << endl;
    cout << p4 << endl;

    /*
        Uso de Move Constructor e Move Assignment
    */

    p4 = move(p1);                      // Atribuição Move
    Ponto p5 = move(p1);                // Construtor Move

    //Apenas para Teste Pontual!
    //p1.x = p1.x * 2;                  // Mudanças não alteram o estado dos outros vetores (p4 e p5) 
    
    cout << p1 << endl;
    cout << p4 << endl;
    cout << p5 << endl;

    return 0;
}