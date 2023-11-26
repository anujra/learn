#pragma once
#include <ostream>>

class Fraction {
protected:
    int num_;
    int dnum_;

public:
Fraction();
Fraction(int n, int d) : num_(n), dnum_(d) {};


void dump(std::ostream& os, bool pretty = false) const {
    os << num_ << "/" << dnum_ << std::endl;
    //this->
}

};
