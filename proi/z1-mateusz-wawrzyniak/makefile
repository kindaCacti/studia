ftest.exe : fract.o fract_test.o
	g++ -g -o ftest.exe fract.o fract_test.o

fract.o : fract.cpp fract.h
	g++ -g -c -Wall -Wextra -pedantic fract.cpp

fract_test.o : fract_test.cpp fract.h
	g++ -g -c -Wall -Wextra -pedantic fract_test.cpp

clean :
	rm ftest.exe fract.o fract_test.o
