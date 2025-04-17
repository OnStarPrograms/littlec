#include "memory_trees.h"
#include <functional>

class scope{
    std::vector<TrieMemory> tries_scope; 
    std::vector<SplayMemory> splays_scope; 
    int scopelevel;
    util::DataTracker tracker;

  public:
    scope();

    void enter_scope();
    bool leave_scope();
    bool insert_var(std::string name, util::type_wrapper variable);
    util::DataTracker getData();
    util::type_wrapper get_var(std::string name);
    void print_var(std::string name);

    void increment_var(std::string name, int size);
    void decrement_var(std::string name, int size);
    bool operator()(std::string name, std::string right_name, char op);
};
