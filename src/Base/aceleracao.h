#ifndef ACELERACAO_H
#define ACELERACAO_H

class Aceleracao {
    public:

        double (*func_x)(double) = nullptr;
        double (*func_y)(double) = nullptr;

        Aceleracao(){};

        Aceleracao(double (*func_x_)(double), double (*func_y_)(double))
        {
            func_x = func_x_;
            func_y = func_y_;
        }

        Aceleracao(const Aceleracao &aceleracao):
            func_x(aceleracao.func_x),
            func_y(aceleracao.func_x)
        {
        }

        Aceleracao(Aceleracao &&aceleracao) noexcept{
            func_x = aceleracao.func_x;
            func_y = aceleracao.func_y;
        }

        ~Aceleracao(){};


         Aceleracao& operator= (Aceleracao &aceleracao){
            func_x = aceleracao.func_x;
            func_y = aceleracao.func_y;

            return *this;
        }
        
        // Atribuição Move
        Aceleracao& operator= (Aceleracao &&aceleracao) noexcept {
            if (&aceleracao == this){
			    return *this;
            }

            func_x = aceleracao.func_x;
            func_y = aceleracao.func_y;

            return *this;
        }
};

#endif