#include "ponto.h"

using namespace std;

int main(){
    // Instanciamento de onjetos da classe Ponto

    Ponto p1 = Ponto(10.1, 20.3);       // Construtor Base
    Ponto p2 = Ponto(20, 50);           // Construtor Base
    Ponto p3 = Ponto(-100.01, 200.10);  // Construtor Base
    Ponto p4 = p2;                      // Construtor de Cópia
    Ponto p5;                        
    p5 = p1;                            // Atribuição por Cópia


    // Exibição dos Pontos no console - Chamada ao operador <<
    cout << "Pontos:\n";
    cout << p1 << endl;
    cout << p2 << endl;
    cout << p3 << endl;
    cout << p4 << endl;
    cout << p5 << endl;

    // Uso do Move Constructor e Move Assignment
    p4 = move(p1);                      // Atribuição Move
    Ponto p6 = move(p1);                // Construtor Move

    //Apenas para Teste Pontual!
    //p1.x = p1.x * 2;                  // Mudanças não alteram o estado dos outros vetores (p4 e p5) 
    
    // Exibição dos Pontos após movimentação de atributos - Chamada ao operador <<
    cout << p1 << endl;
    cout << p4 << endl;
    cout << p6 << endl;

    return 0;
}