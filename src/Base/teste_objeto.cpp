#include <iostream>
#include "objeto.h"

using namespace std;

double constante_0(double x){
    return 2;
}

int main(){
    Vetor posicao = Vetor(0,0);
    Vetor movimento = Vetor(10,10);
    Aceleracao aceleracao = Aceleracao(constante_0, constante_0);
    
    Objeto o1 = Objeto(20, 10, posicao, movimento, aceleracao);
    cout << o1 << endl;

    Objeto o2 = move(o1);

    int cont = 0;
    int max = 20;
    double ti = 0;
    double escala = 1;

    for (cont; cont<=max; cont++){
        cout << o2 << endl;
        
        o2.movimentar(ti, ti+escala, escala);
    }

    return 0;
}