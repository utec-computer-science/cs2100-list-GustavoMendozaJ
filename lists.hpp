#pragma once

#include<iostream>
#include <random>

using namespace std;

namespace List {
    template <typename T>
    class Node {
        public: 
            typedef T value_node;
            value_node value = NULL;
            

            Node(const value_node& l_value = NULL) : value(l_value) {}
            ~Node(){}

            value_node& operator*(){
                return value;
            }

            template <typename _T>
            inline friend ostream& operator<< (ostream& l_out, const Node<_T>& l_node){
             l_out << "Node: " <<  l_node.value;
                return l_out;
            }
    };

    

    // SinglyList Node
    template <typename T>
    class SimplyLinkedList : public Node<T> {
        public:
            typedef typename Node<T>::value_node value_node;
            SimplyLinkedList<T> * next_ptr = nullptr;

            SimplyLinkedList(const T& l_value = NULL) : Node<T>(l_value), next_ptr(nullptr) {}
            ~SimplyLinkedList(){}

            template <typename _T>
            inline friend ostream& operator<< (ostream& l_out, const SimplyLinkedList<_T>& l_node){
             l_out << "Node: [v: " <<  l_node.value << ", p: " << l_node.next << "]";
                return l_out;
            }
    };

    // DoublyList Node
    template <typename T>
    class DoublyLinkedList : public Node<T> {
        public:
            typedef typename Node<T>::value_node value_node;

            DoublyLinkedList<T> * next_ptr = nullptr;
            DoublyLinkedList<T> * prev_ptr = nullptr;

            DoublyLinkedList(const T& l_value = NULL) : Node<T>(l_value), next_ptr(nullptr), prev_ptr(nullptr) {}
            ~DoublyLinkedList(){}

            // Print doubly node information
            template <typename _T>
            inline friend ostream& operator<< (ostream& l_out, const DoublyLinkedList<_T>& l_node){
             l_out << "Node: [v: " <<  l_node.value << ", p_next: " << l_node.next << ", p_prev: " << l_node.prev << "]";
                return l_out;
            }
    };

    // CircularList Node
    template <typename T>
    class CircularLinkedList : public Node<T> {
        public:
            typedef typename Node<T>::value_node value_node;
            

            CircularLinkedList<T> * next_ptr = nullptr;

            CircularLinkedList(const T& l_value = NULL) : Node<T>(l_value), next_ptr(nullptr) {}
            ~CircularLinkedList(){}

            template <typename _T>
            inline friend ostream& operator<< (ostream& l_out, const CircularLinkedList<_T>& l_node){
             l_out << "Node: [v: " <<  l_node.value << ", p_next: " << l_node.next << "]";
                return l_out;
            }
    };

    //DoublyCircularList Node
    template <typename T>
    class DoublyCircularLinkedList : public Node<T> {
        public:
            typedef typename Node<T>::value_node value_node;
        
            DoublyCircularLinkedList<T> * next_ptr = nullptr;
            DoublyCircularLinkedList<T> * prev_ptr = nullptr;


            DoublyCircularLinkedList(const T& l_value = NULL) : Node<T>(l_value), next_ptr(nullptr), prev_ptr(nullptr) {}
            ~DoublyCircularLinkedList(){}

            template <typename _T>
            inline friend ostream& operator<< (ostream& l_out, const DoublyCircularLinkedList<_T>& l_node){
             l_out << "Node: [v: " <<  l_node.value << ", p_next: " << l_node.next << ", p_prev: " << l_node.prev << "]";
                return l_out;
            }
    };


    // List
    template <typename Node>
    class List{
    public:

        typedef Node node_list;
        typedef typename node_list::value_node value_node;
        typedef unsigned int list_size;
        
        class Itr{
            private:
                node_list * pointer = nullptr;

            public: 
                Itr(node_list* itr_pointer = nullptr) : pointer(itr_pointer) {}
                ~Itr() {}

                virtual bool operator!= (Itr it){ return pointer != it.pointer; }
                virtual value_node& operator* () { return **pointer; }

                void operator++ (void){
                    this->pointer = this->pointer->next; 
                }

