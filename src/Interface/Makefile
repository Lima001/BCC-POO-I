END += .out
FLAG += `pkg-config --cflags --libs sdl2`

all:
	g++ teste_controlador.cpp -o teste_controlador$(END) $(FLAG)
	g++ teste_janela.cpp -o teste_janela$(END) $(FLAG)
	g++ teste_cor.cpp -o teste_cor$(END) $(FLAG)
	g++ teste_renderizador.cpp -o teste_renderizador$(END) $(FLAG)
	g++ teste_plano_cartseiano.cpp -o teste_plano_cartseiano$(END) $(FLAG)
	g++ teste_eventos.cpp -o teste_eventos$(END) $(FLAG)

clean:
	rm *$(END)