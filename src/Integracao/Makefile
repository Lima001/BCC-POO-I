END += .out
FLAG += `pkg-config --cflags --libs sdl2`

all:
	g++ movimento_simples.cpp -o movimento_simples$(END) $(FLAG)
	g++ movimento_aleatorio.cpp -o movimento_aleatorio$(END) $(FLAG)
	g++ movimento_colisao_simples.cpp -o movimento_colisao_simples$(END) $(FLAG)

clean:
	rm *$(END)