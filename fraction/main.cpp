#include <iostream>
#include "fraction.h"

int main(int argc, char* argv[]) {

std::cout << "Fraction" << std::endl;
    Fraction f1();
    Fraction f2(f1);    // copy constructor

    f1.dump(std::cout);


}	
