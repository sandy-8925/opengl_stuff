all: build	

build:
	g++ -o tutorial1 tutorial1.cpp -lGLEW -lglfw -lGL -lX11 -lpthread -lXrandr -lXi

clean:
	rm tutorial1