                void operator ++(int n){
                    for (int i = 0; i < n; ++i)
                        this->pointer = this->pointer->next;
                }
        };

        protected:
            node_list *head = nullptr;
            node_list *tail = nullptr;

            template<int Node_type>
            void _push_front_(Node**&,Node**&,value_node);
            template<int Node_type2>
            void _push_back_(Node**&,Node**&,value_node);
            template<int Node_type3>
            node_list* _pop_front_(Node**&,Node**&);
            template<int Node_type4>
            node_list* _pop_back_(Node**&,Node**&);
            template<int Node_type5>
            void _insert_(Node**&,Node**&,Node*,value_node);
            template<int Node_type6>
            void _remove_(Node**&,Node**&,value_node);
            template<int Node_type7>
            void _erase_(Node**&,Node**&,Node*&);
            template<int Node_type8>
            void _reverse_(Node**&,Node**&);
            template<int Node_type9>
            void _clear_(Node**&,Node**&);
            template<int Node_type10>
            void _sort_(Node**&,Node**&);
            template<int Node_type11>
            list_size _size_(Node**&,Node**&);

        public:
            List(List &_list){ 
                node_list * ptr = _list.head;
                int i = 0;
                while (ptr != nullptr) {
                    push_front(_list[i]->value);
                    ptr = ptr->next;
                    ++i;
                    if (ptr == _list.head)
                        return;
                }
            }

            List(value_node *arr, int n){ 
                for(int i = 0; i < n; ++i) {
                    push_back(arr[i]);
                }
            }

            List(node_list * singleNode){ 
                push_front(singleNode->value);
            }

            List(int n){ 
	            std::random_device dev;
	            std::mt19937 rng(dev());
                
                if (std::is_same<value_node, char>::value) {
                    static std::uniform_int_distribution<> dist26(0, 25);
                    for(int i = 0; i < n; ++i)
                        push_front('a' + dist26(rng));
                } else {
                    static std::uniform_real_distribution<> dist100(0, 100);
                    for(int i = 0; i < n; ++i)
                        push_front(dist100(rng));
                }
            }


            List(void) : head(nullptr), tail(nullptr){}
            ~List (void){}
            
            void push_front(const value_node& element){
                node_list ** head_pointer = &head;
                node_list ** tail_pointer = &tail;
                _push_front_<NodeTraits<node_list,value_node>::Node_type>(head_pointer,tail_pointer,element);
            }

            void push_back(const value_node& element){
                node_list ** head_pointer = &head;
                node_list ** tail_pointer = &tail;
                _push_back_<NodeTraits<node_list,value_node>::Node_type>(head_pointer,tail_pointer,element);
            }

            node_list* pop_front(){
                node_list ** head_pointer = &head;
                node_list ** tail_pointer = &tail;
                return _pop_front_<NodeTraits<node_list,value_node>::Node_type>(head_pointer,tail_pointer);
            }

            node_list* pop_back(){
                node_list ** head_pointer = &head;
                node_list ** tail_pointer = &tail;
                return _pop_back_<NodeTraits<node_list,value_node>::Node_type>(head_pointer,tail_pointer);
            }

            void insert(node_t* ref, const value_node &element) {
                node_list ** head_pointer = &head;
                node_list ** tail_pointer = &tail;
                _insert_<NodeTraits<node_list,value_node>::Node_type>(head_pointer,tail_pointer,ref,element);
            }

            void remove(const value_node &element) {
                node_list ** head_pointer = &head;
                node_list ** tail_pointer = &tail;
                _remove_<NodeTraits<node_list,value_node>::Node_type>(head_pointer,tail_pointer,element);
            }

            void erase(node_t* &reference) {
                node_list ** head_pointer = &head;
                node_list ** tail_pointer = &tail;
                _erase_<NodeTraits<node_list,value_node>::Node_type>(head_pointer,tail_pointer,reference);
            }

            void clear() {
                node_list ** head_pointer = &head;
                node_list ** tail_pointer = &tail;
                _clear_<NodeTraits<node_list,value_node>::Node_type>(head_pointer,tail_pointer);
            }

