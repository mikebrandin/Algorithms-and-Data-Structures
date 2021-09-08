#include <iostream>
#include <string>
#include <vector>

#include "review.h"


std::vector <int> InitializeArray(int size){
    std::vector<int> result;
    result.reserve(size);
    
    for (int i = 0; i < size; i++){
        result[i] = 0;
        
    }
    
    return result;
};

int main(){
    return 0;
}