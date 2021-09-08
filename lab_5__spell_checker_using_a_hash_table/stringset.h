/*
 * Name: Mike Brandin
 * Date Submitted: 10/12/2020
 * Lab Section: 4
 * Assignment Name: Lab 5
 */
 
#pragma once

#include <string>
#include <vector>
#include <list>
#include <functional>

using namespace std;

//Stringset class, do not modify definitions for existing members
class Stringset
{
    private:
        vector<list<string>> table;
        int num_elems;
        int size;
    public:
        Stringset();
        vector<list<string>> getTable() const;
        int getNumElems() const;
        int getSize() const;
        void insert(string word);
        bool find(string word) const;
        void remove(string word);
};