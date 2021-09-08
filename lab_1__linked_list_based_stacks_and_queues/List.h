/*
 * Name: Mike Brandin   
 * Date Submitted:
 * Lab Section: 4 
 * Assignment Name: Lab 1
 */


#pragma once

#include <iostream>
#include <string>
#include "Node.h"
using namespace std;

//This class represents a linked list of node objects
//Do not modify anything in the class interface
template <class T>
class List{

 private:
  Node<T> * start; //pointer to the first node in this list
  int mySize;  //size (or length) of this list

 public:
  List();
  ~List();
  int size();
  bool empty();
  void insertStart(T);
  void insertEnd(T);
  void insertAt(T, int);
  void removeStart();
  void removeEnd();
  void removeAt(int);
  T getFirst();
  T getLast();
  T getAt(int);
  int find(T);

  //Print the name and this list's size and values to stdout
  //This function is already implemented (no need to change it)
  void print(string name){
    cout << name << ": ";
    cout << "size = " << size();
    cout << ", values = ";
    Node<T> * iterator = start;
    while(iterator != nullptr){
      cout << iterator->value << ' ';
      iterator = iterator->next;
    }
    cout << endl;
  }

}; //end of class interface (you may modify the code below)

//Implement all of the functions below
//Construct an empty list by initializig this list's instance variables
template <class T>
List<T>::List(){
    start = nullptr;
    mySize = 0;
}

//Destroy all nodes in this list to prevent memory leaks
template <class T>
List<T>::~List(){
    Node<T> * iterator = start;
    Node<T> * temp;
    
    while(iterator != nullptr){
        temp = iterator->next;
        delete iterator;
        iterator = temp;
    }
}

//Return the size of this list
template <class T>
int List<T>::size(){

    return mySize;
}

//Return true if this list is empty
//Otherwise, return false
template <class T>
bool List<T>::empty(){
    return start ? 0 : 1;
}

//Create a new node with value, and insert that new node
//into this list at start
template <class T>
void List<T>::insertStart(T value){//?
    
    Node<T> * newNode = new Node<T>(value);
    newNode->next = start;
    start = newNode;
    mySize++;
    
}

//Create a new node with value, and insert that new node
//into this list at end
template <class T>
void List<T>::insertEnd(T value){
    Node<T> * newNode =  new Node<T>(value);
    newNode->next = nullptr;
    
    if (!start){
        start = newNode;
    }
    
    else{
        Node<T> * iterator = start;
        while (iterator->next != nullptr){
            iterator = iterator->next;
        }
        iterator->next = newNode;
    }
    
    mySize++;

}


//Create a new node with value <value>, and insert that new node at position j
template <class T>
void List<T>::insertAt(T value, int j){
    Node <T> * newNode = new Node<T>(value);
    Node <T> * previous;
    Node <T> * current;
    
    current = start;
    int count = 0;

    if (start != nullptr){
        while (current->next != nullptr && count != j){
            previous = current;
            current = current->next;
            count++;
        }
        if (j == 0){
           insertStart(value); 
        }
        else if(current->next == NULL && j == size()+1){
            insertEnd(value);
        }
        else if(j > size() + 1){
            return;
        }
        else{
            previous->next = newNode;
            newNode->next = current;
        }
    }
    else{//list is empty/start doesnt exist
        start = newNode;
        newNode->next = nullptr;
    }

    mySize++;

}

//Remove node at start
//Make no other changes to list
template <class T>
void List<T>::removeStart(){
    Node<T>* temp = start;

    if (start == nullptr){
        return;
    }
    else{
    start = start->next;
    mySize--;
    }
    delete(temp);
}

//Remove node at end
//Make no other changes to list
template <class T>
void List<T>::removeEnd(){
  Node<T>* temp = start;
  Node<T>* prev = start;

    if (start == NULL){
        return;
    }
    else{
        while(temp->next != NULL){
            prev = temp;
            temp = temp->next;
        }
        mySize--;
        prev->next = NULL;
    }
        
}


//Remove node at position j
//Make no other changes to list
template <class T>
void List<T>::removeAt(int j){
    
    if (j == 0){
        removeStart();
    }
    else if (j == size()){
        removeEnd();
    }
    else if (j > size()){
        return;
    }
    else{

        Node<T> * curr = start;
        Node<T> * prev;
        
        mySize--;

        int count = 0;
        while (curr != nullptr){
            if (count == j){
                prev->next = curr->next;
                delete(curr);
         }
            prev = curr;
            curr = curr->next;
            count++;
        }

    }
    
}

//Return the value of the first node in the Linked List,
//If no first node, return the default constructed value: T()
template <class T>
T List<T>::getFirst(){
    if (start != nullptr){
        return start->value;
    }
    else{
        return T();
    }
}

//Return the value of the last node in the Linked List,
//If no first node, return the default constructed value: T()
template <class T>
T List<T>::getLast(){
    Node<T> * iterator = start;
    while (iterator->next != nullptr){
        iterator = iterator->next;
    }
    return iterator->value;
}



//Return the value of the node at position j in the Linked List,
//If no first node, return the default constructed value: T()
template <class T>
T List<T>::getAt(int j){
    Node<T> * iterator = start;
    int count = 0;
    while (iterator != nullptr){
        if(count == j){
            return (iterator->value);
        }
        iterator = iterator->next;
        count++;
    }
    return T();
}


//Return the position of the (first) node whose value is equal to the key
//Otherwise, return -1
template <class T>
int List<T>::find(T key){
    for(int i = 0; i < size(); i++){
        if (getAt(i) == key){
            return i;
        }
    }
    return -1;
}

