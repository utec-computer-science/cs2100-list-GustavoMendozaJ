#pragma once

template <typename T>
class NodeC {
    public:
        T value;
        NodeC<T> * next;
        NodeC<T> * prev;

        NodeC(){ value = NULL; next = nullptr; prev = nullptr; }
        NodeC(T aa, Node2<T> * bb, Node2<T> * cc) : value(aa), next(bb), prev(cc) {}

        ~NodeC(){ value = NULL; next = nullptr; prev = nullptr; }
};