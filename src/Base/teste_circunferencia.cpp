#include "circunferencia.h"

using namespace std;

int main(){
    Circunferencia c1 = Circunferencia(10, Ponto(10.1f, 20.3f));
    Circunferencia c2 = c1;
    Circunferencia c3 = move(c1);
    Circunferencia c4, c5;
    c4 = c1;
    c5 = move(c1);

    cout << c1 << endl;
    cout << c2 << endl;

    for(int i=0; i<c1.precisao; i++){
        cout << *(c1.demarcacao+i) << endl;
    }

    return 0;
}