CPP = g++

RM = rm -f

CPPFLAGS = -Wall -Wextra -pedantic -c

main: main.o
	$(CPP) $? -o $@

main.o: main.cpp
	$(CPP) $(CPPFLAGS) main.cpp -o $@

clean:
	$(RM) *.o main