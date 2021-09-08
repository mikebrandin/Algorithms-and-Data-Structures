/*
 * Name: Mike Brandin
 * Date Submitted: 10/12/2020
 * Lab Section: 4
 * Assignment Name: Lab 5
 */

#include "stringset.h"
#include <iostream>

Stringset::Stringset() : table(4), num_elems(0), size(4) {}

//Used in test cases and testStringset() in main.cpp, do not modify
vector<list<string>> Stringset::getTable() const
{
    return table;
}

//Used in test cases and testStringset() in main.cpp, do not modify
int Stringset::getNumElems() const
{
    return num_elems;
}

//Used in test cases and testStringset() in main.cpp, do not modify
int Stringset::getSize() const
{
    return size;
}

//Implement this function
void Stringset::insert(string word)
{
    hash<string> stringHash;
    
    bool duplicate = false;
    
    if (find(word)){//if word is already in the list do not add it to the list
        duplicate = true;
        return;
    }
    
    if (num_elems + 1 == size){//if vector is full, double its size
        int index; 
        vector<list<string>> temp(size * 2);   
        
        for (int i = 0; i < size; i++){//loop through vector  
            for (auto j = table[i].begin(); j != table[i].end(); j++){//iterate through linked list
 
                index = stringHash(*j) % (size * 2);//find index by hashing each list node
                temp[index].push_back(*j);//push to back of propper index in vector
            }
        } 
        
        table = temp;
        size = size * 2;//double value of size

    }
    

    
    if (!duplicate){//push to back of array
        table[stringHash(word) % size].push_back(word);
        num_elems = num_elems + 1;//update number of elements
    }
    
}
//Implement this function
bool Stringset::find(string word) const
{
    hash<string> stringHash;
    bool found = false;

    for (auto const& i : table[stringHash(word) % size]) {//iterate through proper list
        if (word.compare(i) == 0){//if a word matches return true
            found = true;
            return found;
        }  
    }
    
    return found;//returns false if word is not in the stringset
}

//Implement this function
void Stringset::remove(string word)
{
    hash<string> stringHash;

    if (find(word)){//if word is in the stringset remove it 
        table[stringHash(word) % size].remove(word);
        num_elems = num_elems - 1;//decrement number of elements
        
    }
}




