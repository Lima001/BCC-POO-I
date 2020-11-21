#include "ponto.h"


using namespace std;

int main(){
    Ponto p1 = Ponto(10.1, 20.3);
    Ponto p2 = Ponto(20, 50);
    Ponto p3 = Ponto(-100.01, 200.10);
    Ponto p4 = p2;

    cout << "Pontos:\n";
    cout << p1 << endl;
    cout << p2 << endl;
    cout << p3 << endl;
    cout << p4 << endl;

    return 0;
}