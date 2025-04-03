#include "memory_trees.h"

bool TrieMemory::insert(std::string var_name, void* data, int size){
    if (head == nullptr){
        head = new node();
        insert_helper(var_name, 0, data, size, head);
    }
    int i = 0;
    node* temp = find_node(var_name, i);
    return insert_helper(var_name, i, data, size, temp);
}

bool TrieMemory::insert(std::string var_name, util::type_wrapper data){
    if (head == nullptr){
        head = new node();
        insert_helper(var_name, 0, data.val, data.size, head);
    }
    int i = 0;
    node* temp = find_node(var_name, i);
    return insert_helper(var_name, i, data.val, data.size, temp);
}

bool TrieMemory::insert_helper(std::string var_name, int i, void* data, int size, node* temp_node){
    node* temp = new node();
    if (i == var_name.length()-1){
        if (temp_node->alphabet[var_name[i]-'a'] != nullptr){
            return false;
        }
        temp->flag = true;
        temp->data = util::type_wrapper(data);
        temp->size = size;
        temp->data.size = size;
    }
    temp_node->alphabet[var_name[i]-'a'] = temp;
    if (var_name.length()-1 > i){
        insert_helper(var_name, i+1, data, size, temp);
    }
    return true;
}


//void TrieMemory::delete_node(node* value){
//    ;
//};

node* TrieMemory::find_node(std::string var_name, int& i){
    node* temp = head;
    while(i < var_name.length()){
        if (temp->alphabet[var_name[i]-'a'] != nullptr){
            temp = temp->alphabet[var_name[i]-'a'];
        }
        else{
            break;
        }
        i++;
    }
    return temp;
}



util::type_wrapper TrieMemory::find(std::string var_name){
    node* temp = head;
    int i = 0;
    while(i < var_name.length()){
        if (temp->alphabet[var_name[i]-'a'] != nullptr){
            temp = temp->alphabet[var_name[i]-'a'];
        }
        else{
            break;
        }
        i++;
    }
    if (temp == nullptr){
        return util::type_wrapper();
    }
    return temp->data;
}

