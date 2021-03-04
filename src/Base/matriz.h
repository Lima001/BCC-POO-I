#ifndef MATRIZ_H
#define MATRIZ_H

#include <iostream>
#include <assert.h>
#include <vector>

/*!
    \file matriz.h
    \class Matriz
    \author Gabriel Eduardo Lima
    \date Última Modificação: 27/02/2001
    \brief Classe para Representação de Matrizes
*/

class Matriz {
    protected:

        unsigned int n_linha;       //!< Quantidade de linhas da Matriz
        unsigned int n_coluna;      //!< Quantidade de colunas da Matriz

        //! Método usado para resetar a \ref Matriz a um estado básico sem linhas nem colunas
        /*!
            Esse método é usado principalmente na necessidade de realocar a quantidade
            de memória dinâmica disponível para a \ref Matriz. Para isso é necessário antes
            deletar toda a memória anteriormente alocada para a Matriz para possível
            configuração conforme contexto.
        */
        void limpar(){
            if (ptr != nullptr){
                
                // Desalocação da Memória Dinamicamente alocada
                for (int i=0; i<n_linha; i++){
                    delete ptr[i];
                }

                delete[] ptr;
                ptr = nullptr;
            }
            // Configuração de Estado Básico
            n_linha = 0;
            n_coluna = 0;
        }

        //! Método usado para alocar memória dinâmica da \ref Matriz que o Invocar
        /*!
            Caso seja necessário alterar a estrutura da \ref Matriz,
            será necessário realocar a quantidade de memória disponível
            para ela.

            Uma vez alocados os espaços na memória para a \ref Matriz,
            os valores que podem ser interpretados como linhas e
            colunas serão todos preenchidos por 0.

            \param n_linha_ usado para definir a nova quantidade de linhas da \ref Matriz e permir a alocação de Memória
            \param n_coluna_ usado para definir a nova quantidade de colunas da \ref Matriz e permir a alocação de Memória
        */
        void alocar(unsigned int n_linha_, unsigned n_coluna_){
            // Desalocação da Memória atual da Matriz - Permite mudança na estrutura da Matriz
            limpar();
            
            n_linha = n_linha_;
            n_coluna = n_coluna_;
            
            // Alocação dinâmica da Memória criando um Ponteiro para Ponteiro (Interprete esse ponteiro como o array de linhas) 
            ptr = new double *[n_linha];

            for (int i=0; i<n_linha; i++){
                // Criação das colunas através do uso de ponteiros
                ptr[i] = new double[n_coluna];

                // Definição de valores default para as colunas
                for (int j=0; j<n_coluna; j++){
                    ptr[i][j] = 0;
                }
            }
        }
        //! Método usado para copiar os elementos de uma \ref Matriz
        /*!
            Esse método é usado para copiar apenas os elementos
            de uma \ref Matriz, isso é os valores de presentes em
            suas linhas e colunas. Para isso observe que a
            \ref Matriz que terá a sua estrutura copiada deve
            obrigatoriamente conter a mesma quantidade de linha
            e coluna da \ref Matriz de destino.

            \param m \ref Matriz que terá seus elementos copiados
        */
        void copiar(const Matriz &m){
            for (int  i=0; i<n_linha; i++){
                for (int j=0; j<n_coluna; j++){
                    ptr[i][j] = m.ptr[i][j];
                }
            }
        }

    public:
        
        double **ptr = nullptr;    //!< Ponteiro para Ponteiros usado para representar uma estrutura de Linhas e Colunas ou Array de Arrays

        //! Construtor Default
        /*!
            Chamado quando nenhum parâmetro de ininicialização for informado.
            
            Cria um objeto \ref Matriz sem linhas e nem colunas.
            Deve ser usado apenas para declaração de variáveis
            que futuramente terão a quantidade de linhas e colunas
            configuradas e memória alocada.

            Observação: Esse caso de objeto não deve ser usado em
            métodos de outras classes que exigem uma \ref Matriz como
            parâmetro. A título de exemplo, @see Renderizador.
        */
        Matriz(){
            alocar(0,0);
        }

        //! Construtor Default
        /*!
            Cria um objeto com a quantidade de linhas e colunas conforme
            dados passados como parâmetro. Nesse caso a memória será automáticamente
            alocada para atender a estrutura informada e valores default serão
            posicionados nas linhas e colunas.

            \param n_linha usado para inicializar atributo de mesma nomenclatura
            \param n_coluna usado para inicializar atributo de mesma nomenclatura
        */
        Matriz(unsigned int n_linha, unsigned int n_coluna){
            alocar(n_linha, n_coluna);
        }
        
        //! Construtor de Cópia
        /*!
            Cria um novo objeto copiando a estrutura e os valores
            de uma determinada Matriz informada.

            \param p Referência constante para a \ref Matriz que será copiada
        */
        Matriz(const Matriz &m){
            alocar(m.n_linha, m.n_coluna);
            copiar(m);
        };
        
        //! Destrutor da Classe
        ~Matriz(){
            limpar();
        }

