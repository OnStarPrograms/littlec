#include "../headers/scope.h"

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
bool scope::insert_var(std::string name, util::type_wrapper variable){
    bool var;
    var = (tries_scope[scopelevel].insert(name, variable))?true:false;
    splays_scope[scopelevel].insert(name, variable);
    return var;
}

bool scope::operator()(std::string name, std::string right_name, char op){
    bool var;
    var = (tries_scope[scopelevel].operate(name, right_name, op))?true:false;
    splays_scope[scopelevel].operate(name, right_name, op);
    return var;
}

util::type_wrapper scope::get_var(std::string name){
    util::type_wrapper var;
    for (int i = 0; i <= scopelevel; i++){
        
        splays_scope[i].find(name);
        
        var = tries_scope[i].find(name);
       
        if (var.has_data() != false){
            break;
        }
    }
    return var;
}

util::DataTracker scope::getData(){
    return util::DataTracker();
}
