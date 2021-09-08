#include <iostream>
#include <string>
#include <vector>

#include "review.h"

void ReadWrite(){
    std::string temp = "z";
    std::vector<std::string> input;

    while ((temp.compare("q") != 0)){
        
    std::cin >> temp;
    if ((temp.compare("q") != 0)){
    input.push_back(temp);
    }
    };

    for (auto i: input){
        std::cout << i << " ";

    }
    std::cout << std::endl;
    
    
};
