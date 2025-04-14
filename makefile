 # make file for mips computer simulation program :)

simulation: main.o alu.o controlunit.o datamemory.o hazardunit.o instructionmemory.o parser.o programcounter.o registerfile.o
	g++ main.o alu.o controlunit.o datamemory.o hazardunit.o instructionmemory.o parser.o programcounter.o registerfile.o -o simulation

main.o: main.cpp
	g++ -c main.cpp

alu.o: alu.cpp alu.h
	g++ -c alu.cpp 

controlunit.o: controlunit.cpp controlunit.h
	g++ -c controlunit.cpp

datamemory.o: datamemory.cpp datamemory.h
	g++ -c datamemory.cpp

hazardunit.o: hazardunit.cpp hazardunit.h
	g++ -c hazardunit.cpp

instructionmemory.o: instructionmemory.cpp instructionmemory.h
	g++ -c instructionmemory.cpp

parser.o: parser.cpp parser.h
	g++ -c parser.cpp

programcounter.o: programcounter.cpp programcounter.h
	g++ -c programcounter.cpp

registerfile.o: registerfile.cpp registerfile.h
	g++ -c registerfile.cpp


clean:
	rm *.o simulation


# target: dependencies
#	 action

