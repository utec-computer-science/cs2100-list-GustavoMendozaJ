// Node.h
#pragma once

template <typename T>
class Node {
    public:
        T value;
        Node<T> * next;

        Node(){ value = NULL; next = nullptr; }
        Node(T a, Node<T> * b) : value(a), next(b) {}

        ~Node(){ value = NULL; next = nullptr; }
};