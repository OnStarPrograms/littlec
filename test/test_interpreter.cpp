#include "../headers/interpreter.h"

int main(){

    interpreter test;

    test.create_int("first_int", 5);
    test.create_int("second_int", 4);
    test.create_int("third_int", 3);
    test.create_int("fourth_int", 3);
    // test.create_int("fourth_int", 2);
    test.create_string("fifth_int", "helloworld");
    
    test.create_int("fou_int", 2);
    test.create_char("fif_int", '2');
    test.compare("fou_int", "fif_int", '~');


    test.compare("fourth_int", "third_int", '~');
    test.start_if();
        test.print_var("second_int");
    test.end_if();
    
    test.compare("first_int", "third_int", '~');
    test.start_if();
        test.print_var("fourth_int");
    test.end_if();

    test.create_int("i", 0);
    test.create_int("height", 5);
    test.compare("i", "height", '<');
    test.start_while();
        test.print_var("i");
        test.increment("i");
        test.compare("i", "height", '<');
    test.end_while();

    test.print_var("first_int");
    test.print_var("fifth_int");
    test.run_program();
    return 0;
}
