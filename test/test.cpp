#include "catch/catch_amalgamated.hpp"
#include <bits/stdc++.h>

#define private public
#define protected public
#define class struct
//#include "../src/littlec.h"
//#include "../src/stack.h"
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



TEST_CASE("LL Insertion", "[heap]"){
	LL myLL;
    int place = 15;
    long int ptrPlace = myLL.insertData(place);
	REQUIRE(*myLL.find(ptrPlace) == place);
}

TEST_CASE("Multiple LL Insertions", "[heap]"){
	LL myLL;
    int place;
    long int ptrPlace;
    for (int i = 0; i < 15; i++){
        place = i;
        ptrPlace = myLL.insertData(place);
        std::cout << ":> " << ptrPlace << std::endl;
	    REQUIRE(*myLL.find(ptrPlace) == place);
    }
}

TEST_CASE("Heap Deletion", "[heap]"){
	LL myHeap;
    int place;
    int newPlace;
    long int ptrPlace;
    std::vector<int> soln;
    std::vector<long int> rem;
    for (int i = 0; i < 15; i++){
        place = i;
        if (i != 12 && i != 3){
            soln.push_back(i);
        }
        ptrPlace = myHeap.insertData(place);
        if (i == 12 || i ==3)
            rem.push_back(ptrPlace);
    } 
    REQUIRE(myHeap.removeData(rem[0]));
    REQUIRE(myHeap.removeData(rem[1]));
    
    Data* final_heap = myHeap.getLL();
    for (int i:soln){
        REQUIRE(i == *(final_heap->data));
        final_heap = final_heap->next;
    }
}

