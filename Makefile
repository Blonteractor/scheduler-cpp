all: build run
build: compile link

compile:
	clang++ -Wall -c -O0 src/algos/*.cpp
	clang++ -Wall -c -O0 src/*.cpp
	mv *.o build/

link:
	clang++ -Wall -O0 -o main build/*.o
	
clean:
	rm -rf build

run: 
	./main
