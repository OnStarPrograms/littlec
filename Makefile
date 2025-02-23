run:
	g++ -std=c++14 -Werror -Wuninitialized -g src/* main.cpp -o build/test
	./build/test
test : ./src/* ./test/test.cpp
	g++ -std=c++14 -Werror -Wuninitialized -g build/catch_amalgamated.o test/test.cpp src/* -o build/test
	./build/test


