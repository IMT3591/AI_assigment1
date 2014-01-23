CC		= g++
#IN		= main.cpp
IN		= environment.cpp dummyAgent.cpp main.cpp
OUT		= main.exe

build:
	${CC} -g -Wall ${IN} -o ${OUT}

clean:
	rm ${OUT}

