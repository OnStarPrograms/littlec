#include "utils.h"
#include <stdlib.h>
#include <string>

struct node{
    util::type_wrapper data;
    int size;
    bool flag;
    node** alphabet;
    node* left;
    node* right;
    node* top;
    std::string name;
    
    node(){
        flag = false;
        size = 0;
        data = util::type_wrapper();
        alphabet = (node**)malloc(sizeof(node*)*52);
        for (int i = 0; i < 52; i++){
            alphabet[i] = nullptr;
        }
        left = nullptr;
        right = nullptr;
        top = nullptr;
    }

    node(std::string splay){
        flag = false;
        size = 0;
        data = util::type_wrapper();
        alphabet = nullptr; 
        left = nullptr;
        right = nullptr;
        top = nullptr;
        name = splay;
    }

    ~node(){
        if (flag == true){
            data.clear_data();
        }
    }
};



class TrieMemory{
    node* head;
    util::DataTracker *track;

  public:
    TrieMemory(){
        head = nullptr; 
        track = util::DataTracker::getInstance();
    }
    ~TrieMemory(){
//        if (head == nullptr)
//            return;
//        for (int i = 0; i < 52; i++){
//            if (head->alphabet[i] != nullptr){
//                delete_node(head->alphabet[i]);
//            }
//        }
//        delete head;
    }
    bool insert(std::string var_name, void* data, int size);
    
    bool insert(std::string var_name, util::type_wrapper data);
    
    bool insert_helper(std::string var_name, int i, void* data, int size, node* temp_node);
    void delete_node(node* value);
    util::type_wrapper find(std::string);
    node* find_node(std::string var_name, int& i);
    

    bool operate(std::string one, std::string two, char op);
    void increment(std::string name){
        int* a = (int*)find(name).val;
        (*a)++;
    };
    void decrement(std::string name){
        int* a = (int*)find(name).val;
        (*a)--;
    };
    void increment(std::string name, int b){
        int* a = (int*)find(name).val;
        (*a)+=b;
    };
    void decrement(std::string name, int b){
        int* a = (int*)find(name).val;
        (*a)-=b;


    };
};

class SplayMemory{
    node* head;

  public:
    SplayMemory(){
        head = nullptr;
    }
    ~SplayMemory(){
//        delete_node(head);
    }
    void zig(node* temp);
    void zag(node* temp);
    void splay(node* found);
    node* find_node(std::string name);
    void delete_node(node* value);
    void insert(std::string name, util::type_wrapper data);
    util::type_wrapper find(std::string name);
    void operate(std::string one, std::string two, char op);
    void increment(std::string name){
        int* a = (int*)find(name).val;
        (*a)++;
    };
    void decrement(std::string name){
        int* a = (int*)find(name).val;
        (*a)--;
    };
    void increment(std::string name, int b){
        int* a = (int*)find(name).val;
        (*a)+=b;
    };
    void decrement(std::string name, int b){
        int* a = (int*)find(name).val;
        (*a)-=b;

    };
};

