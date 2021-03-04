#include <iostream>
#include "aceleracao.h"

using namespace std;

/* 
    Definição de funções para construir um objeto do tipo aceleração,
    onde a aceleração referente ao eixo x condiz a um valor constante 
    (nesse caso, 5), e a aceleração referente ao eixo y condiz ao dobro
    de uma variável representando o tempo no laço for
*/

double constante_5(double x){
    return 5;
}

double dobro(double x){
    return x*2;
}

int main(){

    // Criação de objetos do tipo Aceleracao
    Aceleracao a1;
    a1 = Aceleracao(constante_5, dobro);

    Aceleracao a2 = a1;
    Aceleracao a3 = move(a2);

    Aceleracao a4, a5;
    a4 = a1;
    a5 = move(a1);

    // Chamada às funções as quais o objeto a5 possui ponteiros apontado
    for (int i=0; i<=10; i++){
        cout << a5.func_x(i) << endl;
        cout << a5.func_y(i) << endl;
    }

    return 0;
}