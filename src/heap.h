#include <string>
#include <cassert>
#include <limits.h>


class heap{
    int* intHeapData; //Stores Ints
    int heap_size;
    int heap_capacity;

 public:
    heap(int size){
        intHeapData = new int[size];
        heap_size = 0;
        heap_capacity = size;
    };
    int removeData(int place);
    int* insertData(int& data);
    void heapifyInt(int i);

    int parent(int i) { return (i-1)/2; }
    int left(int i) { return (2*i + 1); }
    int right(int i) { return (2*i + 2); }
};
