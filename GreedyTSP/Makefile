#####################################################
##################  MAKE_FILE  ######################
#####################################################

CXX = g++
CXXFLAGS = -std=c++0x
CXXFLAGS += -Wall
CXXFLAGS += -pedantic-errors
CXXFLAGS += -g


OBJS1 = greedyTSP.o

SRCS1 = greedyTSP.cpp


PROGRAM1_NAME = greedyTSP


${PROGRAM1_NAME}: ${OBJS1}
	${CXX} ${LDFLAGS} ${OBJS1} -o ${PROGRAM1_NAME}
	
${OBJS1}: ${SRCS1}
	${CXX} ${CXXFLAGS} -c $(@:.o=.cpp)	
	
run:
	./${PROGRAM1_NAME}
	
clean:
	rm *.o ${PROGRAM1_NAME}
