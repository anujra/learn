#pragma once
#include <ostream>
#include <iterator>
#include <algorithm>
#include <cstring>

template<class T>
class vector {
    T* data_;
    int size_;
    int cur_;

public:
    vector();
    ~vector();
    void push_back(const T& data);
    void push_front(const T& data);

    void dump(std::ostream& os);
};

template<class T>
vector<T>::vector() {
    data_ = new T[2];
    size_ = 2;
    cur_ = 0;
}

template<class T>
vector<T>::~vector() {
    delete[] data_;
}

template<class T>
void vector<T>::push_back(const T& t) {
    if (cur_ == size_) {
        T* tmp = new T[2* size_];

        //std::memcpy(dest, source, sizeof dest);
        std::memcpy(tmp, data_, sizeof(T)*size_);

        delete[] data_;
        size_ = 2 * size_;
        data_ = tmp;
    }

    data_[cur_++] = t;
}

template<class T>
void vector<T>::dump(std::ostream& os) {
    std::copy(data_, data_+size_, std::ostream_iterator<T>(os, " "));
    os << std::endl;
}