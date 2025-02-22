/*
#include "catch/catch_amalgamated.hpp"
#include <iostream>
#include <bits/stdc++.h>

#define private public
#define protected public
#define class struct
#include "../src/AVLTree.h"

using namespace std;

/*
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

*/
/*
//  Aiden Thomas
//  91401954


TEST_CASE("Test Tree Structure after inputs", "[insertion]"){
    AVLTree test;
    for (int i = 0; i <= 50; i++){
        test.insert("Node"+to_string(i), 50+i);
        test.insert("Node"+to_string(i), 50-i);
    }
    std::vector<node*> output;
    test.getInOrderTraversal(test.head, output);
    for (int i = 0; i < 100; i++){
        REQUIRE(output[i]->getId() == i);
    }
}

TEST_CASE("Test Tree Structure after inputs", "[searches]"){
    AVLTree test;
    for (int i = 0; i < 100; i++){
        test.insert("Node"+to_string(i), i*2);
    }
    // -- 2/3rds of 100 is 66, so 66 Tests are valid
    for (int i = 0; i < 66; i++){
        node* found = test.search(i*3, test.head);
        if ((i*3)%2 == 0){
            REQUIRE(found->getId() == i*3);
        }
        else {
            REQUIRE(found->getId() != i*3);
        }
    }
}

TEST_CASE("Test Tree Structure Input", "[deletion]"){
    AVLTree test;
    for (int i = 0; i < 100; i++){
        test.insert("Node"+to_string(i), i);
    }
    std::vector<int> answer;
    for (int i = 1; i < 10; i++){
        int deleted = rand()%100;
        test.deleteNode(deleted);
        answer.push_back(deleted);
    }
    std::vector<node*> nodeAnswer; 
    test.getInOrderTraversal(test.head, nodeAnswer);
    for (int i = 0; i < nodeAnswer.size(); i++){
        for (int j = 0; j < answer.size(); j++){
            REQUIRE(nodeAnswer[i]->getId() != answer[j]);
        }
    }    
}

//Do the Rotations
TEST_CASE("Test Tree Rotations", "[insertion]"){
    AVLTree test;
    test.insert("Node1", 1);
    
    SECTION("Left Rotation"){
        test.insert("Node2", 2);
        test.insert("Node3", 3);
        std::vector<node*> nodeAnswer; 
        test.getPreOrderTraversal(test.head, nodeAnswer);
        REQUIRE(2 == nodeAnswer[0]->getId());
        REQUIRE(1 == nodeAnswer[1]->getId());
        REQUIRE(3 == nodeAnswer[2]->getId());
    }
    SECTION("Right Rotation"){
        test.insert("Node2", 0);
        test.insert("Node3", -1);
        std::vector<node*> nodeAnswer; 
        test.getPreOrderTraversal(test.head, nodeAnswer);
        REQUIRE(0 == nodeAnswer[0]->getId());
        REQUIRE(-1 == nodeAnswer[1]->getId());
        REQUIRE(1 == nodeAnswer[2]->getId());
    }
    SECTION("RightLeft Rotation"){
        test.insert("Node2", 3);
        test.insert("Node3", 2);
        std::vector<node*> nodeAnswer; 
        test.getPreOrderTraversal(test.head, nodeAnswer);
        REQUIRE(2 == nodeAnswer[0]->getId());
        REQUIRE(1 == nodeAnswer[1]->getId());
        REQUIRE(3 == nodeAnswer[2]->getId());

    }
    SECTION("LeftRight Rotation"){
        test.insert("Node2", -1);
        test.insert("Node3", 0);
        std::vector<node*> nodeAnswer; 
        test.getPreOrderTraversal(test.head, nodeAnswer);
        REQUIRE(0 == nodeAnswer[0]->getId());
        REQUIRE(-1 == nodeAnswer[1]->getId());
        REQUIRE(1 == nodeAnswer[2]->getId());
    
    }
}

TEST_CASE("Test Tree Structure after inputs", "[deletion]"){
    AVLTree test;
    for (int i = 0; i < 100; i++){
        test.insert("Node"+to_string(i), i);
    }
    std::vector<int> answer;
    for (int i = 1; i < 100; i*=2){
        test.deleteNode(i);
        answer.push_back(i);
    }
    std::vector<node*> nodeAnswer; 
    test.getInOrderTraversal(test.head, nodeAnswer);
    for (int i = 0; i < nodeAnswer.size(); i++){
        for (int j = 0; j < answer.size(); j++){
            REQUIRE(nodeAnswer[i]->getId() != answer[j]);
        }
    }
    
}

TEST_CASE("Test Tree Structure after inputs", "[inorder deletion]"){
    AVLTree test;
    for (int i = 0; i < 100; i++){
        test.insert("Node"+to_string(i), i);
    }
    std::vector<int> answer;
    for (int i = 1; i < 50; i+=1){
        test.removeInOrder(1);
        answer.push_back(i);
    }
    std::vector<node*> nodeAnswer; 
    test.getInOrderTraversal(test.head, nodeAnswer);
    for (int i = 0; i < nodeAnswer.size(); i++){
        for (int j = 0; j < answer.size(); j++){
            REQUIRE(nodeAnswer[i]->getId() != answer[j]);
        }
    }
    
}


TEST_CASE("Test Tree Structure after inputs", "[insertion][deletion]"){
    AVLTree test;
    for (int i = 0; i <= 50; i++){
        test.insert("Node"+to_string(i), 50+i);
    }
    std::vector<int> answer;
    for (int i = 50; i < 100; i+=2){
        test.deleteNode(i);
        test.insert("NewNode",i*2);
        test.insert("Node",i);
    }
    std::vector<node*> output;
    test.getInOrderTraversal(test.head, output);
    int count = 0;
    for (int i = 0; i < output.size(); i++){
        if(output[i]->getName()== "NewNode")
            count++;
    }
    REQUIRE(count == 24);
    
    for (int i = 50; i < 100; i+=2){
        int a = test.search(i*2, test.head)->getId();
        REQUIRE(a == i*2);
    }
}
*/
