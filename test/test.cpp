
#include "catch/catch_amalgamated.hpp"
#include <iostream>
#include <bits/stdc++.h>

#define private public
#define protected public
#define class struct
//#include "../src/littlec.h"
//#include "../src/stack.h"
//#include "../src/trie.h"
#include "../src/heap.h"

using namespace std;


// the syntax for defining a test is below. It is important for the name to be unique, but you can group multiple tests with [tags]. A test can have [multiple][tags] using that syntax.

TEST_CASE("Test 2", "[flag]"){
	// you can also use "sections" to share setup code between tests, for example:
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

// you must write 5 unique, meaningful tests for credit on the testing portion of this project!


TEST_CASE("Heap Insertions", "[heap]"){
	// you can also use "sections" to share setup code between tests, for example:
	heap myHeap(15);
    int place = 15;
    int newPlace = place;
    int* ptrPlace = myHeap.insertData(place);

	REQUIRE(*ptrPlace == newPlace);
	REQUIRE(place != newPlace);

	// each section runs the setup code independently to ensure that they don't affect each other
}

TEST_CASE("Heap Insertions Fail", "[heap]"){
	// you can also use "sections" to share setup code between tests, for example:
	heap myHeap(15);
    int place;
    int newPlace;
    int* ptrPlace;
    for (int i = 0; i < 15; i++){
        place = i;
        newPlace = place;
        ptrPlace = myHeap.insertData(place);
	    REQUIRE(*ptrPlace == newPlace);
    }
    REQUIRE_THROWS_AS(myHeap.insertData(place), std::invalid_argument);
    
	// each section runs the setup code independently to ensure that they don't affect each other
}
