all: main.exe main2.exe

%.exe: %.cpp bit.cpp DES.cpp
	g++ -Wall -std=c++11 bit.cpp DES.cpp $< -o $@

run: 
	./main.exe

clean:
	rm *.exe

