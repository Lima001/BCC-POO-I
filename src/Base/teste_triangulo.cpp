#include <iostream>
#include "triangulo.h"

using namespace std;

int main(){
    // Criação de objetos
    Triangulo t1, t2, t3;

    t1 = Triangulo(Ponto(100,100), Ponto(0,200), Ponto(300,200));
    t2 = t1;
    t3 = move(t1);
    Triangulo t4 = t1;
    Triangulo t5 = move(t2);

    // Exibição de objetos do tipo Triangulo
    cout << t1 << endl;
    cout << t2 << endl;
    cout << t3 << endl;
    cout << t4 << endl;
    cout << t5 << endl;

    cout << "\n";

    // Acesso aos atributos de um Retangulo
    cout << t1.p1 << "; ";
    cout << t1.p2 << "; ";
    cout << t1.p3 << endl;

    return 0;
}