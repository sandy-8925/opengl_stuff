all: build	

build: tutorial1 tutorial2 excercise2_1 excercise2_2 excercise2_3 tutorial3

tutorial1:
	g++ -o tutorial1.out tutorial1.cpp -lGLEW -lglfw -lGL -lX11 -lpthread -lXrandr -lXi

tutorial2:
	g++ -o tutorial2.out tutorial2.cpp -lGLEW -lglfw -lGL -lX11 -lpthread -lXrandr -lXi

excercise2_1:
	g++ -o excercise2_1.out excercise2_1.cpp -lGLEW -lglfw -lGL -lX11 -lpthread -lXrandr -lXi

excercise2_2:
	g++ -o excercise2_2.out excercise2_2.cpp -lGLEW -lglfw -lGL -lX11 -lpthread -lXrandr -lXi

excercise2_3:
	g++ -o excercise2_3.out excercise2_3.cpp -lGLEW -lglfw -lGL -lX11 -lpthread -lXrandr -lXi

tutorial3: tutorial3_part1 tutorial3_part2 tutorial3_part3

tutorial3_part1:
	g++ -o tutorial3_part1.out tutorial3_part1.cpp -lGLEW -lglfw -lGL -lX11 -lpthread -lXrandr -lXi

tutorial3_part2:
	g++ -o tutorial3_part2.out tutorial3_part2.cpp -lGLEW -lglfw -lGL -lX11 -lpthread -lXrandr -lXi

tutorial3_part3:
	g++ -o tutorial3_part3.out tutorial3_part3.cpp -lGLEW -lglfw -lGL -lX11 -lpthread -lXrandr -lXi

tutorial3_part4:
	g++ -o tutorial3_part4.out tutorial3_part4.cpp -lGLEW -lglfw -lGL -lX11 -lpthread -lXrandr -lXi -fpermissive

tutorial3_excercise1:
	g++ -o tutorial3_excercise1.out tutorial3_excercise1.cpp -lGLEW -lglfw -lGL -lX11 -lpthread -lXrandr -lXi -fpermissive

clean:
	rm -f *.out
