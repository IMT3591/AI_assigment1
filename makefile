CC		= g++
IN		= environment.cpp dummyAgent.cpp main.cpp
IN2		= environment.cpp dummyAgent.cpp two_cell.cpp
IN3		= environment.cpp dummyAgent.cpp recursive.cpp
OUT		= main.exe

build:
	${CC} -g -Wall ${IN} -o ${OUT}

test:
	${CC} -g -Wall ${IN2} -o two_cell.exe

recursive:
	${CC} -g -Wall ${IN3} -o recursive.exe

clean:
	rm -f ${OUT}

