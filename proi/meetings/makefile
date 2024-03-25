meetings.exe : datetime.o person.o meeting.o main.o
	g++ -g -o meetings.exe main.o

datetime.o : datetime.cpp datetime.h
	g++ -g -c -Wall -Wextra -pedantic datetime.cpp

person.o : person.cpp person.h
	g++ -g -c -Wall -Wextra -pedantic person.cpp

meeting.o : meeting.cpp meeting.h datetime.o person.o
	g++ -g -c -Wall -Wextra -pedantic meeting.cpp datetime.o person.o

main.o : main.cpp datetime.o person.o meeting.o
	g++ -g -c -Wall -Wextra -pedantic main.cpp meeting.o person.o datetime.o

clean :
	rm meetings.exe main.o meeting.o datetime.o person.o