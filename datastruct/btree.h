#pragma once
#include <iostream>

class node {
public:
    int data_;
    node* lft_ = nullptr;
    node* rht_ = nullptr;
};


template<class T>
class nodeT {
public:
    T data_;
    nodeT<T>* lft_ = nullptr;
    nodeT<T>* rht_ = nullptr;
};