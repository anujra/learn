#pragma once
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <string.h>

using namespace std;

class Ad01 {

public:
    static void run(const std::string& in) {

        string line;
        ifstream myfile (in);
        int sum = 0;
        if (myfile.is_open())
        {
            while ( getline (myfile, line) )
            {
                cout << line << '\n';
                int len = line.length();
                for (int ix = 0; ix < len; ++ix)
                    if (isdigit(line[ix])) {
                        int tmp = atoi(&line[ix])*10;
                        sum += tmp;
                        std::cout << "sum: " << sum << "- " << tmp << std::endl; 
                        break;
                    }

                for (int ix = len-1; ix >=0; --ix) {
                    if(isdigit(line[ix])) {
                        sum += (atoi(&line[ix]));
                        std::cout << "sum: " << sum << "- " << (atoi(&line[ix])) << std::endl; 
                        break;
                    }
                }
            std::cout << "-----" << std::endl;
            }
            myfile.close();
        }

        std::cout << sum << std::endl;
        // open file

    }
};