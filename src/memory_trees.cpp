#include "../headers/memory_trees.h"


void operations(node* first, node* second, char op){
    int first_size = first->data.size;
    int second_size = second->data.size;

    if (first_size != second_size){
        return;
    }
    int first_int = 0;
    std::string first_string;
    char first_char = 0;

    int second_int = 0;
    std::string second_string;
    char second_char = 0;


    if (first_size == 4)
        first_int = first->data.get_int();
    else if (first_size == 1)
        first_char = first->data.get_char();
    else
        first_string = first->data.get_string();

    if (second_size == 4)
        second_int = second->data.get_int();
    else if (second_size == 1)
        second_char = second->data.get_char();
    else
        second_string = second->data.get_string();



    if (op == '+'){
        first_int += second_int;
        first_char += second_char;
        first_string += second_string;
    }
    else if (op == '-'){
        first_int -= second_int;
        first_char -= second_char;
    }
    else if (op == '/'){
        first_int /= second_int;
        first_char /= second_char;
    }
    else if (op == '*'){
        first_int *= second_int;
        first_char *= second_char;
    }

    first->data.clear_data();
    if (first_size == 4){
        first->data = util::type_wrapper(first_int);
    }
    else if (first_size == 1){
        first->data = util::type_wrapper(first_char);
    }
    else{
        first->data = util::type_wrapper(first_string);
    }


    
}


bool TrieMemory::insert(std::string var_name, void* data, int size){
    if (head == nullptr){
        head = new node();
        insert_helper(var_name, 0, data, size, head);
    }
    int i = 0;
    node* temp = find_node(var_name, i);
    return insert_helper(var_name, i, data, size, temp);
}

bool TrieMemory::operate(std::string one, std::string two, char op){
    int i = 0;
    node* first_node = find_node(one, i);
    i = 0;
    node* second_node = find_node(two, i);
    operations(first_node, second_node, op);
    return true;
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


void TrieMemory::delete_node(node* value){
    for (int i = 0; i < 52; i++){
        if (value->alphabet[i] != nullptr){
            delete_node(value->alphabet[i]);
        }
    }
    delete value;
};

node* TrieMemory::find_node(std::string var_name, int& i){
    node* temp = head;
    while(i < var_name.length()){
        if (temp != nullptr && temp->alphabet[var_name[i]-'a'] != nullptr){
            temp = temp->alphabet[var_name[i]-'a'];
        }
        else{
            break;
        }
        i++;
        track->inc();
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


void SplayMemory::zig(node* temp){
    node* left = temp->left;
    node* top = temp->top;

    if (temp->left != nullptr){
        temp->left = temp->left->right;
    }
    left->right = temp;
    if (temp == head){
        head = left;
    }
    temp->top = left;
    left->top = top;
};
void SplayMemory::zag(node* temp){
    node* right = temp->right;
    node* top = temp->top;

    if (temp->right != nullptr){
        temp->right = temp->right->left;
    }
    right->left = temp;
    if (temp == head){
        head = right;
    }
    temp->top = right;
    right->top = top;
};

node* SplayMemory::find_node(std::string name){
    node* temp = head;
    while (temp->name != name){
        if (temp->right != nullptr && temp->name < name){
            temp = temp->right;
        }
        else if (temp->left != nullptr && temp->name > name){
            temp = temp->left;
        }
        else{
            break;
        }
    }
    return temp;
}


util::type_wrapper SplayMemory::find(std::string name){
    node* temp = head;
    while (temp->name != name){
        if (temp->right != nullptr && temp->name < name){
            temp = temp->right;
        }
        else if (temp->left != nullptr && temp->name > name){
            temp = temp->left;
        }
        else{
            return util::type_wrapper();
        }
    }
    return temp->data;
}


void SplayMemory::splay(node* found){
    while (found->top != nullptr && found != head){
        node* temp = found->top;
        if (temp->left == found){
            zig(temp);
        }
        else if(temp->right == found){
            zag(temp);
        }
        else{
            break;
        }
    }
}

void SplayMemory::insert(std::string name, util::type_wrapper data){
    if (head == nullptr){
        head = new node(name);
        head->data = data;
        return;
    };
    
    node* temp = new node(name);
    temp->data = data;
   
    node* found = find_node(name);
    if (found->name < name){
        found->right = temp;
        temp->top = found;
    }
    else if (found->name > name){
        found->left = temp;
        temp->top = found;
    }
    else{
        delete temp;
        return;
    }
    splay(temp);
};

void SplayMemory::delete_node(node* value){
    if (value == nullptr)
        return;
    delete_node(value->left);
    delete_node(value->right);
//    delete value;
};

void SplayMemory::operate(std::string one, std::string two, char op){
    node* first_node = find_node(one);
    node* second_node = find_node(two);
    operations(first_node, second_node, op);
}