            void sort() {
                node_list ** head_pointer = &head;
                node_list ** tail_pointer = &tail;
                _sort_<NodeTraits<node_list,value_node>::Node_type>(head_pointer,tail_pointer);
            }

            void reverse() {
                node_list ** head_pointer = &head;
                node_list ** tail_pointer = &tail;
                _reverse_<NodeTraits<node_list,value_node>::Node_type>(head_pointer,tail_pointer);
            }

            list_size size() {
                node_list ** head_pointer = &head;
                node_list ** tail_pointer = &tail;
                return _size_<NodeTraits<node_list,value_node>::Node_type>(head_pointer,tail_pointer);
            }

            Itr begin(){ return Itr(head); }

            Itr end(){ return Itr(tail); }

            value_node& front(void){ return head->value; }; 

            value_node& back(void){ return tail->value; };  

            // Random access
            node_list* operator[] (const int& _position){
                node_list * temp = head;
                for (int i = 0; i < _position; i++, temp = temp->next);
                return temp;
            }

            bool empty(void){ return head == nullptr; }

            inline friend ostream& operator<< (ostream& out, List<node_list>& _list){
                typename List<node_list>::Itr it = _list.begin();
                for(; it != _list.end(); ++it){
                    out << *it << " -> ";
                }
                out << *it << " -> ";
                return out;
            }

            List& operator<< (const value_node& _value){
                this->push_back(_value);
                return *this;
            }

            List& operator>> (const value_node& _value){
                this->push_front(_value);
                return *this;
            }
    };

    // Traits
    #define DEFAULT_NODE 0
    #define SINGLYLIST_NODE 1
    #define DOUBLYLIST_NODE 2
    #define CIRCULARLIST_NODE 3
    #define DOUBLYCIRCULARLIST_NODE 4

    template <typename T, typename TT>
    struct NodeTraits{ 
        static const int Node_type = DEFAULT_NODE; 
    };

    template <typename TT>
    struct NodeTraits< SimplyLinkedList<TT>, TT >{
        static const int Node_type = SINGLYLIST_NODE;
    };

    template <typename TT>
    struct NodeTraits< DoublyLinkedList<TT>, TT >{
        static const int Node_type = DOUBLYLIST_NODE;
    };

    template <typename TT>
    struct NodeTraits< CircularLinkedList<TT>, TT >{
        static const int Node_type = CIRCULARLIST_NODE;
    };

    template <typename NT>
    struct NodeTraits< DoublyCircularLinkedList<NT>, NT >{
        static const int Node_type = DOUBLYCIRCULARLIST_NODE;
    };
    

    template <typename Node, typename ValueNode, int Node_type>
    class LHelper{
        public:
            static void push_front(Node** &head, Node** &tail, ValueNode element){
                cout << "Trait not defined" << endl;
            }
            static void push_back(Node** &head, Node** &tail, ValueNode element){
                cout << "Trait not defined" << endl;
            }
            static Node* pop_front(Node** &head, Node** &tail){
                cout << "Trait not defined" << endl;
                return nullptr;
            }
            static Node* pop_back(Node** &head, Node** &tail){
                cout << "Trait not defined" << endl;
                return nullptr;
            }
            static void insert(Node** &head, Node** &tail, Node* ref, const ValueNode &element) {
                cout << "Trait not defined" << endl;
            }
            static void remove(Node** &head, Node** &tail, const ValueNode &element) {
                cout << "Trait not defined" << endl;
            }
            static void erase(Node** &head, Node** &tail, Node* &ref) {
                cout << "Trait not defined" << endl;
            }
            static void clear(Node** &head, Node** &tail) {
                cout << "Trait not defined" << endl;
            }
            static void sort(Node** &head, Node** &tail) {
                cout << "Trait not defined" << endl;
            }
            static void reverse(Node** &head, Node** &tail) {
                cout << "Trait not defined" << endl;
            }
            static unsigned int size(Node** &head, Node** &tail) {
                cout << "Trait not defined" << endl;
            }
    };

