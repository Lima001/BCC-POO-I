#include <iostream>
#include "retangulo.h"

using namespace std;

int main(){
    Retangulo rect1, rect2, rect3;

    rect1 = Retangulo();
    rect2 = Retangulo(Ponto(10,10),50,50);
    rect3 = move(rect1);
    Retangulo rect4 = rect2;
    Retangulo rect5 = move(rect3);

    cout << rect1 << endl;
    cout << rect2 << endl;
    cout << rect3 << endl;
    cout << rect4 << endl;
    cout << rect5 << endl;

    cout << "\n";

    cout << rect4.inicio << endl;
    cout << rect4.altura << " - ";
    cout << rect4.largura << endl;

    return 0;
}