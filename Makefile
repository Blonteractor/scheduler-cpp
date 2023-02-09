all: compile link clean

compile:
	clang++ -c *.cpp

link:
	clang++ -o main *.o
	
clean:
	rm -rf *.o 