    template <typename Node, typename ValueNode>
    class LHelper<Node,ValueNode,SINGLYLIST_NODE>{
        public:
            static void push_front(Node** &head, Node** &tail, ValueNode element) {
                Node *new_node = new Node(element);
                if (!(*head)) {
                    *tail = new_node;
                    *head = new_node;
                } else {
                    new_node->next = *head;
                    *head = new_node;
                }
            }

            static void push_back(Node** &head, Node** &tail, ValueNode element){
                Node *new_node = new Node(element);
                if (!(*head))
                    *tail = *head = new_node;
                else {
                    (*tail)->next = new_node;
                    *tail = (*tail)->next;
                }
            }

            static Node* pop_front(Node** &head, Node** &tail) {
                Node *ret = new Node((*head)->value);
                Node *ptr = *head;
                *head = ptr->next;
                delete ptr;
                return ret;
            }

            static Node* pop_back(Node** &head, Node** &tail) {
                Node *ret = new Node((*tail)->value);
                Node *ptr = *head;
                while(ptr->next != (*tail)){
                    ptr = ptr->next;
                }
                *tail = ptr;
                delete (*tail)->next;
                (*tail)->next = nullptr;
                return ret;
            }

            static void insert(Node** &head, Node** &tail, Node* ref, const ValueNode &element) {
                for (Node *ptr = *head; ptr != nullptr; ptr = ptr->next){
                    if (ptr == ref) {
                        Node *new_node = new Node(element);
                        new_node->next = ptr->next;
                        ptr->next = new_node;
                        if (ref == *tail)
                            *tail = new_node;
                        return;
                    }
                }
                cout << "Reference not found" << endl;
            }

            static void remove(Node** &head, Node** &tail, const ValueNode &element) {
                Node * temp;
                for (Node * ptr = *head; ptr != nullptr; ptr = ptr->next) { 
                    if (ptr->value == element) {
                     temp = ptr->next;
                        erase(head, tail, ptr);
                        ptr = temp;
                    }
                }
            }

            static void erase(Node** &head, Node** &tail, Node* &ref) {
                if (ref == *head) {
                    *head = (*head)->next;
                    delete ref;
                    return;
                }
                for (Node *ptr = *head; ptr != nullptr; ptr = ptr->next){
                    if (ptr->next == ref) {
                        ptr->next = ptr->next->next;
                        if (ref == *tail)
                            *tail = ptr;
                        delete ref;
                        return;
                    }
                }
                cout << "Reference not found" << endl;
            } 

            static void clear(Node** &head, Node** &tail) { 
                while(*head != nullptr){ pop_front(head, tail); } 
            } 

            static void sort(Node** &head, Node** &tail) {
                bool fin; 
                Node * ptr; 
                Node * hold = nullptr; 
            
                do { 
                    ptr = *head; 
                    fin = false; 
            
                    while (ptr->next != hold) { 
                        if (ptr->value > ptr->next->value) {  
                            ValueNode temp = ptr->value; 
                            ptr->value = ptr->next->value; 
                            ptr->next->value = temp; 
                            fin = true; 
                        } 
                        ptr = ptr->next; 
                    } 
                    hold = ptr;
                } while (fin);
            }

            static void reverse(Node** &head, Node** &tail) {
                push_front(head, tail, (*tail)->value);
                pop_back(head, tail);
                for (Node * ptr = *head; ptr->next != nullptr; ptr = ptr->next) {
                    insert(head, tail, ptr, (*tail)->value);
                    pop_back(head, tail);
                }
            }

            static unsigned int size(Node** &head, Node** &tail){
                unsigned int i = 0;
                for (Node * temp = *head; temp != nullptr; i++, temp = temp->next);
                return i;
            }
    };

    template <typename Node, typename ValueNode>
        class LHelper<Node,ValueNode,DOUBLYLIST_NODE>{
        public:
            public:
            static void push_front(Node** &head, Node** &tail, ValueNode element) {
                Node *new_node = new Node(element);
                new_node->next = *head;
                if (*head == nullptr)
                    *tail = new_node;
                else
                    (*head)->prev = new_node;
                *head = new_node;
            }

