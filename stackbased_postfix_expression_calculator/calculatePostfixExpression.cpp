/*
 * Name: Mike Brandin
 * Date Submitted: 09/21/20
 * Assignment Name: Stack-based Postfix Expression Calculator
 */



#include <string>
#include <stack>

//#include <iostream>



using namespace std;

//Calculates a postfix expression with integer operands using a stack
//The expression is represented using an array of strings
//Each string is either an operand or operator symbol
//Operator symbols:
//"+" addition
//"-" subtraction
//"*" multiplication
//"/" divison
//"%" remainder
//Example expression: "8", "5", "-" evaluates to a result of 3:
//1: push 8, 2: push 5,
//3: "-"-> pop top two values, earlier value is the left-side operand: 8 - 5
//The result of the operation (8-5) is 3, push 3 onto stack
//After evaluation of the expression, the final result should be
//the only value on the stack, return 0 if the stack is
//non-empty after popping the result
//Return 0 if expression is zero-length or if there are insufficient operands
//for an operation
//The STL Stack class can be used
//To easily convert a numeric string to an int you may use the stoi() function
//which takes a string as a parameter and returns a string

bool isOperator(string input){//check if valid operator
    
    if (input == "+" || input == "-" || input == "*" || input == "/" || input == "%"){
        return true;

    }
    else{
        return false;
    }
    
}

int calculatePostfixExpression(string expression[], int length)
{
    stack<int> oStack;
    int temp = 0;
    int oCount = 0;
    int nCount = 0;
    
    for (int i = 0; i < length; i++){//check if input is valid by counting how many operands and operators there are

        if (isOperator(expression[i])){
            oCount++;
        }
        else{
            nCount++;
        }
    
    }
    
    if ((nCount <= oCount) || length == 0){//if the operators exceed or are equal to the operands the equation is invalid
        return 0;//or if length is 0
    }

    
    for (int i = 0; i < length; i++){//iterate through length of input expression
        if (isOperator(expression[i])){//if index is an operator
        
            if (expression[i] == "+"){//add
                temp = oStack.top();
                oStack.pop();
                temp = oStack.top() + temp;//add top two numbers in stack 
                oStack.pop();//pop the top two numbers in the stack

            }
            else if (expression[i] == "-"){//subtract
                temp = oStack.top();
                oStack.pop();
                temp =  oStack.top() - temp;
                oStack.pop();

            }
            else if (expression[i] == "*"){//multiply
                temp = oStack.top();
                oStack.pop();
                temp = oStack.top() * temp;
                oStack.pop();
            
            }
            else if (expression[i] == "/"){//divide
                temp = oStack.top();
                oStack.pop();
                temp = oStack.top() / temp;
                oStack.pop();

            }
            else if (expression[i] == "%"){//modulus
                temp = oStack.top();
                oStack.pop();
                temp = oStack.top() % temp;
                oStack.pop();
                
            }
            
            oStack.push(temp);//push resultant to top of stack

        }
        else{//if index is a number
            oStack.push(stoi(expression[i]));//push to stack
        }
            
    }
    temp = oStack.top();
    
    oStack.pop();
    
    if (!oStack.empty()){//check if stack is empty(except for the result)
        return 0;
    }      
    
    return temp;//return what was previously top of the stack
    
}



int main(){
    
    //string expression[15] = {"21", "5", "-", "34", "2", "-", "*","3", "5", "+", "5", "11", "+", "*", "/"};
    
    //cout << calculatePostfixExpression(expression, 15) << endl;
    
    return 0;
}