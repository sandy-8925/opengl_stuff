all: build	

build:
	g++ -o tutorial1.out tutorial1.cpp -lGLEW -lglfw -lGL -lX11 -lpthread -lXrandr -lXi

clean:
	rm *.out
