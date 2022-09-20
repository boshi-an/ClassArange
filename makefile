flow:
	g++ -c -o linux/flow.o flow.cpp
	g++ -shared -o linux/flow.so linux/flow.o