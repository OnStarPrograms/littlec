# Active Build Methods

lexer: ./src/* ./test/*
	g++ -std=c++14 -Werror -Wuninitialized -g test/testLexerAndParser.cpp src/lexer.cpp src/parser.cpp src/scope.cpp src/memory_trees.cpp -o build/test
	./build/test
million: ./src/* ./test/*
	g++ -std=c++14 -Werror -Wuninitialized -g test/test_million_words.cpp src/memory_trees.cpp src/scope.cpp -o build/test
	./build/test


#old Methods

memory: ./src/* ./test/*
	g++ -std=c++14 -Werror -Wuninitialized -g test/test_memory_tree.cpp src/memory_trees.cpp src/scope.cpp -o build/test
	./build/test


interp: ./src/* ./test/*
	g++ -std=c++14 -Werror -Wuninitialized -g test/test_interpreter.cpp src/scope.cpp  src/memory_trees.cpp -o build/test
	./build/test

data: ./src/* ./test/*
	g++ -std=c++14 -Werror -Wuninitialized -g test/test_data.cpp src/memory_trees.cpp src/scope.cpp -o build/test
	./build/test


