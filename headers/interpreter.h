#include "scope.h"
#include <iostream>

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
        instructions[depth].push("if");
        depth+=1;
        return true;
    };
    bool end_if(){
        instructions[depth].push("end_if");
        depth-=1;
        return true;
    };

    bool start_while(){
        instructions.push_back(util::queue<std::string>());
        instructions[depth].push("while");
        depth+=1;
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

    void run_program(){
        int program_depth = 0;
        util::stack<bool> compare_result;
        util::stack<int> while_loop;
        std::vector<std::string> prev_commands;


        while (instructions[0].size() != 0){
            if (instructions[program_depth].size() == 0){
                program_depth--;
                leave_scope();
            }
            std::string inst = instructions[program_depth].pop();
            
            prev_commands.push_back(inst);
            
            std::cout << inst << std::endl; 
            std::cout << program_depth << std::endl; 
            if (inst == "var"){
                std::string name = instructions[program_depth].pop();
                std::string type = instructions[program_depth].pop();
                if (type == "1"){
                    int num = std::stoi(instructions[program_depth].peek());
                    insert_var(name, util::type_wrapper(num)); 
                }
                if (type == "2"){
                    std::string num = (instructions[program_depth].peek());
                    insert_var(name, util::type_wrapper(num)); 
                }
                if (type == "3"){
                    char num = instructions[program_depth].peek()[0];
                    insert_var(name, util::type_wrapper(num)); 
                }
                
                prev_commands.push_back(name); 
                prev_commands.push_back(type); 
                prev_commands.push_back(instructions[program_depth].pop()); 
            }
            else if (inst == "if"){
                if (compare_result.pop() == true){
                    program_depth+=1;
                    enter_scope();
                }
            }
            else if (inst == "end_if"){
                program_depth-=1;
                leave_scope();
            }
            else if (inst == "comp"){
                char comp = (char)stoi(instructions[program_depth].pop());
                std::cout << comp << std::endl;
                std::string name = instructions[program_depth].pop();
                std::string name_1 = instructions[program_depth].pop();
               
                prev_commands.push_back(std::to_string(comp));
                prev_commands.push_back(name);
                prev_commands.push_back(name_1);
            if (comp == '<' || comp == '>' || comp == '~' || comp == '|')
                compare_result.push(operator()(name, name_1, comp));
            else
                operator()(name, name_1, comp);
            std::cout << compare_result.peek() << std::endl << "====" << std::endl;
            }
            else if (inst == "while"){
                if (compare_result.pop() == true){
                    program_depth+=1;
                    enter_scope();
                    while_loop.push(1);
                }
                instructions[program_depth].push("end_while");
            }
            else if (inst == "end_while"){
                if (compare_result.pop() == false){
                    program_depth-=1;
                    leave_scope();
                    while_loop.pop();
                }
            }
            else if (inst == "inc"){
                std::string name = instructions[program_depth].pop();
                increment_var(name, 1);
                prev_commands.push_back(name);
            }
            else if (inst == "dec"){
                std::string name = instructions[program_depth].pop();
                decrement_var(name, 1);
                prev_commands.push_back(name);
            }
            else if (inst == "print"){
                std::string name = instructions[program_depth].pop();
                prev_commands.push_back(name);
                get_var(name);
            }
            else if (inst == "rec"){

            }
            else if (inst == "set"){

            }


            if (while_loop.size() > 0){
                for (std::string command:prev_commands)
                    instructions[program_depth].push(command);
            }
            prev_commands.clear();
        }
    };
};
