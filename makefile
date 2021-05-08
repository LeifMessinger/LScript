output: LInterpereter.o main.o
	g++ -std=c++17 LInterpereter.o main.o -o output

LInterpereter.o: LInterpereter.cpp LInterpereter.h
	g++ -std=c++17 -c LInterpereter.cpp

main.o: main.cpp LInterpereter.h
	g++ -std=c++17 -c main.cpp

clean:
	rm -f -v *.o output

run:
	./output

debug:
	g++ -std=c++17 -g LInterpereter.cpp main.cpp -o output

