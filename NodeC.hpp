#pragma once

template <typename T>
class Node2 {
    public:
        T value;
        Node2<T> * next;
        Node2<T> * prev;

        Node2(){ value = NULL; next = nullptr; prev = nullptr; }
        Node2(T a, Node2<T> * b, Node2<T> * c) : value(a), next(b), prev(c) {}

        ~Node2(){ value = NULL; next = nullptr; prev = nullptr; }
};