        //! Método usado para exibir a \ref Matriz
        /*!
            Exibe as informações de linhas e colunas da \ref Matriz atual,
            bem como cada linha e coluna no formato usual de representação
            de matrizes.
        */
        void print(){
            std::cout << "Linhas: " << n_linha << std::endl;
            std::cout << "Colunas: " << n_coluna << std::endl;

            for (int i=0; i<n_linha; i++){
                for (int j=0; j<n_coluna; j++){
                    std::cout << ptr[i][j] << " ";
                }
                std::cout << std::endl;
            }
        }

        //! Método utilizado para preencher uma linha inteira da \ref Matriz com valores
        /*!
            Esse método é usado para tornar a atribuição de valores a \ref Matriz mais
            cômoda ao desenvolvedor. Através desse método é possível definir os valores
            de uma linha inteira através de um vetor C++ (vector). Os valores serão copiados 
            conforme sua posição no vetor, "da esquerda para a direita".

            \param index índice da linha que será alterada - Deve ser um valor >= 0 e dentro dos limites da estrutura da \ref Matriz
            \param linha \c vector contendo os elementos das colunas daquela linha
            
            \warning Caso o índice informado não seja válido na \ref Matriz, bem como caso
                     a quantidade de elementos do vetor seja superior a suportada pelo
                     objeto, a operação não será efetuada e o método será finalizado
        */
        void definir_linha(unsigned int index, const std::vector<double> &linha){
            // Verificar condições de incopatibildiade entre parâmetros e a estrutura atual da Matriz
            assert(index >= 0 && index < n_linha && linha.size() == n_coluna);
            
            int cont = 0;

            for (double valor : linha){
                ptr[index][cont] = valor;
                cont++;
            }
        }

        // Sobrecarga de Operadores

        //! Operador de Atibuição de Adição
        /*!
            Soma as respectivas linhas e colunas de uma \ref Matriz a
            \ref Matriz atual. Gera alteração da própria \ref Matriz, não
            criando um novo objeto.

            Observação: Para a soma ser bem sucedida, as matrizes
            devem possuir o exato número de linhas e colunas. Caso
            contrário a operação não é realizada.

            \param m Referência constante a \ref Matriz referente a parcela direita da Operação de Atrbuição de Adição
            \return Referência para a própria \ref Matriz que invocou o método
        */
        Matriz& operator+=(const Matriz &m){
            assert(n_linha == m.n_linha && n_coluna == m.n_coluna);
            
            for (int  i=0; i<n_linha; i++){
                for (int j=0; j<n_coluna; j++){
                    ptr[i][j] += m.ptr[i][j];
                }
            }
            
            return *this;
        }

        //! Operador de Adição
        /*!
            Soma as respectivas linhas e colunas de uma \ref Matriz a
            \ref Matriz atual gerando ao fim um novo objeto.

            Observação: Para a soma ser bem sucedida, as matrizes
            devem possuir o exato número de linhas e colunas. Caso
            contrário a operação não é realizada.

            \param m Referência constante a \ref Matriz referente a parcela direita da Operação de Soma
            \return \ref Matriz resultante da Operação de Soma
        */
        Matriz operator+(const Matriz &m){
            assert(n_linha == m.n_linha && n_coluna == m.n_coluna);
            return Matriz(*this) += m;
        }

        //! Operador de Atibuição de Subtração
        /*!
            Subtrai as respectivas linhas e colunas de uma \ref Matriz a
            Matriz atual. Gera alteração da própria \ref Matriz, não
            criando um novo objeto.

            Observação: Para a operação ser bem sucedida, as matrizes
            devem possuir o exato número de linhas e colunas. Caso
            contrário a operação não érRealizada.

            \param m Referência constante a \ref Matriz referente a parcela direita da Operação de Atrbuição de Subtração
            \return Referência para a própria \ref Matriz que invocou o operador
        */
        Matriz& operator-=(const Matriz &m) {
            assert(n_linha == m.n_linha && n_coluna == m.n_coluna);

            for (int  i=0; i<n_linha; i++){
                for (int j=0; j<n_coluna; j++){
                    ptr[i][j] -= m.ptr[i][j];
                }
            }
        
            return *this;
        }

        //! Operador de Subtração
        /*!
            Suntrai as respectivas linhas e colunas de uma \ref Matriz a
            \ref Matriz atual gerando ao fim um novo objeto.

            Observação: Para a operação ser bem sucedida, as matrizes
            devem possuir o exato número de linhas e colunas. Caso
            contrário a operação não é realizada.

            \param m Referência constante a \ref Matriz referente a parcela direita da Operação de Subtração
            \return \ref Matriz resultante da Operação
        */
        Matriz operator-(const Matriz &m) {
            assert(n_linha == m.n_linha && n_coluna == m.n_coluna);
            return Matriz(*this) -= m;
        }

        //! Operador de atibuição de multiplicação por escalar
        /*!
            Múltiplica as respectivas linhas e colunas de uma \ref Matriz
            por um número escalar. Gera alteração da própria \ref Matriz, não
            criando um novo objeto.

            \param escalar \c float usado para múltiplicar os valores da \ref Matriz que Invocou o operador
            \return Referência para a própria \ref Matriz que invocou o operador
        */
        Matriz& operator*=(float escalar){
            for (int i=0; i<n_linha; i++){
                for (int j=0; j<n_coluna; j++){
                    ptr[i][j] *= escalar;
                }
            }

            return *this;
        }

