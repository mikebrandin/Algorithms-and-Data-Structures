#include <iostream>
#include "review.h"

//I am getting a warning for including "#pragma once" in main which you can see, is not the case
//You can only submit more than one file by submitting the folder, and mimir's grader than compiles
//the header file as if it were a main file. Weird.

int main(){
    ReadWrite();
    return 0;
}