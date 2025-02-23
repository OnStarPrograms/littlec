#include "heap.h"
#include <stdexcept>

void swap(int *x, int *y);

int heap::removeData(int place){
    int returnval = intHeapData[place];
    intHeapData[place] = INT_MIN;
    while (place != 0 && intHeapData[parent(place)] > intHeapData[place])
    {
       swap(&intHeapData[place], &intHeapData[parent(place)]);
       place = parent(place);
    }

    assert(heap_size > 0);
    if (heap_size == 1)
    {
        heap_size--;
        return returnval;
    }

    intHeapData[0] = intHeapData[heap_size-1];
    heap_size--;
    heapifyInt(0);

    return returnval;
};


//Accepts Data, and returns pointer pointing to data.
int* heap::insertData(int& data){
    (heap_size < heap_capacity)?data=data:throw std::invalid_argument("Went over Capacity");

    // First insert the new key at the end

    int i = heap_size;
    intHeapData[i] = data;
    heap_size++;
    // Fix the min heap property if it is violated
    while (i != 0 && intHeapData[parent(i)] > intHeapData[i])
    {
       swap(&intHeapData[i], &intHeapData[parent(i)]);
       i = parent(i);
    } 
    data = i;
    return (intHeapData+i);
};

void heap::heapifyInt(int i){
    int l = left(i);
    int r = right(i);
    int smallest = i;
    if (l < heap_size && intHeapData[l] < intHeapData[i])
        smallest = l;
    if (r < heap_size && intHeapData[r] < intHeapData[smallest])
        smallest = r;
    if (smallest != i)
    {
        swap(&intHeapData[i], &intHeapData[smallest]);
        heapifyInt(smallest);
    }
}


void swap(int *x, int *y)
{
    int temp = *x;
    *x = *y;
    *y = temp;
}