            static void push_back(Node** &head, Node** &tail, ValueNode element){
                Node *new_node = new Node(element);
                new_node->prev = *tail;
                if (*head == nullptr)
                    *head = new_node;
                else
                    (*tail)->next = new_node;
                *tail = new_node;
            }

            static Node* pop_front(Node** &head, Node** &tail) {
                Node *ret = new Node((*head)->value);
                Node *ptr = *head;
                *head = ptr->next;
                if (*head != nullptr)
                    (*head)->prev = nullptr;
                delete ptr;
                return ret;
            }

            static Node* pop_back(Node** &head, Node** &tail) {
                Node *ret = new Node((*tail)->value);
                Node *ptr = (*tail)->prev;
                delete (*tail);
                (*tail) = ptr;
                (*tail)->next = nullptr;
                return ret;
            }

            static void insert(Node** &head, Node** &tail, Node* ref, const ValueNode &element) {
                for (Node *ptr = *head; ptr != nullptr; ptr = ptr->next){
                    if (ptr == ref) {
                        Node *new_node = new Node(element);
                        new_node->next = ptr->next;
                        new_node->prev = ptr;
                        ptr->next = new_node;
                        if (ref == *tail)
                            *tail = new_node;
                        return;
                    }
                }
                cout << "Reference not found" << endl;
            }

            static void remove(Node** &head, Node** &tail, const ValueNode &element) {
                Node * temp;
                for (Node * ptr = *head; ptr != nullptr; ptr = ptr->next) { 
                    if (ptr->value == element) {
                     temp = ptr->next;
                        erase(head, tail, ptr);
                        ptr = temp;
                    }
                }
            }

            static void erase(Node** &head, Node** &tail, Node* &ref) {
                Node * temp = nullptr;
                if (ref == *head) {
                    *head = (*head)->next;
                    (*head)->prev = nullptr;
                    delete ref;
                    return;
                }
                for (Node *ptr = *head; ptr != nullptr; ptr = ptr->next){
                    if (ptr->next == ref) {
                     temp = ptr->next->next;
                        ptr->next = ptr->next->next;
                     temp->prev = ptr;
                        if (ref == *tail)
                            *tail = ptr;
                        delete ref;
                        return;
                    }
                }
                cout << "Reference not found" << endl;
            } 

            static void clear(Node** &head, Node** &tail) { 
                while(*head != nullptr){ pop_front(head, tail); } 
            } 

            static void sort(Node** &head, Node** &tail) {
                bool fin; 
                Node * ptr; 
                Node * hold = nullptr; 
            
                do { 
                    ptr = *head; 
                    fin = false; 
            
                    while (ptr->next != hold) { 
                        if (ptr->value > ptr->next->value) {  
                            ValueNode temp = ptr->value; 
                            ptr->value = ptr->next->value; 
                            ptr->next->value = temp; 
                            fin = true; 
                        } 
                        ptr = ptr->next; 
                    } 
                    hold = ptr;
                } while (fin);
            }

            static void reverse(Node** &head, Node** &tail) {
                Node * temp = nullptr;
                for (Node * ptr = *tail; (*head)->next != nullptr; ptr = ptr->next) {
                 temp = ptr->prev;
                    ptr->prev = ptr->next;
                    ptr->next = temp;
                }
             temp = *head;
                *head = *tail;
                *tail = temp;
            }

            static unsigned int size(Node** &head, Node** &tail){
                unsigned int i = 0;
                for (Node * temp = *head; temp != nullptr; i++, temp = temp->next);
                return i;
            }
    };

    template <typename Node, typename ValueNode>
        class LHelper<Node,ValueNode,CIRCULARLIST_NODE>{
        public:
            public:

            static void push_front(Node** &head, Node** &tail, ValueNode element) {
                Node *new_node = new Node(element);
                new_node->next = *head;
                if (*head == nullptr)
                    *tail = new_node;
                *head = new_node;
                (*tail)->next = *head;
            }
 
