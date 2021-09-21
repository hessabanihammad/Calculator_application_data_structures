mycalc2: mycalc2.o functions.o
	g++ mycalc2.o functions.o -o mycalc2

functions.o: functions.cpp functions.h
	g++ -c -std=c++11 functions.cpp

mycalc2.o: mycalc2.cpp mycalc2.h
	g++ -c -std=c++11 mycalc2.cpp

clean:
	rm *.o

