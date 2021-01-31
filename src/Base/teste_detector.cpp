#include "detector_colisao.h"

using namespace std;

double f(double t){
    return 0;
}

int main(){
    int qtd_objetos = 60;

    Objeto lista_objetos[qtd_objetos];
    
    Vetor posicao = Vetor(-400,0);
    for (int i=0; i<qtd_objetos; i++){
        lista_objetos[i] = Objeto(10, 10, posicao, Vetor(0,20), Aceleracao(f,f));
        posicao.x += 15;
    }

    DetectorColisao detector = DetectorColisao(qtd_objetos, lista_objetos);
    
    for (int i=0; i<qtd_objetos; i++){
        cout << lista_objetos[i] << endl;
    }

    cout << endl;
    
    detector.exibirObjetos();
    
    cout << endl;

    lista_objetos[59] = Objeto(0, 0, Vetor(), Vetor(), Aceleracao(f,f));
    
    detector.exibirObjetos();

    cout << endl;

    vector<pair<Objeto*,Objeto*>> colisoes = detector.detectar();

    for(int i=0; i<colisoes.size(); i++){
        cout << *(colisoes[i].first) << ", " << *(colisoes[i].second) << endl;
    }
    
    return 0;
}