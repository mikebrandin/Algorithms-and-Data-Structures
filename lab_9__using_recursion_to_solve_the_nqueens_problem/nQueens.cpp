/*
 * Name: Mike Brandin
 * Date Submitted: 11/10/2020
 * Lab Section: 4 
 * Assignment Name: lab 9
 */

#include <iostream>
#include <vector>

using namespace std;

bool isMoveValid(vector<vector<int>> &vec, int i, int j){//checks if position is valid for queen
    int tempI = 0;
    int tempJ = j;

    for (tempI = i; tempI >= 0; tempI--){//check up and down
        if (vec[tempI][tempJ] == 1){//if location contains a queen
            return false;
        }
    }
    
    for (tempJ = j; tempJ >= 0; tempJ--){//check left and right
        if (vec[i][tempJ] == 1){//if location contains a queen
            return false;
        }
    }

    for (tempI = i, tempJ = j; tempJ >= 0 && tempI >= 0; tempI--, tempJ--){//check postive diagonals
        if (vec[tempI][tempJ] == 1){//if location contains a queen
            return false;
        }
    }

    for (tempI = i, tempJ = j; tempJ < int(vec.size()) && tempI >= 0; tempJ++, tempI--){//check negative diagonals
        if (vec[tempI][tempJ] == 1){//if location contains a queen
            return false;
        }
    }
    
    return true;//not touching another queen
}

void solCounter(vector<vector<int>> &vec, int* sols, int index, int n){
    if (index == n){//when you have reached the final index
          *sols = *sols + 1;//incremement for last solution and quit recursion
    }
    else{//not last index
        for (int j = 0; j < n; j++){//check all indexes
            if (isMoveValid(vec, index, j)){//if valid move place recurse through next index
                vec[index][j] = 1; //place queen
                solCounter(vec, sols, index + 1, n);//recursively call to next index
                vec[index][j] = 0; //remove queen
            }
        }
    }
}

//Uses recursion to count how many solutions there are for
//placing n queens on an nxn chess board
int nQueens(int n){
    //Implement int nQueens(int n)
    //Feel free to implement any recursive helper functions
    int numSol = 0;//number of solutions
    vector<vector<int>> board(n, vector<int>(n, 0));//create empty 2d array represneting chessboard of size n

    solCounter(board, &numSol, 0, n);//call recursive function to count number of solutions starting at first index
    
    return numSol;//return total number of solutions
}


int main()
{
    cout << "1: " << nQueens(1) << endl;
    cout << "2: " << nQueens(2) << endl;
    cout << "3: " << nQueens(3) << endl;
    cout << "4: " << nQueens(4) << endl;
    cout << "5: " << nQueens(5) << endl;
    cout << "6: " << nQueens(6) << endl;
    cout << "7: " << nQueens(7) << endl;
    cout << "8: " << nQueens(8) << endl;
    cout << "9: " << nQueens(9) << endl;
    cout << "10: " << nQueens(10) << endl;
    cout << "11: " << nQueens(11) << endl;
    cout << "12: " << nQueens(12) << endl;
    return 0;
}