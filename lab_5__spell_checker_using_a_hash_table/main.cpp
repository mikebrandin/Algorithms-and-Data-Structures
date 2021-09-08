/*
 * Name: Mike Brandin
 * Date Submitted: 10/12/2020
 * Lab Section: 4
 * Assignment Name: Lab 5
 */
 
 #include "stringset.h"
 #include <iostream>
 #include <fstream>
 
 void testStringset(Stringset& words);
 void loadStringset(Stringset& words, string filename);
 vector<string> spellcheck(const Stringset& words, string word);
 
 int main()
 {
    Stringset wordlist;

    testStringset(wordlist);
    return 0;
 }
 
 void testStringset(Stringset& words)
 {
     string choice;
     string word;
     do
     {
         cout << "I: insert word" << endl;
         cout << "F: find word" << endl;
         cout << "R: remove word" << endl;
         cout << "P: print words in stringset" << endl;
         cout << "Q: quit" << endl;
         cin >> choice;
         switch (choice[0])
         {
             case 'I':
             case 'i':
                cout << "Enter word to insert: ";
                cin >> word;
                words.insert(word);
                break;
             case 'F':
             case 'f':
                cout << "Enter word to find: ";
                cin >> word;
                if (words.find(word))
                {
                    cout << word << " in stringset" << endl;
                }
                else
                {
                    cout << word << " not in stringset" << endl;
                }
                break;
             case 'R':
             case 'r':
                cout << "Enter word to remove: ";
                cin >> word;
                words.remove(word);
                break;
             case 'P':
             case 'p':
                vector<list<string>> t = words.getTable();
                int numWords = words.getNumElems();
                int tSize = words.getSize();
                for(int i=0; i<tSize; ++i)
                {
                    list<string>::iterator pos;
                    for (pos = t[i].begin(); pos != t[i].end(); ++pos)
                    {
                        cout << *pos << endl;
                    }
                }
                cout << "Words: " << numWords << endl;
         }
     } while (choice[0] != 'Q' && choice[0] != 'q');
 }
//Implement this function
 void loadStringset(Stringset& words, string filename)//load the stringset with word list from file
 {
    ifstream infile(filename);//create input file variable and open file
    string temp;//temp to store words line by line
    
    while (getline(infile, temp)){//get line until end of file
        words.insert(temp);//insert all words into stringet container
    }
    
    infile.close();//close file
 }
 
 
 //Implement this function
 vector<string> spellcheck(const Stringset& words, string word)//return list of suggested words one letter away from input word
 {
    long unsigned int comp = 0;//comparison counter
    vector<list<string>> temp = words.getTable();//set temp to value of stringet table
    vector<string> suggestions;//vector of strings holding suggested words
    
    for (int i = 0; i < words.getSize(); i++){//loop through vector  
        for (auto const& j : temp[i]){//iterate through linked list
            comp = 0;//reset comp to 0
            if (word.length() == j.length()){//check if words of are equal length
                for (long unsigned int k = 0; k < word.length(); k++){//loop through word length
                    if (j[k] == word[k]){//if a letter matches
                        comp = comp + 1;//increment comp
                    }
                }
                if (comp == word.length() - 1){//if word is one letter off from the word add it to suggestions
                    suggestions.push_back(j);
                }
            }
            
        }
    }  
      
      return suggestions;
 }
 
 
 