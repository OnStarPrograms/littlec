#include "../headers/scope.h"
#include <iostream>

scope::scope(){
    scopelevel = 0;
    tracker = util::DataTracker::getInstance();
    tries_scope.push_back(TrieMemory(tracker));
    splays_scope.push_back(SplayMemory(tracker));
};

void scope::enter_scope(){
    scopelevel++;
    tracker.tick();
    tries_scope.push_back(TrieMemory(tracker));
//    tracker.tockTrie("enter scope");

    tracker.tick();
    splays_scope.push_back(SplayMemory(tracker));
//    tracker.tockSplay("enter scope");
}
bool scope::leave_scope(){
    if (scopelevel > 0){
        scopelevel--;
    tracker.tick();
        tries_scope.pop_back();
//    tracker.tockTrie("exit scope");
    tracker.tick();
        splays_scope.pop_back();
//    tracker.tockSplay("exit scope");
        return true;
    }
    return false;
}

void scope::decrement_var(std::string name, int size){
    util::type_wrapper var_node;
      int i = 0;
      for (; i <= scopelevel; i++){
        tracker.tick(); 
         splays_scope[i].find(name);
//        tracker.tockSplay("find");

        tracker.tick(); 
         var_node = tries_scope[i].find(name);
//        tracker.tockTrie("find");

         if (var_node.has_data() != false){
             break;
         }
     }
    //splays_scope[i].increment(name, size);
//    tracker.tick();
//    tracker.tockSplay("find");
    
    
//    tracker.tick();
    tries_scope[i].decrement(name, size);
//    tracker.tockTrie("decrement");
}


void scope::increment_var(std::string name, int size){
      util::type_wrapper var_node;
      int i = 0;
      for (; i <= scopelevel; i++){
        
//        tracker.tick();
         splays_scope[i].find(name);
//        tracker.tockSplay("find");
//        tracker.tick();
         var_node = tries_scope[i].find(name);
         
         if (var_node.has_data() != false){
             break;
         }
     }
    tries_scope[i].clear_tick();
    //splays_scope[i].increment(name, size);
//   tracker.tick();
//    tracker.tockSplay("find");
//   tracker.tick();
    tries_scope[i].increment(name, size);
//    tracker.tockTrie("increment");
}

bool scope::insert_var(std::string name, util::type_wrapper variable){
    bool var;
//   tracker.tick();
    var = (tries_scope[scopelevel].insert(name, variable))?true:false;
//        tracker.tockTrie("insert");
//   tracker.tick();
    splays_scope[scopelevel].insert(name, variable);
//    tracker.tockSplay("insert");
    return var;
}

bool scope::operator()(std::string name, std::string right_name, char op){
    bool var;
    

    node* data_1 = nullptr; 
    util::type_wrapper data_1_var;
     for (int i = 0; i <= scopelevel; i++){
//       tracker.tick();
         splays_scope[i].find(name);
//        tracker.tockSplay("find");

//       tracker.tick();
         data_1_var = tries_scope[i].find(name);
//        tracker.tockTrie("find");
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
//        tracker.tick();
         splays_scope[i].find(name);
//        tracker.tockSplay("find");
//       tracker.tick();
         data_2_var = tries_scope[i].find(right_name);
//        tracker.tockTrie("find");
         int j = 0;
         data_2 = tries_scope[i].find_node(right_name, j);

         if (data_2_var.has_data() != false){
             break;
         }
     }
    if (data_1_var.has_data() == false || data_2_var.has_data() == false)
        return false;
    if (op != '>' && op != '<' && op != '~' && op != '|'){
//       tracker.tick();
        var = (tries_scope[i].operate(name, right_name, op))?true:false;
        std::string operation = "operation";
        operation+=op;
//        tracker.tockTrie(operation);
//        tracker.tick();
        splays_scope[i].operate(name, right_name, op);
//        tracker.tockSplay(operation);
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
       
//        tracker.tick();
        splays_scope[i].find(name);
//        tracker.tockSplay("find");
//       tracker.tick();
        var = tries_scope[i].find(name);
//        tracker.tockTrie("find");
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
    for (auto i:tries_scope)
        tracker.update(i.getData());
    for (auto i:splays_scope)
        tracker.update(i.getData());
    return tracker;
}
