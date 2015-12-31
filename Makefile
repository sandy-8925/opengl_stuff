all: build	

build: tutorial1 tutorial2

tutorial1:
	g++ -o tutorial1.out tutorial1.cpp -lGLEW -lglfw -lGL -lX11 -lpthread -lXrandr -lXi

tutorial2:
	g++ -o tutorial2.out tutorial2.cpp -lGLEW -lglfw -lGL -lX11 -lpthread -lXrandr -lXi

excercise2_1:
	g++ -o excercise2_1.out excercise2_1.cpp -lGLEW -lglfw -lGL -lX11 -lpthread -lXrandr -lXi

clean:
	rm *.out
