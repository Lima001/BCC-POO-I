END += .out
FLAG += `pkg-config --cflags --libs sdl2`

all:
	g++ movimento_simples.cpp -o movimento_simples$(END) $(FLAG)
	g++ movimento_aleatorio.cpp -o movimento_aleatorio$(END) $(FLAG)
	g++ movimento_colisao_simples.cpp -o movimento_colisao_simples$(END) $(FLAG)
	g++ movimento_colisao_cmux.cpp -o movimento_colisao_cmux$(END) $(FLAG)
	g++ movimento_colisao_cmb.cpp -o movimento_colisao_cmb$(END) $(FLAG)
	g++ movimento_colisao_borda.cpp -o movimento_colisao_borda$(END) $(FLAG)

clean:
	rm *$(END)