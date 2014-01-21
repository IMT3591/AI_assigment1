CC		= g++
IN		= environment.cpp main.cpp
OUT		= main.exe

build:
	${CC} -g -Wall ${IN} -o ${OUT}

clean:
	rm ${OUT}

