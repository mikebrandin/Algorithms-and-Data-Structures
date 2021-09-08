/*
 * Name: Mike Brandin
 * Date Submitted: 9/28/2020
 * Lab Section: 4
 * Assignment Name: Lab 4
 */

#pragma once

#include <vector>

template <class T>
int linearSearch(std::vector<T> data, T target){
    for (int i = 0; i < data.size(); i++){
        if (data[i] == target){
            return i;
        }
    }
    return -1;
}


template <class T>
int binarySearch(std::vector<T> data, T target){
    int first = 0;
    int last = data.size() - 1;
    int mid = 0;
    
    while (first <= last){
        mid = first + (last - first) / 2;

        if (data[mid] < target){
            first = mid + 1;
        }
        else if (data[mid] > target){
            last = mid - 1;
        }
        else{
            return mid;
        }
    }
    
    return -1;
}
