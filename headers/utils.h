#include <string>
#include <vector>
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

    class DataTracker{
        std::vector<float> insertionTime;
      public:
        std::vector<float> getTimePerInsertion(){
            for (int i = 0; i < 50; i++){
                insertionTime.push_back((float) i);
            }
            return insertionTime;
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
        int _size = 0;
    
      public:
        void push(G data){
            base.insert(data);
            _size++;
        }
    
        G peek(){
            return base.getHead();
        }
        
        G pop(){
            _size--;
            return base.popHead();
        }
        int size(){
            return _size;
        }
    };
    
    
    template<typename T>
    class stack{
        linkedlist<T> base;
        int _size = 0;
    
      public:
        void push(T data){
            base.insert(data);
            _size++;
        }
    
        T peek(){
            return base.getTail();
        }
        
        T pop(){
            _size--;
            return base.popTail();
        }
        int size(){
            return _size;
        }
    };

    template<typename T>
    class dequeue{
        linkedlist<T> base;
        int _size = 0;
    
      public:
        void push(T data){
            base.insert(data);
            _size++;
        }
    
        T peek_tail(){
            return base.getTail();
        }
        
        T pop_tail(){
            _size--;
            return base.popTail();
        }
        T peek_head(){
            return base.getHead();
        }
        
        T pop_head(){
            _size--;
            return base.popHead();
        }
        int size(){
            return _size;
        }
    };
};
