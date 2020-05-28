CCOPTS=-Wall -std=c++11 -O3

all: tsp

tsp: obj/solution.o obj/axisgoal.o obj/tsp.o obj/city.o src/main.cpp
	g++ $(CCOPTS) -o $@ $^

obj/tsp.o: src/tsp.cpp src/header/tsp.h
	g++ $(CCOPTS) -o $@ -c src/tsp.cpp
	
obj/axisgoal.o: src/axisgoal.cpp src/header/axisgoal.h
	g++ $(CCOPTS) -o $@ -c src/axisgoal.cpp

obj/city.o: src/city.cpp src/header/city.h
	g++ $(CCOPTS) -o $@ -c src/city.cpp
	
obj/solution.o: src/solution.cpp src/header/solution.h
	g++ $(CCOPTS) -o $@ -c src/solution.cpp

clear:
	rm obj/* tsp
