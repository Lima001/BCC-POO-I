#include "ponto.h"
#include "circunferencia.h"

using namespace std;

int main(){
    Ponto p1 = Ponto(10.1f, 20.3f);
    Circunferencia c = Circunferencia(10, p1);

    return 0;
}