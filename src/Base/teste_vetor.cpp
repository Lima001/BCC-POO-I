#include "vetor.h"

using namespace std;

int main(){
    // Instanciamento de objetos da Classe Vetor
    Vetor v1 = Vetor(1,1);              // Construtor Base
    Vetor v2 = Vetor(5,7);              // Construtor Base
    Vetor v3 = v1+v2;                   // Criação a partir da soma de Vetores
    Vetor v4 = v1-v2;                   // Criação a partir da subtração de Vetores
    Vetor v5 = 20*v1;                   // Criação a partir da multiplicação de um Vetor por um escalar
    Vetor v6 = Vetor(1.5, 0.75);        // Construtor Base
    Vetor v7;                           // COnstrutor Default
    v7 = v1;                            // Atribuição por Cópia
    
    Ponto inicio = Ponto(10.2,10.2);
    Ponto fim = Ponto(15.2,20.2);
    Vetor v8 = Vetor(inicio, fim);                  // Construtor Base (A partir de Pontos já existentes)
    Vetor v9 = Vetor(Ponto(10,10), Ponto(20,10));   // Construtor Base (A partir de Pontos criados no momento)

    Vetor v10 = v1;                                 // Construtor de Cópia

    // Exibição dos Vetores no console - Chamada ao operador <<
    cout << "Vetores:\n";
    cout << v1 << endl;
    cout << v2 << endl;
    cout << v3 << endl;
    cout << v4 << endl;
    cout << v5 << endl;
    cout << v6 << endl;
    cout << v7 << endl;
    cout << v8 << endl;
    
    // Atribuição por Movimentação
    v1 = move(v8);
    // Exibição do vetor com seus atributos atualizados
    cout << v8 << endl;

    // Exibição dos Vetores no console - Chamada ao operador <<
    cout << v9 << endl;
    cout << v10 << endl;

    // Chamada e exibição de algumas funções pertencentes aos Vetores
    cout << "Módulo v1: " << v1.getModulo() << endl;
    cout << "Módulo v3: " << v3.getModulo() << endl;
    cout << "Produto escalar v1 * v2: " << v1*v2 << endl;
    cout << v8.vetorToPonto() << endl;

    return 0;
}