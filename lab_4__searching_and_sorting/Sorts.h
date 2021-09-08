/*
 * Name: Mike Brandin
 * Date Submitted: 9/28/2020
 * Lab Section: 4
 * Assignment Name: Lab 4
 */


#pragma once

#include <vector>

template <class T>
std::vector<T> merge(std::vector<T>  lVec, std::vector<T>  rVec)
{
   std::vector<T> output;
   while (lVec.size() > 0 || rVec.size() > 0) {
        if (lVec.size() > 0 && rVec.size() > 0) {
            if (lVec.front() <= rVec.front()) {
                output.push_back(lVec.front());
                lVec.erase(lVec.begin());
            } 
            else {
                output.push_back(rVec.front());
                rVec.erase(rVec.begin());
            }
        }  
        else if ((int)lVec.size() > 0) {
            for (long unsigned int i = 0; i < lVec.size(); i++){
                output.push_back(lVec[i]);
            }
            break;
        }  
        else if ((int)rVec.size() > 0) {
            for (long unsigned int i = 0; i < rVec.size(); i++){
                output.push_back(rVec[i]);
            }
            break;
        }
   }
   return output;
}

template <class T>
std::vector<T> mergeSort(std::vector<T> lst){

    //std:: cout << lst.size() << std::endl;
   if (lst.size() <= 1){
      return lst;
   }
   else{
 
        std::vector<T> temp; 
        std::vector<T> temp2;
       long unsigned int mid = (lst.size()+ 1) / 2;
     
       for (long unsigned int i = 0; i < mid; i++) {//push the front half of the vector into temp
            //std:: cout << "test" << std::endl;
            temp.push_back(lst[i]);
       }
    
       for (long unsigned int i = mid; i < lst.size(); i++) {//push the back half of the vector into temp2
            //std:: cout << i << std::endl;
            temp2.push_back(lst[i]);
       }
     
       temp = mergeSort(temp);
       temp2 = mergeSort(temp2);
    
       return merge(temp, temp2);
   }
}
template<class T> 
void swap(T& left, T& right){
  T tmp(left);
  left = right;
  right = tmp;
}

template <class T>
int partition(std::vector<T> & lst, int tempFirst, int tempLast, int pos){//partition vector into two and return index of pivot

	swap(lst[tempFirst], lst[pos]);//swap pivot with first index

	int first = tempFirst + 1;
	int last = tempLast;
	
	while (first < last){//partition 
		if (lst[first] < lst[tempFirst]){
			first++;
		}
		else if (lst[--last] < lst[tempFirst]){
			std::swap(lst[first], lst[last]);//swap values of  vector to approppriate array
		}
	}
	
	std::swap(lst[tempFirst], lst[--first]);//swap pivot to original location
	
	return first;
}

template <class T>
std::vector<T> quickSort2(std::vector<T> & lst, int first, int last){

	if (first >= last){	//if vector has less than two elements
		return lst;
	}
	
	int indexP = (first + last) / 2;//choose index for pivot(can vary)
	indexP = partition(lst, first, last, indexP);//parition vector

	if (first < indexP){
	   quickSort2(lst, first, indexP);//recursively call this function(first half of vector)
	}
	if (indexP < last){//recursively call this function(second half of vector)
		quickSort2(lst, indexP + 1, last);
	}
	
	return lst;
}

template <class T> 
std::vector<T> quickSort(std::vector<T> lst){

	if (lst.size() > 1){//check for valid size of vector
		return quickSort2(lst, 0, lst.size());//call primary recursive function
	}
	
	return lst;//return sorted vector
}

