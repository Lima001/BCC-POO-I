#include "gerenciador_arquivo.h"

using namespace std;

double f_const(double t){
    return 0;
}

int main(){
    // Criação de um objeto do tipo GerenciadorArquivo para manipular o arquivo teste.txt
    string nome_arquivo = "teste.txt";
    GerenciadorArquivo g(nome_arquivo);

    // Criação do Arquivo
    g.criarArquivo();

    // Criação dos Objetos que serão salvos e recuperados do arquivo
    Objeto lista_objetos[3];
    lista_objetos[0] = Objeto(10, 20, Vetor(0,0), Vetor(0,20), Aceleracao(f_const,f_const));
    lista_objetos[1] = Objeto(10, 20, Vetor(0,0), Vetor(-25,-25), Aceleracao(f_const,f_const));
    lista_objetos[2] = Objeto(10, 50, Vetor(-100,100), Vetor(50,50), Aceleracao(f_const,f_const));

    g.salvarObjetos(3,lista_objetos);
    
    g.lerArquivo();
    cout << endl << "Linha 2: " << g.getLinhaN(2) << endl;
    
    g.recuperarObjetos(lista_objetos);
    cout << "--------------------" << endl;
    cout << lista_objetos[0] << endl;
    cout << lista_objetos[1] << endl;
    cout << lista_objetos[2] << endl;
    
    return 0;
}