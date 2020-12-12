#include <iostream>
#include "controlador_SDL.h"

using namespace std;

int main(){
    Controlador_SDL control;
    
    control = Controlador_SDL();
    control.inicializar();
    control.pausar(1000);
    control.finalizar();

    return 0;
}