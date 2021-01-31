END += .out

all:
	g++ teste_ponto.cpp -o teste_ponto$(END)
	g++ teste_vetor.cpp -o teste_vetor$(END)
	g++ teste_circunferencia.cpp -o teste_circunferencia$(END)
	g++ teste_retangulo.cpp -o teste_retangulo$(END)
	g++ teste_triangulo.cpp -o teste_triangulo$(END)
	g++ teste_aceleracao.cpp -o teste_aceleracao$(END)
	g++ teste_objeto.cpp -o teste_objeto$(END)
	g++ teste_matriz.cpp -o teste_matriz$(END)
	g++ teste_detector.cpp -o teste_detector$(END) `pkg-config --cflags --libs sdl2`

clean:
	rm *$(END)