CC=g++
CFLAGS= -std=c++11 -c 
DIR=../src/
@tack: main.o App.o Game.o Wall.o Player.o Enemy.o EnemyRook.o EnemyBishop.o EnemyStandard.o Level.o Point.o Entity.o PrintUtils.o
	$(CC) -o @tack main.o App.o Game.o Wall.o Player.o Enemy.o EnemyRook.o EnemyBishop.o EnemyStandard.o Level.o Point.o Entity.o PrintUtils.o

Point.o: $(DIR)Point.cpp
	$(CC) $(CFLAGS) $(DIR)Point.cpp 

PrintUtils.o: $(DIR)PrintUtils.cpp
	$(CC) $(CFLAGS) $(DIR)PrintUtils.cpp 

Entity.o: $(DIR)Entity.cpp
	$(CC) $(CFLAGS) $(DIR)Entity.cpp 

Wall.o: $(DIR)Wall.cpp
	$(CC) $(CFLAGS) $(DIR)Wall.cpp 

Player.o: $(DIR)Player.cpp
	$(CC) $(CFLAGS) $(DIR)Player.cpp

Enemy.o: $(DIR)Enemy.cpp
	$(CC) $(CFLAGS) $(DIR)Enemy.cpp 

EnemyStandard.o: $(DIR)EnemyStandard.cpp
	$(CC) $(CFLAGS) $(DIR)EnemyStandard.cpp 

EnemyRook.o: $(DIR)EnemyRook.cpp
	$(CC) $(CFLAGS) $(DIR)EnemyRook.cpp 

EnemyBishop.o: $(DIR)EnemyBishop.cpp
	$(CC) $(CFLAGS) $(DIR)EnemyBishop.cpp 

Level.o: $(DIR)Level.cpp
	$(CC) $(CFLAGS) $(DIR)Level.cpp  

Game.o: $(DIR)Game.cpp
	$(CC) $(CFLAGS) $(DIR)Game.cpp 

App.o: $(DIR)App.cpp
	$(CC) $(CFLAGS) $(DIR)App.cpp 

main.o: $(DIR)main.cpp
	$(CC) $(CFLAGS) $(DIR)main.cpp 

clean:
	-rm *.o $(objects) @tack
