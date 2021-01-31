#ifndef MATRIZ_H
#define MATRIZ_H

#include <iostream>
#include <assert.h>
#include <vector>

class Matriz {
    protected:
        void limpar(){
            if (ptr != nullptr){
                
                for (int i=0; i<n_linha; i++){
                    delete ptr[i];
                }

                delete[] ptr;
                ptr = nullptr;
            }
            n_linha = 0;
            n_coluna = 0;
        }

        void alocar(unsigned int n_linha_, unsigned n_coluna_){
            limpar();
            n_linha = n_linha_;
            n_coluna = n_coluna_;

            ptr = new double *[n_linha];

            for (int i=0; i<n_linha; i++){
                ptr[i] = new double[n_coluna];

                
                for (int j=0; j<n_coluna; j++){
                    ptr[i][j] = 0;
                }
            }
        }

        void copiar(const Matriz &m){
            for (int  i=0; i<n_linha; i++){
                for (int j=0; j<n_coluna; j++){
                    ptr[i][j] = m.ptr[i][j];
                }
            }
        }

    public:
        unsigned int n_linha;
        unsigned int n_coluna;
        double **ptr = nullptr;

        Matriz(){
            alocar(0,0);
        }

        Matriz(unsigned int n_linha, unsigned int n_coluna){
            alocar(n_linha, n_coluna);
        }
        
        Matriz(const Matriz &m){
            alocar(m.n_linha, m.n_coluna);
            copiar(m);
        };
        
        ~Matriz(){
            limpar();
        }

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

        void definir_linha(unsigned int index, const std::vector<double> &linha){
            assert(index >= 0 && index < n_linha && linha.size() == n_coluna);
            
            int cont = 0;

            for (double valor : linha){
                ptr[index][cont] = valor;
                cont++;
            }
        }

        Matriz& operator+=(const Matriz &m){
            assert(n_linha == m.n_linha && n_coluna == m.n_coluna);
            
            for (int  i=0; i<n_linha; i++){
                for (int j=0; j<n_coluna; j++){
                    ptr[i][j] += m.ptr[i][j];
                }
            }
            
            return *this;
        }

        Matriz operator+(const Matriz &m){
            assert(n_linha == m.n_linha && n_coluna == m.n_coluna);
            return Matriz(*this) += m;
        }

        Matriz& operator-=(const Matriz &m) {
            assert(n_linha == m.n_linha && n_coluna == m.n_coluna);

            for (int  i=0; i<n_linha; i++){
                for (int j=0; j<n_coluna; j++){
                    ptr[i][j] -= m.ptr[i][j];
                }
            }
        
            return *this;
        }

        Matriz operator-(const Matriz &m) {
            assert(n_linha == m.n_linha && n_coluna == m.n_coluna);
            return Matriz(*this) -= m;
        }

        Matriz& operator*=(float escalar){
            for (int i=0; i<n_linha; i++){
                for (int j=0; j<n_coluna; j++){
                    ptr[i][j] *= escalar;
                }
            }

            return *this;
        }

        friend Matriz operator*(const float escalar, const Matriz &m){
		    Matriz a = m;
            a *= escalar;
            
            return a;
	    }

        friend Matriz operator*(const Matriz &m, const float escalar){
            Matriz a = m;
            a *= escalar;
            
            return a;
	    }

        Matriz operator*(const Matriz &m){
            assert(n_coluna == m.n_linha);

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

        Matriz& operator=(const Matriz &m){
            alocar(m.n_linha, m.n_coluna); 
            copiar(m);
            return *this;
        }

        Matriz& operator=(const Matriz &&m){
            if (&m == this){
                return *this;
            }
            
            alocar(m.n_linha, m.n_coluna); 
            copiar(m);
            
            return *this;
        }

        double*& operator[](int index){
            assert(index >= 0 && index <= n_linha);
            return ptr[index];    
        }
};

#endif