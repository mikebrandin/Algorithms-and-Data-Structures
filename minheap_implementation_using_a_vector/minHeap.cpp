/*
 * Name: Mike Brandin
 * Date Submitted: 11/16/20
 * Assignment Name: minHeap
 */

#include "minHeap.h"
#include <iostream>


void minHeap::siftUp(int pos){
    
    if (pos == 0){//base case; break recursion when the parameter is 0
        return;
    }
    
    int par = (pos - 1) / 2;//parent node

    if(heap[par] > heap[pos]){//swap element with its parent as long as the pos index value is less than its parent
        int temp = heap[par];
        heap[par] = heap[pos];
        heap[pos] = temp;
        siftUp(par);
    }
}

void minHeap::siftDown(int pos){
    
    int rightPos = 2 * pos + 2;//right node
    int leftPos = 2 * pos + 1;//left node

    if (leftPos >= int(heap.size())){//base case; if left position is a leaf node, break recusion
        return;
    }
    
    int min = pos;

    if (heap[pos] > heap[leftPos]){//if left node violates heap property
        min = leftPos;
    }
    
    if ((rightPos < int(heap.size())) && (heap[min] > heap[rightPos])){//if right node violates heap property
        min = rightPos;
    }

    if (min != pos){//swap spots and recurse
        int temp = heap[pos];
        heap[pos] = heap[min];
        heap[min] = temp;
        siftDown(min);
    }
    
}


minHeap::minHeap(vector<int> data){//create a heap from the ground up from given array
    
    for (int i = data.size() - 1; i >= 0; i--){
        insert(data[i]);//call insert with values
        siftDown(i);//sift down to maintain heap property
    }
}

void minHeap::insert(int value){//insert a value into the heap
    
   heap.push_back(value);//push back value into vector
   siftUp(heap.size() - 1);//sift up for the height

}

int minHeap::removeMin(){//Removes minimum value
    int temp = -1;//if this value is returned, there is an error
    
    if (heap.size()){//if size of heap is not 0

        temp = heap[0];//keep min value

        heap[0] = heap[heap.size() - 1];
        
        heap.pop_back();//remove min
        
        siftDown(0);//call sift down to maintain heap property
    }
    
    return temp;//return min value
}

int main(){
    
    vector<int> input={1,2,3,4,5,6,7,8,9,10};
    vector<int> test={1,2,3,4,5,6,7,8,9,10};
    vector<int> heapTest;
    
    for (int i=9; i>0; i--) swap(input[i], input[rand()%i]);
    minHeap h(input);
    
    for (int i=0; i<10; i++) heapTest.push_back(h.removeMin());
    
    for (int i=0; i<10; i++){
      heapTest.push_back(h.removeMin());
      cout << heapTest[i] << endl;
        
    }
        
        
    return 0;
}