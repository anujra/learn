#include <iostream>
#include "ad01.h"


int main(int argc, char* argv[]) {
    std::cout << "hello advent 2023" << std::endl;

    if (argc != 2) {
        std::cerr << "input required" << std::endl;
        return 1;
    }
        


    Ad01::run(argv[1]);


    return 0;
}