#include "scope.h"
#include <iostream>

class interpreter : public scope {
    std::vector<util::dequeue<util::queue<std::string>*>> instructions;
    int depth;
  public:
    interpreter() : scope(){
        instructions.push_back(util::dequeue<util::queue<std::string>*>());
        instructions[0].push(new util::queue<std::string>());
        depth = 0;
    };
    bool create_int(std::string name, int val){
        instructions[depth].peek_tail()->push("var");
        instructions[depth].peek_tail()->push(name);
        instructions[depth].peek_tail()->push("1");
        instructions[depth].peek_tail()->push(std::to_string(val));
        return true;
    };
    bool create_string(std::string name, std::string val){
        instructions[depth].peek_tail()->push("var");
        instructions[depth].peek_tail()->push(name);
        instructions[depth].peek_tail()->push("2");
        instructions[depth].peek_tail()->push(val);
        return true;
    };
    bool create_char(std::string name, char val){
        instructions[depth].peek_tail()->push("var");
        instructions[depth].peek_tail()->push(name);
        instructions[depth].peek_tail()->push("3");
        instructions[depth].peek_tail()->push(std::to_string(val));
        return true;
    };
    
    bool compare(std::string name, std::string name_1, char code){
        instructions[depth].peek_tail()->push("comp");
        instructions[depth].peek_tail()->push(std::to_string(code));
        instructions[depth].peek_tail()->push(name);
        instructions[depth].peek_tail()->push(name_1);
        return true;
    };
    
    bool start_if(){
        instructions[depth].peek_tail()->push("if");
        depth+=1;
        if (instructions.size()-1 == depth){
            instructions[depth].push(new util::queue<std::string>);
        }
        else{
            instructions.push_back(util::dequeue<util::queue<std::string>*>());
            instructions[depth].push(new util::queue<std::string>);
        }
        return true;
    };
    bool end_if(){
        instructions[depth].peek_tail()->push("end_if");
        depth-=1;
        instructions[depth].peek_tail()->push("out_scope_check");

        return true;
    };

    bool start_while(){
        instructions[depth].peek_tail()->push("while");
        depth+=1;
        if (instructions.size()-1 == depth){
            instructions[depth].push(new util::queue<std::string>);
        }
        else{
            instructions.push_back(util::dequeue<util::queue<std::string>*>());
            instructions[depth].push(new util::queue<std::string>);
        }
        return true;
    };
    bool end_while(){
        depth-=1;
        instructions[depth].peek_tail()->push("out_scope_check");
        return true;
    };

    bool increment(std::string name){
        instructions[depth].peek_tail()->push("inc");
        instructions[depth].peek_tail()->push(name);
        return true;
    };
    bool decrement(std::string name){
        instructions[depth].peek_tail()->push("dec");
        instructions[depth].peek_tail()->push(name);
        return true;
    };

    bool print_var(std::string name){
        instructions[depth].peek_tail()->push("print");
        instructions[depth].peek_tail()->push(name);
        return true;
    };
    bool recv_int(std::string name){
        instructions[depth].peek_tail()->push("rec");
        instructions[depth].peek_tail()->push("int");
        instructions[depth].peek_tail()->push(name);
        return true;
    };
    bool recv_string(std::string name){
        instructions[depth].peek_tail()->push("rec");
        instructions[depth].peek_tail()->push("string");
        instructions[depth].peek_tail()->push(name);
        return true;
    };
    bool recv_char(std::string name){
        instructions[depth].peek_tail()->push("rec");
        instructions[depth].peek_tail()->push("char");
        instructions[depth].peek_tail()->push(name);
        return true;
    };

