#include "doublyLinkedSwap.h"
#include <iostream>

using namespace std;

void swapWithNext(Node * p){
    
    struct Node *temp = p->next;//create a temp node
    
    if (temp != nullptr && temp->value != 0 && p->value != 0){//check if given edge node or dummy node
        Node *beforeP = p->prev;//node before p           
        Node *afterP = temp->next;//node after p

        temp->prev = p->prev;//connect previous pointers with node before
        p->next = temp->next;//connect next pointers with node after

        temp->next = p;//reconnect 
        p->prev = temp;

        beforeP->next = temp;//swap locations of temp and p

        afterP->prev = p;
        
    }
}



int main(){
    return 0;
}