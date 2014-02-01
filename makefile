CC		= g++
#IN		= main.cpp
IN		= environment.cpp dummyAgent.cpp main.cpp
IN2		= environment.cpp dummyAgent.cpp two_cell.cpp
OUT		= main.exe

build:
	${CC} -g -Wall ${IN} -o ${OUT}

b:
	${CC} -g -Wall ${IN2} -o two_cell.exe

clean:
	rm ${OUT}