            static void push_back(Node** &head, Node** &tail, ValueNode element){
                Node *new_node = new Node(element);
                new_node->next = *head;
                if (*head == nullptr) {
                    *head = new_node;
                    new_node->next = *head;
                } else
                    (*tail)->next = new_node;
                *tail = new_node;
            }

            static Node* pop_front(Node** &head, Node** &tail) {
                Node *ret = new Node((*head)->value);
                Node *ptr = *head;
                *head = ptr->next;
                ptr->next = nullptr;
                (*tail)->next = *head;
                delete ptr;
                if (ptr == *head) {
                    *head = nullptr;
                    *tail = nullptr;
                }
                return ret;
            }

            static Node* pop_back(Node** &head, Node** &tail) {
                Node *ret = new Node((*tail)->value);
                Node *ptr = *head;
                while (ptr->next->next != *head)
                    ptr = ptr->next;
                
                Node * temp = ptr->next;
                delete ptr->next;
                *tail = ptr;
                (*tail)->next = *head;
                return ret;
            }

            static void insert(Node** &head, Node** &tail, Node* ref, const ValueNode &element) {
                Node * ptr = *head;
                do {
                    if (ptr == ref) {
                        Node * new_node = new Node(element);
                        new_node->next = ptr->next;
                        ptr->next = new_node;
                        if (ref == *tail)
                            *tail = new_node;
                        return;
                    }
                    ptr = ptr->next;
                } while (ptr != *head);
                cout << "Reference not found" << endl;
            }

            static void remove(Node** &head, Node** &tail, const ValueNode &element) {
                Node * ptr = *head;
                Node * temp;
                do { 
                    if (ptr->value == element) {
                     temp = ptr->next;
                        erase(head, tail, ptr);
                        ptr = temp;
                    } else
                        ptr = ptr->next;
                } while (ptr != *head);
            }

            static void erase(Node** &head, Node** &tail, Node* &ref) {
                Node * ptr = *head;
                if (ref == *head) {
                    *head = (*head)->next;
                    (*tail)->next = *head;
                    delete ref;
                    return;
                }
                do {
                    if (ptr->next == ref) {
                        ptr->next = ptr->next->next;
                        if (ref == *tail)
                            *tail = ptr;
                        delete ref;
                        return;
                    }
                    ptr = ptr->next;
                } while (ptr != *head);
                
                cout << "Reference not found" << endl;
            } 

            static void clear(Node** &head, Node** &tail) { 
                while(*head != nullptr){ pop_front(head, tail); }
            } 

            static void sort(Node** &head, Node** &tail) {
                bool fin; 
                Node * ptr; 
                Node * hold = *head; 
            
                do { 
                    ptr = *head; 
                    fin = false; 
            
                    while (ptr->next != hold) { 
                        if (ptr->value > ptr->next->value) {  
                            ValueNode temp = ptr->value; 
                            ptr->value = ptr->next->value; 
                            ptr->next->value = temp; 
                            fin = true; 
                        } 
                        ptr = ptr->next; 
                    } 
                    hold = ptr;
                } while (fin);
            }

            static void reverse(Node** &head, Node** &tail) {
                push_front(head, tail, (*tail)->value);
                pop_back(head, tail);
                Node * ptr = *head;
                do {
                    insert(head, tail, ptr, (*tail)->value);
                    pop_back(head, tail);
                    ptr = ptr->next;
                } while (ptr != *head);
            }

