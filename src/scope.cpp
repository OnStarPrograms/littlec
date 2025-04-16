#include "../headers/scope.h"
#include <iostream>

scope::scope(){
    scopelevel = 0;
    tries_scope.push_back(TrieMemory());
    splays_scope.push_back(SplayMemory());
};

void scope::enter_scope(){
    scopelevel++;
    tries_scope.push_back(TrieMemory());
    splays_scope.push_back(SplayMemory());
}
bool scope::leave_scope(){
    if (scopelevel > 0){
        scopelevel--;
        tries_scope.pop_back();
        splays_scope.pop_back();
        return true;
    }
    return false;
}

void scope::decrement_var(std::string name, int size){
    splays_scope[scopelevel].decrement(name, size);
    tries_scope[scopelevel].decrement(name, size);
}


void scope::increment_var(std::string name, int size){
    splays_scope[scopelevel].increment(name, size);
    tries_scope[scopelevel].increment(name, size);
}

bool scope::insert_var(std::string name, util::type_wrapper variable){
    bool var;
    var = (tries_scope[scopelevel].insert(name, variable))?true:false;
    splays_scope[scopelevel].insert(name, variable);
    return var;
}

bool scope::operator()(std::string name, std::string right_name, char op){
    bool var;
    if (op != '>' && op != '<' && op != '~' && op != '|'){
        var = (tries_scope[scopelevel].operate(name, right_name, op))?true:false;
        splays_scope[scopelevel].operate(name, right_name, op);
        return var;
    }

    int i = 0;
    node* data_1 = tries_scope[scopelevel].find_node(name, i);
    i = 0;
    node* data_2 = tries_scope[scopelevel].find_node(right_name, i);

    if (op == '>'){
        if (data_1->size == 4){
            return data_1->data.get_int() > data_2->data.get_int();
        }
        if (data_1->size == 1){
            return data_1->data.get_char() > data_2->data.get_char();
        }
        return data_1->data.get_string() > data_2->data.get_string();
    }
    if (op == '<'){
        if (data_1->size == 4){
            return data_1->data.get_int() < data_2->data.get_int();
        }
        if (data_1->size == 1){
            return data_1->data.get_char() < data_2->data.get_char();
        }
        return data_1->data.get_string() < data_2->data.get_string();
    }
    if (op == '~'){
        if (data_1->size == 4){
            bool data__ = (data_1->data.get_int() == data_2->data.get_int());
            std::cout << data__ << std::endl; 

            return data_1->data.get_int() == data_2->data.get_int();
        }
        if (data_1->size == 1){
            return data_1->data.get_char() == data_2->data.get_char();
        }
        return data_1->data.get_string() == data_2->data.get_string();
    }
    else{
        if (data_1->size == 4){
            return data_1->data.get_int() != data_2->data.get_int();
        }
        if (data_1->size == 1){
            return data_1->data.get_char() != data_2->data.get_char();
        }
        return data_1->data.get_string() != data_2->data.get_string();
    }

}

util::type_wrapper scope::get_var(std::string name){
    util::type_wrapper var;
    node* var_nodes;
    for (int i = 0; i <= scopelevel; i++){
        
        splays_scope[i].find(name);
        
        var = tries_scope[i].find(name);
        int j = 0;
        var_nodes = tries_scope[i].find_node(name, j);

        if (var.has_data() != false){
            break;
        }
    }
    if (var_nodes->size == 4){
        std::cout << var.get_int() << std::endl;
    }
    else if (var_nodes->size == 1){
        std::cout << var.get_char() << std::endl;
    }
    else { 
        std::cout << var.get_string() << std::endl;
    }
    return var;
}

util::DataTracker scope::getData(){
    return util::DataTracker();
}
