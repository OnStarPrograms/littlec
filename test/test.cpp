#include "catch/catch_amalgamated.hpp"
#include <bits/stdc++.h>

#define private public
#define protected public
#define class struct
//#include "../src/littlec.h"
#include "../src/utils.h"
//#include "../src/trie.h"
#include "../src/ll.h"

using namespace std;


// the syntax for defining a test is below. It is important for the name to be unique, but you can group multiple tests with [tags]. A test can have [multiple][tags] using that syntax.

TEST_CASE("Test 2", "[flag]"){
	int one = 1;

	SECTION("num is 2") {
		int num = one + 1;
		REQUIRE(num == 2);
	};

	SECTION("num is 3") {
		int num = one + 2;
		REQUIRE(num == 3);
	};

	// each section runs the setup code independently to ensure that they don't affect each other
}

TEST_CASE("Util Insertions", "[stack]"){
	int array[] = {0,1,2,3,4,5,6,7,8,9};
	int answer[] = {9,8,7,6,5,4,3,2,1,0};
    util::stack<int> myStack;


    for (int i = 0; i < 10; i++){
        myStack.push(array[i]);
    }


    for (int i = 0; i < 10; i++){
        REQUIRE(myStack.peek() == answer[i]);
        REQUIRE(myStack.pop() == answer[i]);
    }
    std::cout << "Insertions Finished" << std::endl;
}
