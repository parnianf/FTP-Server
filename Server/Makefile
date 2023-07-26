CC := g++ -std=c++11
all: Server.out

Server.out: main.o CommandHandler.o Server.o User.o UserManager.o JsonParser.o Logger.o
	$(CC) -o Server.out main.o CommandHandler.o Server.o User.o UserManager.o JsonParser.o Logger.o

JsonParser.o: JsonParser.cpp JsonParser.hpp Json.hpp User.hpp
	$(CC) -c JsonParser.cpp -o JsonParser.o

User.o: User.cpp User.hpp
	$(CC) -c User.cpp -o User.o

Logger.o: Logger.cpp Logger.hpp
	$(CC) -c Logger.cpp -o Logger.o

UserManager.o: UserManager.cpp UserManager.hpp User.hpp
	$(CC) -c UserManager.cpp -o UserManager.o

CommandHandler.o: CommandHandler.cpp CommandHandler.hpp User.hpp UserManager.hpp JsonParser.hpp Logger.hpp
	$(CC) -c CommandHandler.cpp -o CommandHandler.o

Server.o: Server.cpp Server.hpp CommandHandler.hpp JsonParser.hpp UserManager.hpp Logger.hpp
	$(CC) -c Server.cpp -o Server.o

main.o: main.cpp Server.hpp 
	$(CC) -c main.cpp -o main.o

.PHONY: clean
clean:
	rm *.o
	rm Server.out
	rm *.log