    bool set_var(std::string name, int val){
        instructions[depth].peek_tail()->push("set");
        instructions[depth].peek_tail()->push("int");
        instructions[depth].peek_tail()->push(name);
        return true;
    };
    bool set_var(std::string name, std::string val){
        instructions[depth].peek_tail()->push("set");
        instructions[depth].peek_tail()->push("string");
        instructions[depth].peek_tail()->push(name);
        return true;
    };
    bool set_var(std::string name, char val){
        instructions[depth].peek_tail()->push("set");
        instructions[depth].peek_tail()->push("char");
        instructions[depth].peek_tail()->push(name);
        return true;
    };

    util::DataTracker million_word_hell();
    util::DataTracker get_data();

    void run_program(){
        int program_depth = 0;
        util::stack<bool> compare_result;
        util::stack<int> while_loop;
        std::vector<std::string> prev_commands;
        instructions[0].peek_head()->push("end");

        while (instructions[0].peek_head()->size() != 0){
            if (instructions[program_depth].size() == 0){
                program_depth--;
                leave_scope();
            }
            std::string inst = instructions[program_depth].peek_head()->pop();
            
            prev_commands.push_back(inst);
            
            std::cout << inst << std::endl; 
            if (inst == "var"){
                std::string name = instructions[program_depth].peek_head()->pop();
                std::string type = instructions[program_depth].peek_head()->pop();
                if (type == "1"){
                    int num = std::stoi(instructions[program_depth].peek_head()->peek());
                    insert_var(name, util::type_wrapper(num)); 
                }
                if (type == "2"){
                    std::string num = (instructions[program_depth].peek_head()->peek());
                    insert_var(name, util::type_wrapper(num)); 
                }
                if (type == "3"){
                    char num = instructions[program_depth].peek_head()->peek()[0];
                    insert_var(name, util::type_wrapper(num)); 
                }
                
                prev_commands.push_back(name); 
                prev_commands.push_back(type); 
                prev_commands.push_back(instructions[program_depth].peek_head()->pop()); 
            }
            else if (inst == "if"){
                if (compare_result.peek() == true){
                    program_depth+=1;
                    enter_scope();

                }
            }
            else if (inst == "end_if"){
                instructions[program_depth].pop_head();
                program_depth-=1;
                leave_scope();
            }
            else if (inst == "out_scope_check"){
                if (compare_result.pop() == 0){
                    instructions[program_depth+1].pop_head();
                }
            }
            else if (inst == "comp"){
                char comp = (char)stoi(instructions[program_depth].peek_head()->pop());
                std::string name = instructions[program_depth].peek_head()->pop();
                std::string name_1 = instructions[program_depth].peek_head()->pop();
               
                prev_commands.push_back(std::to_string(comp));
                prev_commands.push_back(name);
                prev_commands.push_back(name_1);
            if (comp == '<' || comp == '>' || comp == '~' || comp == '|')
                compare_result.push(operator()(name, name_1, comp));
            else
                operator()(name, name_1, comp);
            }
            else if (inst == "while"){
                if (compare_result.peek() == true){
                    program_depth+=1;
                    enter_scope();
                    while_loop.push(1);
                    prev_commands.erase(prev_commands.begin());
                }
                instructions[program_depth].peek_head()->push("end_while");
            }
            else if (inst == "end_while"){
                if (compare_result.pop() == false){
                    program_depth-=1;
                    leave_scope();
                    while_loop.pop();
//                    instructions[program_depth].pop_head();
                }
            }
            else if (inst == "inc"){
                std::string name = instructions[program_depth].peek_head()->pop();
                increment_var(name, 1);
                prev_commands.push_back(name);
            }
            else if (inst == "dec"){
                std::string name = instructions[program_depth].peek_head()->pop();
                decrement_var(name, 1);
                prev_commands.push_back(name);
            }
            else if (inst == "print"){
                std::string name = instructions[program_depth].peek_head()->pop();
                prev_commands.push_back(name);
                get_var(name);
            }
            else if (inst == "rec"){

            }
            else if (inst == "set"){

            }

            if (while_loop.size() > 0){
                for (std::string command : prev_commands)
                      instructions[program_depth].peek_head()->push(command);
            }
            prev_commands.clear();

        }
    };
};
