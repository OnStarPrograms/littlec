#include <string>
#include <vector>
#include <chrono>
#include <fstream>
#include <iostream>
#pragma once


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

    // no idea how I'm gonna test if this works lmao
// no idea how I'm gonna test if this works lmao

    class DataTracker{
        std::vector<std::pair<std::string, int>> timeLogTrie;
        std::vector<std::pair<std::string, int>> timeLogSplay;
    public:
        inline static int increment;
      /*
        std::vector<float> getTrieTimePerInsertion(){
            for (int i = 0; i < 50; i++){
                insertionTime.push_back((float) i);
            }
            return insertionTime;
        }
        std::vector<float> getSplayTimePerInsertion(){
            for (int i = 0; i < 50; i++){
                insertionTime.push_back((float) i);
            }
            return insertionTime;
        }
       */




        // std::chrono::time_point<std::chrono::system_clock> start, end;
        // using picoseconds = std::chrono::duration<long long, std::pico>;

        static DataTracker &getInstance() {
            static DataTracker mine;
            return mine;
        };
        void tick() {
            // constexpr auto N = 1000;
            // start = std::chrono::system_clock::now();
        }
        void inc() {
            increment++;
        }
        void tockTrie(std::string command) {
            // end = std::chrono::system_clock::now();
            // auto elapsed_seconds = picoseconds{start-end}/1000;
            // timeLogTrie.push_back({command, elapsed_seconds.count()});
            timeLogTrie.push_back({command, increment});
            increment = 0;
        }
        void tockSplay(std::string command) {
            //end = std::chrono::system_clock::now();
            // auto elapsed_seconds = picoseconds{start-end}/1000;
            // timeLogSplay.push_back({command, elapsed_seconds.count()});
            timeLogSplay.push_back({command, increment});
            increment = 0;
        }

        void writeToFile() {
            // The graph within the HTML file uses Chart.js
            // Issue: JS is stubborn about importing external data for safety reasons
            // To send c++ data to JavaScript code, we can parse the data as a JS variable
            // This piece of code writes a set of strings and creates a JS file using the class variables
            // When complete, this JS file is read as a variable within dataGraph.html
            std::string TrieGraphX = "var TrieGraphX = [";
            std::string TrieGraphY = "var TrieGraphY = [";
            std::string SplayGraphX = "var SplayGraphX = [";
            std::string SplayGraphY = "var SplayGraphY = [";
            std::string ender = "];\n";

            for (auto entry: timeLogTrie) {
                TrieGraphX = TrieGraphX + "\"" + entry.first + "\",";
                TrieGraphY = TrieGraphY + std::to_string(entry.second) + ",";
            }
            TrieGraphX.pop_back();
            TrieGraphY.pop_back();
            TrieGraphX += ender;
            TrieGraphY += ender;

            for(auto entry: timeLogSplay) {
                SplayGraphX = SplayGraphX + "\"" + entry.first + "\",";
                SplayGraphY = SplayGraphY + std::to_string(entry.second) + ",";
            }
            SplayGraphX.pop_back();
            SplayGraphY.pop_back();
            SplayGraphX += ender;
            SplayGraphY += ender;

            std::fstream os;
            os.open("./graph_data.js", std::ios::trunc | std::ios::out);
            if (!os) {
                std::cerr << "Error opening graph_data.js" << std::endl;
            }

            os << TrieGraphX;
            os << TrieGraphY;
            os << SplayGraphX;
            os << SplayGraphY;

            os.close();
        }
    };
    int DataTracker::increment = 1;
};
