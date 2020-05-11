// Node.h
#pragma once

template <typename T>
class Node {
    public:
        T value;
        Node<T> * next;

        Node(){ value = NULL; next = nullptr; }
        Node(T aa, Node<T> * bb) : value(aa), next(bb) {}

        ~Node(){ value = NULL; next = nullptr; }
};