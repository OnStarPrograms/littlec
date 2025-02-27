#include "ll.h"
#include <iostream>

Data* search(Data* head, long int ID){
    Data* temp = head;
    if (temp == nullptr)
        return nullptr;
    while (temp->next != nullptr && temp->next->ID != ID)
        temp = temp->next;
    return temp;
}

bool LL::removeData(long int ID){
    Data* found = search(head, ID);
    if (found->next == nullptr)
        return false;

    Data* temp = found->next;
    found->next = temp->next;
    delete temp;
    return true;
};

long int LL::insertData(int data){
    Data* temp = new Data(data);
    if (head == nullptr){
        head = tail = temp;
        std::cout << "hi1" << std::endl;
        return temp->ID;
    };
    tail->next = temp;
    tail = temp;
    return temp->ID;
};

int* LL::find(long int ID){
    Data* found = search(head, ID);
    if (found != nullptr && found->ID == ID)
        return found->data;
    if (found->next == nullptr)
        return nullptr;
    return found->next->data;
};
