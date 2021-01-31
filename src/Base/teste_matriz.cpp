#include "matriz.h"

using namespace std;

int main(){

    Matriz m1 = Matriz(3,3);

    vector<double> l1 = {1,1,1};
    vector<double> l2 = {2,2,2};
    vector<double> l3 = {3,3,3};

    m1.definir_linha(0,l1);
    m1.definir_linha(1,l2);
    m1.definir_linha(2,l3);

    Matriz m2 = m1;

    m1.print();
    cout << endl;
    (m1 *= 2).print();
    cout << endl;
    (m1 += m2).print();
    cout << endl;
    (m1 + m2*2).print();
    cout << endl;
    (2*m1 + m2).print();
    cout << endl;
    (m1 -= m2).print();
    cout << endl;
    (m1 - m2).print();

    cout << endl;

    cout << m1[0][0] << endl;
    m1[0][0] = 57;
    cout << m1[0][0] << endl;
    m1.print();

    cout << endl;

    Matriz A = Matriz(3,2);
    Matriz B = Matriz(2,3);

    A.definir_linha(0, vector<double>{2,3});
    A.definir_linha(1, vector<double>{0,1});
    A.definir_linha(2, vector<double>{-1,4});

    B.definir_linha(0, vector<double>{1,2,3});
    B.definir_linha(1, vector<double>{-2,0,4});

    (A*B).print();
    cout << endl;
    (B*A).print();

    return 0;
}