#include <iostream>
#include <string>
#include "review.h"

void ReadStdIn2(){
    int count = 0;
    std::string temp = "z";
    
    while ((temp.compare("q") != 0)){
    std::cin >> temp;
    count++;
    };
    count--;
    
    std::cout << count;
    
};

