#include <iostream>
#include "objeto.h"

using namespace std;

int main(){
    Vetor posicao = Vetor(0,0);
    Vetor movimento = Vetor(10,10);
    
    Objeto o1 = Objeto(20, posicao, movimento);
    cout << o1 << endl;

    Objeto o2 = move(o1);

    int cont = 0;
    int max = 20;

    for (cont; cont<max; cont++){
        cout << o2 << endl;
        
        o2.movimentar();
    }

    return 0;
}