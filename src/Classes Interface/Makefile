FLAG += `pkg-config --cflags --libs sdl2`

all:
	g++ teste_controlador.cpp -o teste_controlador $(FLAG)
	g++ teste_janela.cpp -o teste_janela $(FLAG)
	g++ teste_cor.cpp -o teste_cor $(FLAG)
	g++ teste_renderizador.cpp -o teste_renderizador $(FLAG)
	g++ teste_plano_cartseiano.cpp -o teste_plano_cartseiano $(FLAG)

clean:
	rm teste_controlador teste_janela teste_cor teste_plano_cartseiano teste_renderizador