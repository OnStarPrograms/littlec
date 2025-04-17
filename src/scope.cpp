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
    util::type_wrapper var_node;
      int i = 0;
      for (; i <= scopelevel; i++){

         splays_scope[i].find(name);

         var_node = tries_scope[i].find(name);

         if (var_node.has_data() != false){
             break;
         }
     }
    //splays_scope[i].increment(name, size);
    tries_scope[i].decrement(name, size);
}


void scope::increment_var(std::string name, int size){
      util::type_wrapper var_node;
      int i = 0;
      for (; i <= scopelevel; i++){

         splays_scope[i].find(name);

         var_node = tries_scope[i].find(name);

         if (var_node.has_data() != false){
             break;
         }
     }
    //splays_scope[i].increment(name, size);
    tries_scope[i].increment(name, size);
}

bool scope::insert_var(std::string name, util::type_wrapper variable){
    bool var;
    var = (tries_scope[scopelevel].insert(name, variable))?true:false;
    splays_scope[scopelevel].insert(name, variable);
    return var;
}

bool scope::operator()(std::string name, std::string right_name, char op){
    bool var;
    

    node* data_1 = nullptr; 
    util::type_wrapper data_1_var;
     for (int i = 0; i <= scopelevel; i++){

         splays_scope[i].find(name);

         data_1_var = tries_scope[i].find(name);
         int j = 0;
         data_1 = tries_scope[i].find_node(name, j);

         if (data_1_var.has_data() != false){
             break;
         }
     }
    node* data_2 = nullptr; 
    util::type_wrapper data_2_var;
    int i = 0;
     for (; i <= scopelevel; i++){

         splays_scope[i].find(name);

         data_2_var = tries_scope[i].find(right_name);
         int j = 0;
         data_2 = tries_scope[i].find_node(right_name, j);

         if (data_2_var.has_data() != false){
             break;
         }
     }
    if (data_1_var.has_data() == false || data_2_var.has_data() == false)
        return false;
    if (op != '>' && op != '<' && op != '~' && op != '|'){
        var = (tries_scope[i].operate(name, right_name, op))?true:false;
        splays_scope[i].operate(name, right_name, op);
        return var;
    }

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
            std::cout << data_1->data.get_int() << " < " << data_2->data.get_int() << std::endl;
            return data_1->data.get_int() < data_2->data.get_int();
        }
        if (data_1->size == 1){
            return data_1->data.get_char() < data_2->data.get_char();
        }
        return data_1->data.get_string() < data_2->data.get_string();
    }
    if (op == '~'){
        if (data_1->size == 4){
            std::cout << data_1->data.get_int() << " == " << data_2->data.get_int();
            bool data__ = (data_1->data.get_int() == data_2->data.get_int());
            std::cout << " -> " << data__ << std::endl; 

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
        std::cout  <<  " -> " << var.get_int() << std::endl;
    }
    else if (var_nodes->size == 1){
        std::cout <<  " -> " << var.get_char() << std::endl;
    }
    else { 
        std::cout  <<  " -> " << var.get_string() << std::endl;
    }
    return var;
}

util::DataTracker scope::getData(){
    return util::DataTracker();
}
