#include <iostream>
#include "Sorts.h"
#include <string>
#include <vector>




int main(){
    
//std::vector<std::string> stringTest {"earthlings","greetings","leader","me","take","to","yall","your"};
std::vector<std::string> stringTest2 {"greetings", "yall", "earthlings", "take", "me", "to", "your", "leader"};
std::vector<std::string> a = quickSort(stringTest2);

//std::vector<double> doubleTest{ 1.6, 1.2, 1.1, 1.5, 1.9, 1.3, 1.7, 1.4, 1.8 };

//std::vector<double> a = quickSort(doubleTest);


for (int i = 0; i < 8; i++){
    std::cout << a[i] << std::endl;
}

return 0;
}
