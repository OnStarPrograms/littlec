#include <string>
#include <cassert>
#include <limits.h>
#include <stdlib.h>

struct Data{
    long int ID;
    int* data;
    Data* next;
    Data(int data){
        this->data = new int(data);
        ID = (long int)(this->data);
        next = nullptr;
    }
};

class LL{
    Data* head;
    Data* tail;
  public:
    LL(){
        head = tail = nullptr;
    };
    bool removeData(long int ID);
    long int insertData(int data);
    Data* getLL(){return head;};
    int* find(long int ID);
};
