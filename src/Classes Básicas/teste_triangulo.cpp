#include <iostream>
#include "triangulo.h"

using namespace std;

int main(){
    Triangulo t1, t2, t3;

    t1 = Triangulo(Ponto(100,100), Ponto(0,200), Ponto(300,200));
    t3 = t1;

    cout << t1 << endl;
    cout << t2 << endl;
    cout << t3 << endl;

    cout << "\n";

    cout << t1.getPonto1() << "; ";
    cout << t1.getPonto2() << "; ";
    cout << t1.getPonto3() << endl;

    return 0;
}