#include "scope.h"

class interpreter : public scope {
    std::vector<util::queue<std::string>> instructions;
    int depth;
  public:
    interpreter() : scope(){
        instructions.push_back(util::queue<std::string>());
        depth = 0;
    };
    bool create_int(std::string name, int val){
        instructions[depth].push("var");
        instructions[depth].push(name);
        instructions[depth].push("1");
        instructions[depth].push(std::to_string(val));
        return true;
    };
    bool create_string(std::string name, std::string val){
        instructions[depth].push("var");
        instructions[depth].push(name);
        instructions[depth].push("2");
        instructions[depth].push(val);
        return true;
    };
    bool create_char(std::string name, char val){
        instructions[depth].push("var");
        instructions[depth].push(name);
        instructions[depth].push("3");
        instructions[depth].push(std::to_string(val));
        return true;
    };
    
    bool compare(std::string name, std::string name_1, char code){
        instructions[depth].push("comp");
        instructions[depth].push(std::to_string(code));
        instructions[depth].push(name);
        instructions[depth].push(name_1);
        return true;
    };
    
    bool start_if(){
        instructions.push_back(util::queue<std::string>());
        depth+=1;
        instructions[depth].push("if");
        return true;
    };
    bool end_if(){
        depth-=1;
        return true;
    };

    bool start_while(){
        instructions.push_back(util::queue<std::string>());
        depth+=1;
        instructions[depth].push("while");
        return true;
    };
    bool end_while(){
        depth-=1;
        return true;
    };

    bool increment(std::string name){
        instructions[depth].push("inc");
        instructions[depth].push(name);
        return true;
    };
    bool decrement(std::string name){
        instructions[depth].push("dec");
        instructions[depth].push(name);
        return true;
    };

    bool print_var(std::string name){
        instructions[depth].push("print");
        instructions[depth].push(name);
        return true;
    };
    bool recv_int(std::string name){
        instructions[depth].push("rec");
        instructions[depth].push("int");
        instructions[depth].push(name);
        return true;
    };
    bool recv_string(std::string name){
        instructions[depth].push("rec");
        instructions[depth].push("string");
        instructions[depth].push(name);
        return true;
    };
    bool recv_char(std::string name){
        instructions[depth].push("rec");
        instructions[depth].push("char");
        instructions[depth].push(name);
        return true;
    };

    bool set_var(std::string name, int val){
        instructions[depth].push("set");
        instructions[depth].push("int");
        instructions[depth].push(name);
        return true;
    };
    bool set_var(std::string name, std::string val){
        instructions[depth].push("set");
        instructions[depth].push("string");
        instructions[depth].push(name);
        return true;
    };
    bool set_var(std::string name, char val){
        instructions[depth].push("set");
        instructions[depth].push("char");
        instructions[depth].push(name);
        return true;
    };

    util::DataTracker million_word_hell();
    util::DataTracker get_data();

    void run_program();
};
