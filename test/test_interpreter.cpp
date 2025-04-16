#include "../headers/interpreter.h"

int main(){

    interpreter test;

    test.create_int("first_int", 5);
    test.create_int("second_int", 4);
    test.create_int("third_int", 3);
    test.create_int("fourth_int", 3);
    test.create_int("fourth_int", 2);
    test.create_string("fifth_int", "helloworld");
    test.compare("fourth_int", "third_int", '~');
    test.start_if();
    test.print_var("second_int");
    test.end_if();
   // 
    test.compare("first_int", "third_int", '~');
    test.start_if();
    test.print_var("fourth_int");
    test.end_if();
    test.print_var("first_int");
    test.print_var("fifth_int");
    test.run_program();
    return 0;
}