            static unsigned int size(Node** &head, Node** &tail){
                unsigned int i = 0;
                if (*head != nullptr) {
                    Node * temp = *head;
                    do {
                        i++;
                     temp = temp->next;
                    } while  temp != *head);
                }
                return i;
            }
    };

    template <typename Node, typename ValueNode>
        class LHelper<Node,ValueNode,DOUBLYCIRCULARLIST_NODE>{
        public:
            public:
            static void push_front(Node** &head, Node** &tail, ValueNode element) {
                Node *new_node = new Node(element);
                new_node->next = *head;
                new_node->prev = *tail;
                if (*head == nullptr) {
                    *tail = new_node;
                    (*tail)->next = new_node;
                    (*tail)->prev = new_node;
                } else
                    (*head)->prev = new_node;
                *head = new_node;
                (*tail)->next = *head;
            }
            static void push_back(Node** &head, Node** &tail, ValueNode element){
                Node *new_node = new Node(element);
                new_node->next = *head;
                new_node->prev = *tail;
                if (*head == nullptr) {
                    *head = new_node;
                    new_node->next = *head;
                    new_node->prev = *head;
                } else
                    (*tail)->next = new_node;
                *tail = new_node;
            }

            static Node* pop_front(Node** &head, Node** &tail) {
                Node *ret = new Node((*head)->value);
                Node *ptr = *head;
                *head = ptr->next;
                if (*head != nullptr)
                    (*head)->prev = *tail;
                (*tail)->next = *head;
                delete ptr;
                if (ptr == *head) {
                    *head = nullptr;
                    *tail = nullptr;
                }
                return ret;
            }

            static Node* pop_back(Node** &head, Node** &tail) {
                Node *ret = new Node((*tail)->value);
                Node * ptr = (*tail)->prev;
                delete (*tail);
                *tail = ptr;
                (*tail)->next = *head;
                return ret;
            }

            static void insert(Node** &head, Node** &tail, Node* ref, const ValueNode &element) {
                Node * ptr = *head;
                do {
                    if (ptr == ref) {
                        Node * new_node = new Node(element);
                        new_node->next = ptr->next;
                        new_node->prev = ptr;
                        ptr->next = new_node;
                        if (ref == *tail)
                            *tail = new_node;
                        return;
                    }
                    ptr = ptr->next;
                } while (ptr != *head);
                cout << "Reference not found" << endl;
            }

            static void remove(Node** &head, Node** &tail, const ValueNode &element) {
                Node * ptr = *head;
                Node * temp;
                do { 
                    if (ptr->value == element) {
                     temp = ptr->next;
                        erase(head, tail, ptr);
                        ptr = temp;
                    } else
                        ptr = ptr->next;
                } while (ptr != *head);
            }

            static void erase(Node** &head, Node** &tail, Node* &ref) {
                Node * ptr = *head;
                Node * temp = nullptr;
                if (ref == *head) {
                    *head = (*head)->next;
                    (*head)->prev = *tail;
                    delete ref;
                    return;
                }
                do {
                    if (ptr->next == ref) {
                     temp = ptr->next->next;
                        ptr->next = temp;
                     temp->prev = ptr;
                        if (ref == *tail) {
                            (*tail) = ptr;
                            (*tail)->next = *head;
                        }
                        delete ref;
                        return;
                    }
                    ptr = ptr->next;
                } while (ptr != *head);
                
                cout << "Reference not found" << endl;
            } 

            static void clear(Node** &head, Node** &tail) { 
                while(*head != nullptr){ pop_front(head, tail); }
            } 

            static void sort(Node** &head, Node** &tail) {
                bool fin; 
                Node * ptr; 
                Node * hold = *head; 
            
                do { 
                    ptr = *head; 
                    fin = false; 
            
                    while (ptr->next != hold) { 
                        if (ptr->value > ptr->next->value) {  
                            ValueNode temp = ptr->value; 
                            ptr->value = ptr->next->value; 
                            ptr->next->value = temp; 
                            fin = true; 
                        } 
                        ptr = ptr->next; 
                    } 
                    hold = ptr;
                } while (fin);
            }


            static void reverse(Node** &head, Node** &tail) {
                Node * ptr = *tail;
                Node * temp = nullptr;
                do {
                 temp = ptr->prev;
                    ptr->prev = ptr->next;
                    ptr->next = temp;
                    ptr = ptr->next;
                } while ((*head)->next != *tail);

             temp = *head;
                *head = *tail;
                *tail = temp;
            }

            static unsigned int size(Node** &head, Node** &tail){
                unsigned int i = 0;
                if (*head != nullptr) {
                    Node * temp = *head;
                    do {
                        i++;
                     temp = temp->next;
                    } while  temp != *head);
                }
                return i;
            }
    };


    template<typename Node> template<int Node_type>
    void List<Node>::_push_front_(
        typename List<Node>::node_list ** &head, 
        typename List<Node>::node_list ** &tail, 
        typename List<Node>::value_node element){
    
        LHelper<List<Node>::node_list,List<Node>::value_node,Node_type>::push_front(head,tail,element);
    }

    template<typename Node> template<int Node_type>
    void List<Node>::_push_back_(
        typename List<Node>::node_list ** &head, 
        typename List<Node>::node_list ** &tail, 
        typename List<Node>::value_node element){
    
        LHelper<List<Node>::node_list,List<Node>::value_node,Node_type>::push_back(head,tail,element);
    }

    template<typename Node> template<int Node_type>
    Node* List<Node>::_pop_front_(
        typename List<Node>::node_list ** &head, 
        typename List<Node>::node_list ** &tail){
    
        return LHelper<List<Node>::node_list,List<Node>::value_node,Node_type>::pop_front(head,tail);
    }

    template<typename Node> template<int Node_type>
    Node* List<Node>::_pop_back_(
        typename List<Node>::node_list ** &head, 
        typename List<Node>::node_list ** &tail){
    
        return LHelper<List<Node>::node_list,List<Node>::value_node,Node_type>::pop_back(head,tail);
    }

    template<typename Node> template<int Node_type>
    void List<Node>::_insert_(
        typename List<Node>::node_list ** &head, 
        typename List<Node>::node_list ** &tail,
        typename List<Node>::node_list * ref,
        typename List<Node>::value_node element){
    
        LHelper<List<Node>::node_list,List<Node>::value_node,Node_type>::insert(head,tail,ref,element);
    }

    template<typename Node> template<int Node_type>
    void List<Node>::_remove_(
        typename List<Node>::node_list ** &head, 
        typename List<Node>::node_list ** &tail,
        typename List<Node>::value_node element){
    
        LHelper<List<Node>::node_list,List<Node>::value_node,Node_type>::remove(head,tail,element);
    }

    template<typename Node> template<int Node_type>
    void List<Node>::_erase_(
        typename List<Node>::node_list ** &head, 
        typename List<Node>::node_list ** &tail,
        typename List<Node>::node_list * &reference){
    
        LHelper<List<Node>::node_list,List<Node>::value_node,Node_type>::erase(head,tail,reference);
    }

    template<typename Node> template<int Node_type>
    void List<Node>::_clear_(
        typename List<Node>::node_list ** &head, 
        typename List<Node>::node_list ** &tail){
    
        LHelper<List<Node>::node_list,List<Node>::value_node,Node_type>::clear(head,tail);
    }

    template<typename Node> template<int Node_type>
    void List<Node>::_sort_(
        typename List<Node>::node_list ** &head, 
        typename List<Node>::node_list ** &tail){
    
        LHelper<List<Node>::node_list,List<Node>::value_node,Node_type>::sort(head,tail);
    }

    template<typename Node> template<int Node_type>
    void List<Node>::_reverse_(
        typename List<Node>::node_list ** &head, 
        typename List<Node>::node_list ** &tail){
    
        LHelper<List<Node>::node_list,List<Node>::value_node,Node_type>::reverse(head,tail);
    }

    template<typename Node> template<int Node_type>
    unsigned int List<Node>::_size_(
        typename List<Node>::node_list ** &head, 
        typename List<Node>::node_list ** &tail){
    
        return LHelper<List<Node>::node_list,List<Node>::value_node,Node_type>::size(head,tail);
    }

    typedef SimplyLinkedList<float> SINGLYLIST_NODE_t;
    typedef List<SINGLYLIST_NODE_t> singlylist_t;

    typedef DoublyLinkedList<float> DOUBLYLIST_NODE_t;
    typedef List<DOUBLYLIST_NODE_t> doublylist_t;

    typedef CircularLinkedList<float> CIRCULARLIST_NODE_t;
    typedef List<CIRCULARLIST_NODE_t> circularlist_t;

    typedef DoublyCircularLinkedList<float> DOUBLYCIRCULARLIST_NODE_t;
    typedef List<DOUBLYCIRCULARLIST_NODE_t> doublycircularlist_t;
}