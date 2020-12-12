#include "controlador_SDL.h"
#include "janela.h"
#include "gerenciador_evento.h"

using namespace std;

int main(){

    Controlador_SDL control;
    CorRGBA branco, azul, verde;

    branco = CorRGBA();
    azul = CorRGBA(0,0,255);
    verde = CorRGBA(0,255,0);

    control = Controlador_SDL();
    control.inicializar();

    Janela janela = Janela("Testando", 800, 600);
    janela.iniciarSurface();

    GerenciadorEvento gerenciador = GerenciadorEvento();

    bool executar = true;
    while (executar){
        gerenciador.registrarEvento();

        if (gerenciador.evento.tipo_evento == QUIT){
            executar = false;
            break;
        }
        else if (gerenciador.evento.tipo_evento == KEYDOWN){
            if (gerenciador.evento.trigger == T_KP){
                cout << "OI!!!" << endl;
            }

            cout << gerenciador.evento << endl;
        }

        janela.atualizar();
    }
    
    gerenciador.registrarEvento();
    cout << gerenciador.evento << endl;
    
    return 0;
}