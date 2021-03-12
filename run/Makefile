END += .out
FLAG += `pkg-config --cflags --libs sdl2`

all:
	g++ simulacao.cpp -o simulacao$(END) $(FLAG)

clean:
	rm *$(END)