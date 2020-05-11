#pragma once

#include <iostream>
#include <ostream>
#include <random>
#include "NodeC.hpp"

using namespace std;

namespace DoublyLinkedList {
    template <typename T>
    class itr {
        private:
            typedef NodeC<T> Node;
            Node * pointer;
            
        public:
            itr(){ pointer = nullptr; }
            itr(Node * ptr) { this->pointer = ptr; }
            
            void operator ++(){
                this->pointer = this->pointer->next;
            }

            void operator ++(int n){
                for (int i = 0; i < n; ++i)
                    this->pointer = this->pointer->next;
            }

            void operator --(){
                this->pointer = this->pointer->prev;
            }

            void operator --(int n){
                for (int i = 0; i < n; ++i)
                    this->pointer = this->pointer->prev;
            }
            
            T operator * (){
                return this->pointer->value;
            }
            
            bool operator == (const itr & it){
                return this->pointer == it.pointer;
            }
            
            bool operator != (const itr & it){
                return this->pointer != it.pointer;
            }

            bool operator <= (const itr & it){
                return this->pointer <= it.pointer;
            }

            bool operator >= (const itr & it){
                return this->pointer >= it.pointer;
            }

            bool operator < (const itr & it){
                return this->pointer < it.pointer;
            }

            bool operator > (const itr & it){
                return this->pointer > it.pointer;
            }
    };
    
    template <typename T>
    class List {
        protected:
            typedef NodeC<T> Node;
            
            Node * head_pointer = nullptr;
            Node * tail_pointer = nullptr;
            unsigned int length = 0;

        public:
            typedef itr<T> iterator;
 
            List(List* List){ 
                Node * ptr = List.head_pointer;
                int i = 0;
                while (ptr != nullptr) {
                    push_f(List[i]->value);
                    ptr = ptr->next;
                    ++i;
                }
            }
 
            List(T *arr, int n){ 
                for(int i = 0; i < n; ++i) {
                    push_b(arr[i]);
                }
            }

            List(Node* singleNode){ 
                push_f(singleNode->value);
            }

            List(int n){ 
	            std::random_device dev;
	            std::mt19937 rng(dev());

                if (std::is_same<T, char>::value) {
                    static std::uniform_int_distribution<> dist26(0, 25);
                    for(int i = 0; i < n; ++i)
                        push_f('a' + dist26(rng));
                } else {
                    static std::uniform_real_distribution<> dist100(0, 100);
                    for(int i = 0; i < n; ++i)
                        push_f(dist100(rng));
                }
            }

            List(){ 
                head_pointer = nullptr;
                tail_pointer = nullptr;
                length = 0;
            }

            ~List(){
                while(!isEmpty()){ pop_f(); }
            }

            Node * front() { return head_pointer; }
            
            Node * back() { return tail_pointer; }; 
            
            void push_b(const T& content) {
                Node * new_node = new Node(content, nullptr, tail_pointer);
                if (head_pointer == nullptr) 
                    head_pointer = new_node;  
                else
                    tail_pointer->next = new_node;
                tail_pointer = new_node;
                ++length;
            }

            void push_f(const T& content) {
                Node * new_node = new Node(content, head_pointer, nullptr);
                if (head_pointer == nullptr)
                    tail_pointer = new_node;
                else
                    head_pointer->prev = new_node;
                head_pointer = new_node;
                ++length;
            }

            Node * pop_back() {
                Node * ptr = tail_pointer->prev;
                Node * tmp = tail_pointer;
                delete tail_pointer;
                tail_pointer = ptr;
                tail_pointer->next = nullptr;
                --length;
                return tmp;
            }

            Node * pop_f() {
                Node * ptr = head_pointer;
                head_pointer = ptr->next;
                if (length > 1)
                    head_pointer->prev = nullptr;
                delete ptr;
                --length;
                return ptr;
            }

            Node * operator[] (const int& pos) {
                Node * ptr = head_pointer;
                int i = 0;
                
                for (ptr = head_pointer; ptr != nullptr; ptr = ptr->next){
                    if (i == pos)
                        return ptr;
                    ++i;
                }

                return nullptr;
            }
            
            bool isEmpty() { 
                return head_pointer == nullptr; 
            }

            unsigned int size() { 
                return length; 
            }

            void clear() { 
                while(!isEmpty()){ pop_f(); } 
            }

            void erase(Node * ref) {
                Node * tmp = nullptr;
                if (ref == head_pointer) {
                    head_pointer = head->next;
                    head_pointer->prev = nullptr;
                    delete ref;
                    --length;
                    return;
                }
                for (Node * ptr = head_pointer; ptr != nullptr; ptr = ptr->next){
                    if (ptr->next == ref) {
                        tmp = ptr->next->next;
                        ptr->next = ptr->next->next;
                        tmp->prev = ptr;
                        if (ref == tail_pointer)
                            tail_pointer = ptr;
                        delete ref;
                        --length;
                        return;
                    }
                }
                cout << "Content not found" << endl;
            } 
            
            void insert(Node * ref, const T& content) {
                for (Node * ptr = head_pointer; ptr != nullptr; ptr = ptr->next){
                    if (ptr == ref) {
                        Node * new_node = new Node(content, ptr->next, ptr);
                        ptr->next = new_node;
                        ++length;
                        if (ref == tail_pointer)
                            tail_pointer = new_node;
                        return;
                    }
                }
                cout << "Content not found" << endl;
            }

            void remove(const T& content) {
                Node * tmp;
                for (Node * ptr = head_pointer; ptr != nullptr; ptr = ptr->next) { 
                    if (ptr->value == content) {
                        tmp = ptr->next;
                        erase(ptr);
                        ptr = tmp;
                    }
                }
            }

            void sort() {
                bool end; 
                Node * ptr; 
                Node * hold = nullptr; 
            
                do { 
                    ptr = head_pointer; 
                    end = false; 
            
                    while (ptr->next != hold) { 
                        if (ptr->value > ptr->next->value) {  
                            T tmp = ptr->value; 
                            ptr->value = ptr->next->value; 
                            ptr->next->value = tmp; 
                            end = true; 
                        } 
                        ptr = ptr->next; 
                    } 
                    hold = ptr;
                } while (end);
            } 

            void reverse() {
                Node * tmp = nullptr;
                for (Node * ptr = tail_pointer; head_pointer->next != nullptr; ptr = ptr->next) {
                    tmp = ptr->prev;
                    ptr->prev = ptr->next;
                    ptr->next = tmp;
                }
                tmp = head_pointer;
                head_pointer = tail_pointer;
                tail_pointer = tmp;
            }

            inline friend ostream& operator << (ostream &oss, const List &List) {
                Node * ptr = List.head_pointer;
                while (ptr != nullptr) {
                    oss << ptr->value << " ";
                    ptr = ptr->next;
                }
                return oss;
            }

            iterator begin(){
                return iterator(head_pointer);
            }
            
            iterator end() {
                return iterator(nullptr);
            }
    };
}