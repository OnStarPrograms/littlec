#include <string>

class heap{
    std::string* charHeapData; //Stores Strings
    int* intHeapData; //Stores Ints

 public:
    heap(int size){
        charHeapData = new std::string[size];
        intHeapData = new int[size];
    };
    std::string removeData(std::string* place);
    std::string* insertData(std::string data);
    int removeData(int* place);
    int* insertData(int data);
};
