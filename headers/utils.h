#include <string>
#include <vector>
#include <chrono>
/*
 * util::
 *  LinkedList
 *  - insert(N data)
 *  - getHead() -> N
 *  - popHead() -> N
 *  - getTail() -> N
 *  - popTail() -> N
 *
 *  queue
 *  - push(G data)
 *  - peek() -> G
 *  - pop() -> G
 *
 *  stack
 *  - push(G data)
 *  - peek() -> g
 *  - pop() -> g
 *
 * Stepan:
 *  Write a class that accepts a DataTracker Object, and builds a graph from that object
 *  
 *  DataTracker
 *  - getTimePerInsertion() -> std::vector<float>
 *
 */


namespace util{
    struct type_wrapper{
        void* val;
        int size;
    
        type_wrapper(){
            this->val = nullptr;
            size = 0;
        }
        type_wrapper(void* val){
            this->val = val;
        }
        type_wrapper(int val){
            int* temp = new int(val);
            this->val =(void*)temp;
            this->size = 4;
        }
        type_wrapper(char val){
            char* temp = new char(val);
            this->val =(void*)temp;
            this->size = 1;
        }
        type_wrapper(std::string val){
            std::string* temp = new std::string(val);
            this->val =(void*)temp;
            this->size = sizeof(val);
        }

        void clear_data(){
            free(val);
        }
    
        bool has_data(){
            return (val != nullptr);
        }
        int get_int(){
            return (*(int*)val);
        }
        bool get_bool(){
            return (*(bool*)val);
        }
        char get_char(){
            return (*(char*)val);
        }
        std::string get_string(){
            return (*(std::string*)val);
        }
    };


    template <typename N>
    class linkedlist{
        struct node{
            node* next;
            node* prev;
            N data;
            node(N data){
                this->data = data;
                this->next = nullptr;
                this->prev = nullptr;
            };
        };
        node* head;
        node* tail;
      public:
        linkedlist(){
            head = nullptr;
            tail = nullptr;
        };
        void insert(N data){
            node* temp = new node(data);
            if (head == nullptr){
                head = tail = temp;
                return;
            }
            tail->next = temp;
            temp->prev = tail;
            tail = temp;
        }
        N getHead(){
            if (tail == nullptr){
                return  *(new N());
            }
            return head->data;
        }
        N popHead(){
            node* temp = head;
            if (tail == nullptr){
                return  *(new N());
            }
            if (tail == head){
                N _temp = temp->data;
                delete temp;
                head = tail = nullptr;
                return _temp;
            }
            head = head->next;
            N _temp = temp->data;
            delete temp;
            head->prev = nullptr;
            return _temp;
        }
        N getTail(){
            if (tail == nullptr){
                return *(new N());
            }
            return tail->data;
        }
        N popTail(){
            node* temp = tail;
            if (tail == nullptr){
                return *(new N());
            }
            if (tail == head){
                N _temp = temp->data;
                delete temp;
                head = tail = nullptr;
                return _temp;
            }
            tail = temp->prev;
            tail->next = nullptr;
            N _temp = temp->data;
            delete temp;
            return _temp;
        }
    };
    
    template <typename G>
    class queue{
        linkedlist<G> base;
    
      public:
        void push(G data){
            base.insert(data);
        }
    
        G peek(){
            return base.getHead();
        }
        
        G pop(){
            return base.popHead();
        }
    };
    
    
    template<typename T>
    class stack{
        linkedlist<T> base;
    
      public:
        void push(T data){
            base.insert(data);
        }
    
        T peek(){
            return base.getTail();
        }
        
        T pop(){
            return base.popTail();
        }
    };

    // no idea how I'm gonna test if this works lmao
    class DataTracker{
        std::vector<pair<std::string, float>> insertionTime;
    public:
        /* placeholder
        std::vector<float> getTimePerInsertion(){
            for (int i = 0; i < 50; i++){
                insertionTime.push_back((float) i);
            }
            return insertionTime;
        }
        */
        std::chrono::time_point<std::chrono::system_clock> start, end;
        void tick() {
            start = std::chrono::system_clock::now();
        }
        void tock(std::string command) {
            end = std::chrono::system_clock::now();
            std::chrono::duration<float> elapsed_seconds = end - start;
            insertionTime.push_back(command, elapsed_seconds.count());
        }
        void writeToFile() {
            // create a txt file if it doesn't exist already
            // write each pair of string + float to a line in CSV format
            // will it be sorted? i dunno lmao

        }
    };
};
