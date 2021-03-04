#include "circunferencia.h"

using namespace std;

int main(){
    // Criação de objetos do tipo Circunferencia
    Circunferencia c1 = Circunferencia(10, Ponto(10.1f, 20.3f));
    Circunferencia c2 = c1;
    Circunferencia c3 = move(c1);
    Circunferencia c4, c5;
    c4 = c1;
    c5 = move(c1);

    cout << c1 << endl;
    cout << c2 << endl;

    // Gerando e iterando sobre a demarcacao da Circunferencia c1
    c1.gerarDemarcacao();
    for(int i=0; i<c1.precisao; i++){
        cout << *(c1.demarcacao+i) << endl;
    }

    return 0;
}