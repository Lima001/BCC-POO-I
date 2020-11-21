#include "vetor.h"

using namespace std;

int main(){
    Vetor v1 = Vetor(1,1);
    Vetor v2 = Vetor(5,7);
    Vetor v3 = v1+v2;
    Vetor v4 = v1-v2;
    Vetor v5 = 20*v1;
    Vetor v6 = Vetor(1.5, 0.75);
    
    Ponto inicio = Ponto(10.2,10.2);
    Ponto fim = Ponto(15.2,20.2);
    Vetor v7 = Vetor(inicio, fim);

    Vetor v8 = v1;

    cout << "Vetores:\n";
    cout << v1 << endl;
    cout << v2 << endl;
    cout << v3 << endl;
    cout << v4 << endl;
    cout << v5 << endl;
    cout << v6 << endl;
    cout << v7 << endl;
    cout << v8 << endl;

    cout << "Módulo v1: " << v1.getModulo() << endl;
    cout << "Módulo v3: " << v3.getModulo() << endl;
    cout << "Produto escalar v1 * v2: " << v1*v2 << endl;

    return 0;
}