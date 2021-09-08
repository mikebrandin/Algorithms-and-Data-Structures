#include "review.h"
#include <iostream>

int Fibonacci(int a){
  int fibnum[a];
  fibnum[0] = 1;
  fibnum[1] = 1;


  
  if (a > 1){
  fibnum[a] = Fibonacci(a-1) + Fibonacci(a-2); 
  }
  
  return fibnum[a];  
};

