/*
 * Name: Mike Brandin   
 * Date Submitted: 12/02/2020
 * Assignment Name: Word Ladder
 */

#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <queue>
using namespace std;

vector<string> V; //words from wordlist05.txt
//Global variables for bfs distance, bfs predecessor, and neighboring nodes

//Should be unordered_map type
unordered_map<string, bool> visits;//store visited states
unordered_map<string, int> dist;//distance from source
unordered_map<string, string> pred;//predecessor state
unordered_map<string, vector<int>> nbrs;//vector of neighboring states


//Implement breadth-first search, refer to Lab 10

void breadthfirstSearch(string s, string t){
    visits[s] = true;
    dist[s] = 0;
    queue<string> unsearched;
    unsearched.push(s);
    string current = unsearched.front();
    int numLoops = 0;
    
    while ((!unsearched.empty()) && (pred[current] != t)) {
        if (numLoops != 0){
            current = unsearched.front();
        }
        unsearched.pop();
        for (int i : nbrs[current]){
            if (!visits[V[i]]){
        	    visits[V[i]] = true;
          	    dist[V[i]] = 1 + dist[current];
          	    pred[V[i]] = current;
        	    unsearched.push(V[i]);
            }
        }
        numLoops++;
    }
}


int binarySearch(int left, int right, string data){//recursive binary search algorithm from lab 4
    
    if (right >= left) { 
        int m = left + (right - left) / 2; 
        if (V[m] == data){
            return m; 
        }
        if (V[m] > data){
            return binarySearch(left, m - 1, data);
        }
        return binarySearch(m + 1, right, data); 
    } 
    
    return -1;
}

void checkNeighbors(void){//generate map of imported dictionary
    for (int i = 0; i < int(V.size()); i++){//loop through every word in dictionary
        vector<int> tempNbrs;//vector to insert into nbrs
        for (int alphabet = 97; alphabet < 123; alphabet++){//loop every letter of alphabet
            for (int letterPos = 0; letterPos < 5; letterPos++){//loop thru every letter in word
                string tempWord = V[i];
                tempWord[letterPos] = alphabet;//change a letter
                if (tempWord != V[i] && binarySearch(0, V.size() - 1, tempWord) != -1){//if word is found in dictionary add to temp nbrs vector
                    tempNbrs.push_back(binarySearch(0, V.size() - 1, tempWord));
                }
            }
        }
        nbrs[V[i]] = tempNbrs;
    }
}

void wordLadder(string s, string t, int &steps, vector<string> &p){//Implement this function

    ifstream infile;//create input file variable 
    infile.open("wordlist05.txt");//open file
    string temp;//temp to store words line by line
    
    while (getline(infile, temp)){//get line until end of file
        V.push_back(temp);//insert all words into vector
    }
    
    infile.close();//close file
    
    checkNeighbors();//check neighbors to generate map of the dictionary
    breadthfirstSearch(s, t);//perform breadthfirstSearch

    steps = dist[t];//set value of steps to distance of target node
  
    vector<string> tempVec;//vec to store indiv path
    string current = t;
    
    int i = 0;
    while (current != s && i < 100){//create path backwards then reverse 
        tempVec.push_back(current);
        current = pred[current];
        i++;
    }
    if (i <= 99){
        tempVec.push_back(s);
        
        for (auto i : tempVec){//push back all strings from tempVec to path vector
            p.push_back(i);
        }
    }
    else{
        steps = 0;
    }
}


int main(void)
{
  int steps = 0;
  string s, t;
  vector<string> path;
  
  cout << "Source: ";
  cin >> s;

  cout << "Target: ";
  cin >> t;

  wordLadder(s, t, steps, path);

  if (steps == 0)
  {
      cout << "No path!\n";
  }
  else
  {
      cout << "Steps: " << steps << "\n\n";
      for (int i=0; i<int(path.size()); i++)
      {
          cout << path[i] << endl;
      }
  }
  return 0;
}
