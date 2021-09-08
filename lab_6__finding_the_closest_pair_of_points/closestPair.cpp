/*
 * Name: Mike Brandin   
 * Date Submitted: 10/19/2020
 * Lab Section: 4
 * Assignment Name: Lab 6 
 */

#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <cmath>

using namespace std;

struct point
{
    double x;
    double y;
};

/*Implement the following function
  Reads in a file specified by the parameter
  Format of file: #of points on first line
                  remaining (#of points) lines: x-value and y-value of point
                  one point per line
                  x-value and y-value are double-precision values and
                  bounded by the unit square 0.0 <= x,y < 1.0
  Should use "spatial hashing" where the #of cells scales with the #of points
  and find the distance between the closest pair of points which will be
  returned as a double type value
*/

double findDistance(point vec1, point vec2){//calculate the distance between two points

    return sqrt((vec1.x - vec2.x)*(vec1.x - vec2.x) + (vec1.y - vec2.y)*(vec1.y - vec2.y));//return distance
}

double closestPair(string filename){
    
    ifstream infile(filename);//open file
    int size; 
    
    infile >> size;//get size of file
    
    vector<point> points(size);
    
    for (int i = 0; i < size; i++){//populate vector of point structs with coordinates

        infile >> points[i].x >> points[i].y;
    }

    infile.close();//close file

    int cellSize = sqrt(size);//i chose the cellsize as the square root because it will make a square grid every time, likely more efficient
    
    vector<vector<vector<point>>> cellVec(cellSize, vector<vector<point>>(cellSize));//3 dimensional array and allocate correct size


    //below I calculate the correct position of each point based on its value and I populate the appropriate cell

    double xpos = 0;
    double ypos = 0;
    
    point myPoint;
    
    for (int i = 0; i < size; i++){

        xpos = points[i].x * cellSize;
        ypos = points[i].y * cellSize;

        myPoint.x = points[i].x;//grab value from earlier vector of points
        myPoint.y = points[i].y;

        cellVec[int(xpos)][int(ypos)].push_back(myPoint);

    }
    
    double min = 1000;

    for (int i = 0; i < cellSize; i++){//row loop
        for (int j = 0; j < cellSize; j++){//column loop   
            
            for (int c = 0; c < int(cellVec[i][j].size()); c++){//index loop
    
                if (cellVec[i][j].size() > 0){//check that cell is not empty
                
                
                //for the cell and its adjacent cells check each index and compare its distance to the original point, 
                //if the distance is smaller than the minimum, it is the new minimum
                
                    for (long unsigned int k = 0; k < cellVec[i][j].size(); k++){//check own cell
                        if (cellVec[i][j][c].x != cellVec[i][j][k].x && cellVec[i][j][c].y != cellVec[i][j][k].y && findDistance(cellVec[i][j][c], cellVec[i][j][k]) < min){
                                
                            min = findDistance(cellVec[i][j][c], cellVec[i][j][k]);
                        }
                    }
                    
                    if (i+1 < cellSize && cellVec[i+1][j].size() != 0){//check cell to the right
                        for (long unsigned int k = 0; k < cellVec[i+1][j].size(); k++){
                            if (cellVec[i][j][c].x != cellVec[i+1][j][k].x && cellVec[i][j][c].y != cellVec[i+1][j][k].y && findDistance(cellVec[i][j][c], cellVec[i+1][j][k]) < min){
                                
                                min = findDistance(cellVec[i][j][c], cellVec[i+1][j][k]);
                            }
                        }                
                    }
                    
                    if (i+1 < cellSize && j+1 < cellSize && cellVec[i+1][j+1].size() != 0){//check cell to the top right
                        for (long unsigned int k = 0; k < cellVec[i+1][j+1].size(); k++){
                            if (cellVec[i][j][c].x != cellVec[i+1][j+1][k].x && cellVec[i][j][c].y != cellVec[i+1][j+1][k].y && findDistance(cellVec[i][j][c], cellVec[i+1][j+1][k]) < min){
        
                                min = findDistance(cellVec[i][j][c], cellVec[i+1][j+1][k]);
                            }
                        }                
                    }     
                    
                    if (i+1 < cellSize && j-1 >= 0 && cellVec[i+1][j-1].size() != 0){//check cell to the bottom right
                        for (long unsigned int k = 0; k < cellVec[i+1][j-1].size(); k++){
                            if (cellVec[i][j][c].x != cellVec[i+1][j-1][k].x && cellVec[i][j][c].y != cellVec[i+1][j-1][k].y && findDistance(cellVec[i][j][c], cellVec[i+1][j-1][k]) < min){
        
                                min = findDistance(cellVec[i][j][c], cellVec[i+1][j-1][k]);
                            }
                        }
                    }
                    
                    if (j+1 < cellSize && cellVec[i][j+1].size() != 0){//check cell above
                        for (long unsigned int k = 0; k < cellVec[i][j+1].size(); k++){
                            if (cellVec[i][j][c].x != cellVec[i][j+1][k].x && cellVec[i][j][c].y != cellVec[i][j+1][k].y && findDistance(cellVec[i][j][c], cellVec[i][j+1][k]) < min){
        
                                min = findDistance(cellVec[i][j][c], cellVec[i][j+1][k]);
        
                            }
                        }
                    }
        
                    if (j-1 >= 0 && cellVec[i][j-1].size() != 0){//check cell below
                        for (long unsigned int k = 0; k < cellVec[i][j-1].size(); k++){
                            if (cellVec[i][j][c].x != cellVec[i][j-1][k].x && cellVec[i][j][c].y != cellVec[i][j-1][k].y && findDistance(cellVec[i][j][c], cellVec[i][j-1][k]) < min){
        
                                min = findDistance(cellVec[i][j][c], cellVec[i][j-1][k]);
                            }
                        }                
                    }
                   
                    if (i-1 >= 0 && cellVec[i-1][j].size() != 0){//check cell to the left
                        for (long unsigned int k = 0; k < cellVec[i-1][j].size(); k++){
                            if (cellVec[i][j][c].x != cellVec[i-1][j][k].x && cellVec[i][j][c].y != cellVec[i-1][j][k].y && findDistance(cellVec[i][j][c], cellVec[i-1][j][k]) < min){

                                min = findDistance(cellVec[i][j][c], cellVec[i-1][j][k]);
                            }
                        }
                    }
                    
                    if (i-1 >= 0 && j+1 < cellSize && !cellVec[i-1][j+1].size() != 0){//check cell to the top left
                        for (long unsigned int k = 0; k < cellVec[i-1][j+1].size(); k++){
                            if (cellVec[i][j][c].x != cellVec[i-1][j+1][k].x && cellVec[i][j][c].y != cellVec[i-1][j+1][k].y && findDistance(cellVec[i][j][c], cellVec[i-1][j+1][k]) < min){
                                
                                min = findDistance(cellVec[i][j][c], cellVec[i-1][j+1][k]);
                            }
                            
                        }
                        
                    }
                    
                    if (i-1 >= 0 && j-1 >= 0 && cellVec[i-1][j-1].size() != 0){//check cell to the bottom left
                        for (long unsigned int k = 0; k < cellVec[i-1][j-1].size(); k++){
                            if (cellVec[i][j][c].x != cellVec[i-1][j-1][k].x && cellVec[i][j][c].y != cellVec[i-1][j-1][k].y && findDistance(cellVec[i][j][c], cellVec[i-1][j-1][k]) < min){
                                
                                min = findDistance(cellVec[i][j][c], cellVec[i-1][j-1][k]);
                            }
                        }
                    }
    
                }//if statement to check if empty
            
            
            }//index loop
            
        }//column loop   
        
    }//row loop
    
    
    return min;
}

int main()
{
    double min;
    string filename;
    cout << "File with list of points within unit square: ";
    cin >> filename;
    min = closestPair(filename);
    cout << setprecision(16);
    cout << "Distance between closest pair of points: " << min << endl;
    return 0;
}