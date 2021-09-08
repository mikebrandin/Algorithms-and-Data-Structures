#include "IntegerArrayQueue.h"
#include <iostream>

using namespace std;

bool IntegerArrayQueue::enqueue(int value){

    if ((back +2) % size == front){//queue is full
        return false;//do not enqueue
    }
    else {//queue is not full
        back = (back + 1) % size;//increment back 
        array[back] = value; //set value to back of array
        return true;//+++
    }
}

int IntegerArrayQueue::dequeue(){
    
    if ((back + 1) % size == front){//queue is empty
        return 0;//do not dequeue
    }
    else{//queue not empty
        int temp = array[front];//create a temp variable
        front = (front + 1) % size; //increment front
        return temp;//return value that WAS at front
    }
}


int main(){
    return 0;
}