/*
 * Name: Mike Brandin
 * Date Submitted: 09/18/20
 * Lab Section: 4 
 * Assignment Name: Lab 3
 */

#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

//Represents an occupied square in the grid
//Do not modify the GridSquare class or its member functions
class GridSquare
{
    private:
        int row, col;
    public:
        GridSquare() : row(0), col(0) {} //Default constructor, (0,0) square
        GridSquare(int r, int c) : row(r), col(c) {} //(r,c) square
        //Compare with == operator, used in test cases
        bool operator== (const GridSquare r) const
        {
            if ((row == r.row) && (col == r.col))
            {
                return true;
            }
            return false;
        }
        int getRow() { return row; } //return row value
        int getCol() { return col; } //return column value
        //Output using << operator, used in Grouping::printGroups()
        friend ostream& operator<< (ostream& os, const GridSquare obj);
};

//Function definition for <ostream> << <GridSquare>
ostream& operator<< (ostream& os, const GridSquare obj)
{
    os << "(" << obj.row << "," << obj.col << ")";
    return os;
}

/*
Groups squares in 10x10 grid upon construction
Additional private helper functions may be added
Need to implement the constructor that takes a file name
as well as findGroup
The findGroup function's parameter list may be changed based
on how the function is implemented
*/
class Grouping
{
    private:
        int grid[10][10];
        vector<vector<GridSquare>> groups;
    public:
        Grouping() : grid{},groups() {} //Default constructor, no groups
        Grouping(string fileName); //Implement this function
        void findGroup(int r, int c); //Implement this function (recursive)
        bool isInGroup(GridSquare input);

        void printGroups() //Displays grid's groups of squares
        {
            for(long unsigned int g=0; g<groups.size(); g++)
            {
                cout << "Group " << g+1 << ": ";
                for(long unsigned int s=0; s<groups[g].size(); s++)
                {
                    cout << " " << groups[g][s];
                }
                cout << endl;
            }
        }
        vector<vector<GridSquare>> getGroups() //Needed in unit tests
        {
            return groups;
        }
};



//Implement the (parameterized) constructor and findGroup functions below
Grouping::Grouping(string fileName){
    ifstream file;
    file.open(fileName);
    string line;

        for (int xCount = 0; xCount < 10; xCount++){//fill out the grid
            getline(file, line);
            for (int yCount = 0; yCount < 10; yCount++){
                if (line[yCount] != '.'){
                    grid[xCount][yCount] = 1;
                }
                else{
                    grid[xCount][yCount] = 0;
                }
            }    
        }
    
    file.close();
    
    
    vector<GridSquare> temp; //push first group into array
    groups.push_back(temp);
    
    for (int xCount = 0; xCount < 10; xCount++){ 
        for (int yCount = 0; yCount < 10; yCount++){
            if (grid[xCount][yCount] == 1){//for all X's in array
                if (groups[groups.size()-1].empty()){//if last group is empty fill it with findGroup
                    findGroup(xCount, yCount);
                }
                else{//if last group is occupied, create a new one and call findGroup
                    vector<GridSquare> temp; 
                    groups.push_back(temp);
                    findGroup(xCount, yCount);    
                }
    
            }
        }
    }    

    if (groups.empty()){
        //nothing    
    }
    else if (groups[groups.size() - 1].empty()){//if group at end is empty get rid of it 
        groups.pop_back();
    }

}

bool Grouping::isInGroup(GridSquare input){//return true if input matches the coord's of an already grouped coord
    for(long unsigned int g=0; g<groups.size(); g++){
        for(long unsigned int s=0; s<groups[g].size(); s++){
            if (groups[g][s] == input){
                return true;
            }
        }
    }
    return false;
}


void Grouping::findGroup(int r, int c){//recursive function to find all adjacent coords in a group 
    int groupNum = groups.size() - 1;//automatically get group index

    GridSquare temp(r, c);
    if (isInGroup(temp)){//if already in a group, abort
        return;
    }
    else {
        groups[groupNum].push_back(temp);
        
        if ((r > 0) && grid[r-1][c] == 1){//if there's an  X to the left; call recursive function
            findGroup(r-1, c);
        }
        if ((r < 9) && grid[r+1][c] == 1){//if there's an  X to the right; call recursive function
            findGroup(r+1, c);
        }
        if ((c > 0) && grid[r][c-1] == 1){//if there's an  X below; call recursive function
            findGroup(r, c-1);
        }
        if ((c < 9) && grid[r][c+1] == 1){//if there's an  X above; call recursive function
            findGroup(r, c+1);
        }
        else{//if not adjacent or inbounds, abort
            return;
        }
    
    }
}

//Simple main function to test Grouping
int main()
{
    Grouping input1("input1.txt");
    input1.printGroups();
    
    return 0;
}