#include "../headers/memory_trees.h"
#include <iostream>

int main(){
    {
        TrieMemory test;
        SplayMemory test_2;

        test_2.insert("foo", util::type_wrapper(5));

        test.insert("foo", util::type_wrapper(5));


        std::string test_var_two = "helloString";
        std::string test_var_two_data = "hello world";
        
        test.insert(test_var_two, util::type_wrapper(test_var_two_data));

        test_2.insert(test_var_two, util::type_wrapper(test_var_two_data));

        

        std::cout << (test.find("oogba").has_data() == false) << std::endl;
        std::cout << test.find(test_var_two).get_string() << std::endl;
        std::cout << test.find("foo").get_int() << std::endl;
        
        std::cout << (test_2.find("oogba").has_data() == false) << std::endl;
        std::cout << test_2.find(test_var_two).get_string() << std::endl;
        std::cout << test_2.find("foo").get_int() << std::endl;


        bool funky = false;
        test.insert("temp_var", (void*)&funky, 1);

        std::cout << test.find("temp_var").get_bool() << std::endl;
          
    }
    std::cout << "deletedTrie" << std::endl;
    std::cout << "deletedSplay" << std::endl;
}
