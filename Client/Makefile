CC := g++ -std=c++11
all: Client.out

Client.out: main.o Client.o
	$(CC) -o Client.out main.o Client.o

Client.o: Client.cpp Client.hpp
	$(CC) -c Client.cpp -o Client.o

main.o: main.cpp Client.hpp 
	$(CC) -c main.cpp -o main.o

.PHONY: clean
clean:
	rm *.o
	rm Client.out