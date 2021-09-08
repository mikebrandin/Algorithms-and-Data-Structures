#include <iostream>
#include "List.h"
#include "Node.h"
#include "ListQueue.h"
#include "ListStack.h"


int main(){
    
    ListStack<char> stack3;
  char c[] = {'m', 'l', 'k', 'j', 'i', 'h', 'e', 'c', 'b', 'a', 'p', 'z'};
  for(int i = 0; i < 12; i++){
    stack3.push(c[i]);
  }
  stack3.print("list");
    
    // Use cout as usual
// cout << "Hello World";
stack3.print("list");
char test[12];
char test2[] = {'z', 'p', 'a', 'b', 'c', 'e', 'h', 'i', 'j', 'k', 'l', 'm'};
string bob;
// This section skips the info printout 
// section of the print function

for (int i=0; i<12;i++){
	// test[i] = stoi(bob);
	test[i] = bob.at(0);
		 stack3.push(test[i]);

	 stack3.push(test2[i]);

}
    
  stack3.print("list");

    
    return 0;
}