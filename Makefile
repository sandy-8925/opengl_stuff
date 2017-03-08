CC=gcc
COMPILE_OPTS=-lGLEW -lglfw -lGL -lX11 -lpthread -lXrandr -lXi -g -fpermissive

all: build	

build: tutorial1 tutorial2 excercise2_1 excercise2_2 excercise2_3 tutorial3

tutorial1: tutorial1.cpp
	g++ -o tutorial1.out tutorial1.cpp $(COMPILE_OPTS)

tutorial2: tutorial2.cpp
	g++ -o tutorial2.out tutorial2.cpp $(COMPILE_OPTS)

excercise2_1: excercise2_1.cpp
	g++ -o excercise2_1.out excercise2_1.cpp $(COMPILE_OPTS)

excercise2_2: excercise2_2.cpp
	g++ -o excercise2_2.out excercise2_2.cpp $(COMPILE_OPTS)

excercise2_3: excercise2_3.cpp
	g++ -o excercise2_3.out excercise2_3.cpp $(COMPILE_OPTS)

tutorial3: tutorial3_part1 tutorial3_part2 tutorial3_part3 tutorial3_part4 tutorial3_excercise1 tutorial3_excercise2 tutorial3_excercise3

tutorial3_part1: tutorial3_part1.cpp
	g++ -o tutorial3_part1.out tutorial3_part1.cpp $(COMPILE_OPTS)

tutorial3_part2: tutorial3_part2.cpp
	g++ -o tutorial3_part2.out tutorial3_part2.cpp $(COMPILE_OPTS)

tutorial3_part3: tutorial3_part3.cpp
	g++ -o tutorial3_part3.out tutorial3_part3.cpp $(COMPILE_OPTS)

tutorial3_part4: tutorial3_part4.cpp tutorial3_part4.vs tutorial3_part4.frag
	g++ -o tutorial3_part4.out tutorial3_part4.cpp $(COMPILE_OPTS) 

tutorial3_excercise1: tutorial3_excercise1.cpp tutorial3_excercise1.vs tutorial3_part4.frag
	g++ -o tutorial3_excercise1.out tutorial3_excercise1.cpp $(COMPILE_OPTS) 

tutorial3_excercise2: tutorial3_excercise2.cpp tutorial3_excercise2.vs tutorial3_part4.frag
	g++ -o tutorial3_excercise2.out tutorial3_excercise2.cpp $(COMPILE_OPTS) 

tutorial3_excercise3: tutorial3_excercise3.cpp
	g++ -o tutorial3_excercise3.out tutorial3_excercise3.cpp $(COMPILE_OPTS) 

tutorial4: tutorial4.cpp
	g++ -o tutorial4.out tutorial4.cpp $(COMPILE_OPTS) -lSOIL

clean:
	rm -f *.out
