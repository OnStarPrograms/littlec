run:
	g++ -std=c++14 -Werror -Wuninitialized -g src/main.cpp src/AVLTree.cpp -o build/test
	./build/test
test : ./src/AVLTree.h ./test/test.cpp
	g++ -std=c++14 -Werror -Wuninitialized -g build/catch_amalgamated.o test/test.cpp src/AVLTree.cpp -o build/test
	./build/test


