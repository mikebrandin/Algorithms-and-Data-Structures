/*
 * Name: Mike Brandin
 * Date Submitted: 10/21/2020  
 * Assignment Name: single-word anagram finder
 */

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <unordered_map>


using namespace std;

vector<string> loadWordlist(string filename);

/*Implement the following function:
  anagram() takes a word (string) and a wordlist of all words (vector of strings)
  and builds a dictionary/map where the key is a specific number of times each
  letter occurs in a word and the associated value is a vector of strings
  containing all words using those letters (anagrams).
  The value returned is a vector of strings containing the corresponding
  set of anagrams
*/
vector<string> anagram(string word, vector<string> wordlist);

int main()
{
    vector<string> words;
    vector<string> anagrams;
    string inputWord;
    words=loadWordlist("wordlist.txt");
    cout << "Find single-word anagrams for the following word: ";
    cin >> inputWord;
    anagrams = anagram(inputWord, words);
    
    for (int i=0; i<int(anagrams.size()); i++)
    {
        cout << anagrams[i] << endl;
    }
    return 0;
}

vector<string> loadWordlist(string filename)
{
    vector<string> words;
    ifstream inFile;
    string word;
    inFile.open(filename);
    if(inFile.is_open())
    {
        while(getline(inFile,word))
        {
            if(word.length() > 0)
            {
                words.push_back(word);
            }
        }
        inFile.close();
    }
    return words;
}

long long hasher(string const& word) {//function counts number of each letter in string and outputs a unique hash value for this sequence
    long long hash = 0;
    long long charWeight = 1;
    const int modulus = 1e8 + 9;
    for (char c : word) {//iterate thru each character in the word
        hash = (hash+(c-'a'+1)*charWeight) % modulus;
        charWeight = (charWeight * 31) % modulus;
    }
    return hash;
}

//Implement this function
vector<string> anagram(string word, vector<string> wordlist)
{
    //hash<string> stringHash;
    unordered_map<int, vector<string>> dict;//created hash table with integer keys and vector of string values
    sort(word.begin(), word.end());//sort word 

    for (int i = 0; i < int(wordlist.size()); i++){//loop through length of the wordlist
        string temp(wordlist[i]);//temp string to store each word
        sort(temp.begin(), temp.end());//sort the word

    
        if (dict.find(hasher(temp)) == dict.end()){//if anagram is already in dictionary
            vector<string> vec;
            vec.push_back(wordlist[i]);
            dict.insert(make_pair(hasher(temp), vec));//add dictionary entry to hash address with vector of anagraa
        }
        else{//if anagram is not in dictionary yet
            vector<string> vec(dict[hasher(temp)]);
            vec.push_back(wordlist[i]);//add word to vector
            dict[hasher(temp)] = vec;//add new dictionary entry

        }
    
    }
    
    return dict[hasher(word)];//return the dictionary entry at the word's hash address

}