        //! Operador de atibuição de multiplicação por escalar a esquerda
        /*!
            Múltiplica as respectivas linhas e colunas de uma \ref Matriz
            por um número escalar informado a esquerda de \b *.
            Nesse caso gera uma nova \ref Matriz resultante da operação

            \param escalar \c float usado para múltiplicar os valores de uma \ref Matriz
            \param m Referência constante a uma \ref Matriz usada na Operação
            \return \ref Matriz resultante do produto entre a \ref Matriz de parâmetro e o escalar
        */
        friend Matriz operator*(const float escalar, const Matriz &m){
		    Matriz a = m;
            a *= escalar;
            
            return a;
	    }

        //! Operador de atibuição de multiplicação por escalar a direita
        /*!
            Múltiplica as respectivas linhas e colunas de uma \ref Matriz
            por um número escalar informado a direita de \b *.
            Nesse caso gera uma nova \ref Matriz resultante da operação

            \param escalar \c float usado para múltiplicar os valores de uma \ref Matriz
            \param m Referência constante a uma \ref Matriz usada na Operação
            \return \ref Matriz resultante do produto entre a \ref Matriz de parâmetro e o escalar
        */
        friend Matriz operator*(const Matriz &m, const float escalar){
            Matriz a = m;
            a *= escalar;
            
            return a;
	    }

        //! Múltiplicação entre Matrizes
        /*!
            Realiza a múltiplicação entre duas matrizes
            gerando ao final um novo objeto do tipo \ref Matriz
            como resultado da operação.

            Observação: Deve-se observar a condição matemática
            necessária para que a multiplicação entre as matrzies
            ocorra com sucesso. Considere uma matriz \f$ A (linha X coluna) \f$
            e a matriz \f$ B (linha X coluna) \f$. Para que a multiplicação
            ocorra deve-se observar a seguinte verdade \f$ A coluna = B linha \f$

            \param m Referência a \ref Matriz usada na operação de múltiplicação
            \return \ref Matriz resultante da múltplicação de matrizes 
        */
        Matriz operator*(const Matriz &m){
            assert(n_coluna == m.n_linha);

            // Alocação dinâmica da Memória conforme estrutura da Matriz Resultante
            Matriz resultado = Matriz(n_linha, m.n_coluna);

            for (int i=0; i<n_linha; i++){
                for (int j=0; j<m.n_coluna; j++){
                    for (int k=0; k<m.n_linha; k++){
                        resultado[i][j] += ptr[i][k] * m.ptr[k][j];
                    }
                }
            }

            return resultado;
        }

        //! Atribuição por Cópia
        /*!
            Copia a estrutura completa de uma \ref Matriz. Dessa forma
            pode-se copiar qualquer \ref Matriz, independente de sua
            quantidade de linhas e colunas divergirem da quantidade
            atual da \ref Matriz que invocou o operador. Isso deve-se ao
            fato da alocação dinâmica de memória realizada na
            chamada desse método.

            \param m Referência constante da \ref Matriz que será Copiado
            \return Referência para a \ref Matriz que invocou o operador
        */
        Matriz& operator=(const Matriz &m){
            alocar(m.n_linha, m.n_coluna); 
            copiar(m);
            
            return *this;
        }

        //! Atribuição Move
        /*!
            Movimenta a estrutura completa de uma \ref Matriz. Dessa forma
            pode-se usar como parâmetro qualquer \ref Matriz, independente de sua
            quantidade de linhas e colunas divergirem da quantidade
            atual da \ref Matriz que invocou o método. Isso deve-se ao
            fato da alocação dinâmica de memória realizada na
            chamada desse método.

            \param vetor Referência rvalue da \ref Matriz Base para a operação
            \return Referência para o \ref Matriz que Invocou o Método
        */
        Matriz& operator=(const Matriz &&m){
            /*
                Verifica se o parâmetro referencia o próprio objeto.
                Em caso de verdade, retorno a referência para o objeto
                atual. Em caso de falsidade, significa que a referência
                é para outro objeto e a movimentação dos atributos ocorre.
            */
            if (&m == this){
                return *this;
            }
            
            alocar(m.n_linha, m.n_coluna); 
            copiar(m);
            
            return *this;
        }

        //! Operador de Acesso
        /*!
            Usado quando é necessário acessar um elemento
            em um índice específico da \ref Matriz. Permite tanto
            a leitura quanto a escrita da posição da \ref Matriz .

            Observação: O índice informado deve ser compatível
            com a estrutura da \ref Matriz, caso contrário a operação
            não é realizada a fim de evitar acesso a espaços
            de memórias não pertencetes a \ref Matriz .

            \param index índice que deseja-se acessar
            \return Referência para o endereço de memória do elemento no índice informado
        */
        double*& operator[](int index){
            assert(index >= 0 && index <= n_linha);
            return ptr[index];    
        }
};

#endif