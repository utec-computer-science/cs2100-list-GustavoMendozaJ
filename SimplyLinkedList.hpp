#pragma once

#include <iostream>
#include <ostream>
#include <random>
#include "Node.hpp"

using namespace std;

namespace Symplelist {
    template <typename T>
    class itr {
        private:
            typedef Node<T> Node;
            Node * pointer;
            
        public:
            itr(){ 
                pointer = nullptr; 
            }

            itr(Node * ptr) { 
                this->pointer = ptr;
            }
            
            void operator ++(){
                this->pointer = this->pointer->next;
            }

            void operator ++(int n){
                for (int i = 0; i < n; ++i)
                    this->pointer = this->pointer->next;
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
            typedef Node<T> Node;
            
            Node * head_pointer = nullptr;
            Node * tail_pointer = nullptr;
            unsigned int length = 0;

        public:
            typedef itr<T> iterator;

            List(List* List){ 
                Node * ptr = List.head;
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

            // Randomized constructor of size n
            List(int n){ 
                // Generate random seed
	            std::random_device dev;
	            std::mt19937 rng(dev());

                // Generate distribution in range [0, 100]
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

            Node * front() { 
                return head_pointer; 
                }
  
            Node * back() { 
                return tail_pointer; 
                }; 
            
            void push_b(const T& content) {
                Node * new_node = new Node(content, nullptr);
                if (head_pointer == nullptr) 
                    head_pointer = new_node;
                else
                    tail_pointer->next = new_node;
                tail_pointer = new_node;
                ++length;
            }

            void push_f(const T& content) {
                Node * new_node = new Node(content, head_pointer);
                if (head_pointer == nullptr)
                    tail_pointer = new_node;
                head_pointer = new_node;
                ++length;
            }

            Node * pop_b() {
                Node * ptr = head_pointer;
                while (ptr->next->next != nullptr)
                {
                    ptr = ptr->next;
                }
                Node * tmp = ptr->next;
                delete ptr->next;
                ptr->next = nullptr;
                tail_pointer = ptr;
                --length;
                return tmp;
            }

            Node * pop_f() {
                Node * ptr = head_pointer;
                head_pointer = ptr->next;
                ptr->next = nullptr;
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
                if (ref == head_pointer) {
                    head_pointer = head->next;
                    delete ref;
                    --length;
                    return;
                }
                for (Node * ptr = head_pointer; ptr != nullptr; ptr = ptr->next){
                    if (ptr->next == ref) {
                        ptr->next = ptr->next->next;
                        if (ref == tail_pointer)
                            tail_pointer = ptr;
                        delete ref;
                        --length;
                        return;
                    }
                }
                cout << " Content not found" << endl;
            } 
            
            void insert(Node * ref, const T& content) {
                for (Node * ptr = head_pointer; ptr != nullptr; ptr = ptr->next){
                    if (ptr == ref) {
                        Node * new_node = new Node(content, ptr->next);
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
                push_f(tail_pointer->value);
                pop_b();
                for (Node * ptr = head_pointer; ptr->next != nullptr; ptr = ptr->next) {
                    insert(ptr, tail_pointer->value);
                    pop_b();
                }
            }; 

            inline friend ostream& operator << (ostream &os, const List &List) {
                Node * ptr = List.head_pointer;
                while (ptr != nullptr) {
                    os << ptr->value << " ";
                    ptr = ptr->next;
                }
                return os;
            }

            iterator begin(){
                return iterator(head_pointer);
            }
            
            iterator end() {
                return iterator(nullptr);
            }
    };
}