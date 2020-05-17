#####################################################
##################  MAKE_FILE  ######################
#####################################################

FLAGS   := -O2 -DNDEBUG -ftree-vectorize -Wall
OBJECTS := main.o city.o tree.o algorithms.o

DivideConquerTSP: $(OBJECTS)
	g++ $(FLAGS) $(OBJECTS) -o DivideConquerTSP

main.o: main.cpp
	g++ $(FLAGS) -c main.cpp
	
city.o: city.cpp
	g++ $(FLAGS) -c city.cpp	
	
tree.o: tree.cpp
	g++ $(FLAGS) -c tree.cpp
	
algorithms.o: algorithms.cpp
	g++ $(FLAGS) -c algorithms.cpp

clean:
	rm -rf *o DivideConquerTSP
