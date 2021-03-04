#ifndef GERENCIADOR_ARQUIVO_H
#define GERENCIADOR_ARQUIVO_H

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include "../Base/objeto.h"

using namespace std;

/*!
    \file gerenciador_arquivo.h
    \class GerenciadorArquivo
    \author Gabriel Eduardo Lima
    \date Última Modificação: 27/02/2001
    \brief Classe para manipulação de arquivos visando
           a persitência de dados relacionados a objetos
           do tipo \ref Objeto. @see Objeto
*/

class GerenciadorArquivo {

    private:

        fstream target;             //!< Camada de manipulação de arquivo C++
        string endereco_arquivo;    //!< Endereço do arquivo a ser manipulado

        //! Particiona uma string a partir de um delimitador
        /*!
            Dada uma \c string \a str, o particionamento de \a str resultará
            um vetor onde cada elementos desse vetor será um elemento 
            particionado da string a partir da divisão usando-se um
            caractere delimitador.

            \param str Referência constante para a \c string a ser particionada 
            \param v Referência para o vector que armazenrá os pedaços da \c string particionada
            \param delim caractere usado como delimitador que separa as diferentes particões de uma \c string
            \return vetor onde os itens são os elementos particionados da \c string
        */
        void split(const string& str, vector<string>& v, char delim){
            // Criação de variáveis auxiliares
            stringstream ss(str);
            string token;
            
            while (std::getline(ss, token, delim)) {
                v.push_back(token);
            }

            // Limpar stream
            ss.flush();
        }

    public:

        //! Construtor default
        /*!
            Cria um objeto preparado para realizar manipulações
            sobre o arquivo no endereço informado por parâmetro.

            Observação: Não inicia nenhum processo de manipulação
            no arquivo!

            \param endereco_arquivo usado para inicializar atributo de mesma nomenclatura
        */
        GerenciadorArquivo(string endereco_arquivo):
            endereco_arquivo(endereco_arquivo){
        }

        //! Cria o arquivo informado ao gerenciador
        void criarArquivo(){
            target.open(endereco_arquivo, ios::out);
            target.close();
        }

        //! Apaga todo o conteúdo informado ao gerenciador
        void limparArquivo(){            
            target.open(endereco_arquivo, ios::out | ios::trunc);
            target.close();
        }

        //! Retorna uma linha específica conforme informado
        /*!
            Retorna uma linha \b n do arquivo do gerenciador. Em
            caso do número da linha informado não ser condizente
            com o conteúdo do arquivo, uma mensagem de erro será
            exibida e a operação retornará uma \c string vazia ao final

            \param n_linha número da linha que será retornada
        */
        string getLinhaN(int n_linha){
            target.open(endereco_arquivo, ios::in);
            
            string str;
            int linha_atual = 0;
            
            while (getline(target, str)){
                
                if (linha_atual == n_linha){
                    break;
                }

                str = "";
                linha_atual++;
            }
            
            target.close();

            // Mensagem de Erro
            if (linha_atual != n_linha)
                cout << "Erro - linha inexistente" << endl;

            return str;
        };

        //! Exibe todas as linhas do arquivo do gerenciador na ordem em que estiverem armazenadas
        void lerArquivo(){
            target.open(endereco_arquivo, ios::in);
            
            string str;
            
            while (getline(target,str))
                cout << str << endl;

            target.close();
        }

        //! Escreve os \ref Objeto no arquivo
        /*!
            Dada uma quantidade de objetos e um array de \ref Objeto com essa quantidade,
            esse método irá escrever cada Objeto em uma linha do arquivo
            conforme especifcado pela sobrecarga do operador << em \ref Objeto .

            \param qtd_objetos quantidade de objetos a serem salvos no arquivo
            \param lista_objetos objetos do tipo \ref Objeto que serão salvos no arquivo

            @see Objeto
        */
        void salvarObjetos(int qtd_objetos, Objeto* lista_objetos){
            target.open(endereco_arquivo, ios::app);
            
            for (int i=0; i<qtd_objetos; i++){
                target << *(lista_objetos+i) << endl;
            }
            
            target.close();
        };
        
        //! Recupera todos \ref Objeto do arquivo
        /*!
            Esse método é usado para recuperar os \ref Objeto
            presentes no arquivo passado para o gerenciador.
            Esse método é útil, pois permite a inicialização de diversos
            objetos usando como base um arquivo.

            Observação: Devido ao fato de um \ref Objeto possuir
            um atributo \a a que referese-se a um objeto \ref Aceleracao
            e que esse obejto é constítuido por funções e seus endereços de memória
            no momento da instaciação, não é possível recuperar a função usada nos
            objetos. Dessa forma, todo \ref Objeto recuperado de um arquivo terá sua aceleração
            definida pelo construtor default de \ref Aceleracao, devendo o desenvolvedor
            alterar esse atributo posteriormente conforme necessidade.

            \param lista_objetos Ponteiro para um array de \ref Objeto que deve
            possuir alocado ao mínimo a quantidade de Objeto salvos no arquivo
            para que esses possam ser recuperados e inseridos nesse array
        */
        void recuperarObjetos(Objeto* lista_objetos){
            target.open(endereco_arquivo, ios::in);
            
            // Variáveis Auxiliares
            int i = 0;
            string str, raio, massa;
            vector<string> vetor, r, v;
            
            while (getline(target, str)){
                // Partição do Objeto em seus atributos
                split(str.substr(7,str.length()-1), vetor, ';');
                
                raio = vetor[0];
                massa = vetor[1];

                // Partição das componentes dos vetores
                split(vetor[2], r, ',');
                split(vetor[3], v, ',');

                // Criação do Objeto com os dados recuperados do arquivo
                *(lista_objetos+i) = Objeto(
                    stof(raio),
                    stof(massa),
                    Vetor(stof(r[0].substr(6)),stof(r[1].substr(0,r[1].length()-1))),
                    Vetor(stof(v[0].substr(6)),stof(v[1].substr(0,v[1].length()-1)))
                );

                // Reset das variáveis auxiliares
                vetor.erase(vetor.begin(),vetor.end());
                r.erase(r.begin(),r.end());
                v.erase(v.begin(),v.end());

                i++;
            }
            
            target.close();
        };
};
#endif