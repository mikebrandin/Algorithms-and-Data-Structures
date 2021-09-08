/*
 * Name: Mike Brandin
 * Date Submitted: 11/06/20
 * Lab Section: 4
 * Assignment Name: lab 8
 */

#include <iostream>
#include <vector>
#include <cstdlib>
#include <algorithm>
#include <assert.h>
#include <time.h>

using namespace std;

struct Node {
  int key;
  int size;
  Node *left;
  Node *right;
  Node (int k) { key = k; size = 1; left = right = nullptr; }
};

void fix_size(Node *T)
{
  T->size = 1;
  if (T->left) T->size += T->left->size;
  if (T->right) T->size += T->right->size;
}

// insert value v at rank r
Node *insert(Node *T, int v, int r)
{
    int curRank;

    if (!T){
        return new Node(v);
    }
    if (T->left){//if the left node exists set the current rank to the size of that node
        curRank = T->left->size;
    }
    else{
        curRank = 0;//otherwise bst is empty
    }
    
    if (curRank < r){//recurse to check if current rank is smaller than the desired rank
        T->right = insert(T->right, v, r - curRank - 1);
    }
    else{//recurse to check if current rank is larger or equal to the desired rank
        T->left = insert(T->left, v, r);

    }
        
    fix_size(T);
    return T;//return tree
  //Implement Node *insert(Node *T, int v, int r)
}

// returns a vector of key values corresponding to the inorder traversal of T (i.e., the contents of T in sorted order)
vector<int> inorder_traversal(Node *T)
{
  vector<int> inorder;
  vector<int> rhs;
  if (T == nullptr) return inorder;
  inorder=inorder_traversal(T->left);
  inorder.push_back(T->key);
  rhs=inorder_traversal(T->right);
  inorder.insert(inorder.end(), rhs.begin(), rhs.end());
  return inorder;
}

// return pointer to node of rank r (with r'th largest key; e.g. r=0 is the minimum)
Node *select(Node *T, int r)
{
  assert(T!=nullptr && r>=0 && r<T->size);

  int rank_of_root = T->left ? T->left->size : 0;
  if (r == rank_of_root) return T;
  if (r < rank_of_root) return select(T->left, r);
  else return select(T->right, r - rank_of_root - 1);
}

// Split tree T on rank r into tree L (containing ranks < r) and 
// a tree R (containing ranks >= r)
void split(Node *T, int r, Node **L, Node **R)
{
  //Implement void split(Node *T, int r, Node **L, Node **R)
    int curRank;
    
    if (!T){//if T is a nullptr
        *L = nullptr;
        *R = nullptr;
        return;
    }

    if (T->left){//if the left node exists set the current rank to the size of that node
        curRank = T->left->size;
    }
    else{
        curRank = 0;//otherwise bst is empty
    }    
    
    if (curRank >= r){//recurse through left tree 
        split(T->left, r, L, &(T->left)); 
        *R = T;//set node pointer to right side to T
        fix_size(*R);
    }
    else{
        split(T->right, r - curRank - 1, &(T->right), R);//recurse through right tree   
        *L = T;//set node pointer to left side to T
        fix_size(*L);
    }
}

// insert value v at rank r
Node *insert_random(Node *T, int v, int r)
{
  // If (v,r) is the Nth node inserted into T, then:
  // with probability 1/N, insert (v,r) at the root of T
  // otherwise, insert_random (v,r) recursively left or right of the root of T
   
    //srand(time(NULL));
    if (T){//if T is not a nullptr
        int curRank;
        
        if (T->left){//if the left node exists set the current rank to the size of that node
            curRank = T->left->size;
        }
        else{
            curRank = 0;//otherwise bst is empty
        }
        
        if ((rand() % (T->size)) == 0){//if random number mod size of tree is 0, that will be the root
            Node *L, *R;
            split(T, r, &L, &R);//split the array at this node
            
            Node* newNode = nullptr;
            newNode = insert(newNode, v, r);//create a new tree
           

            newNode->left = L;//connect left path to new tree
            newNode->right = R;//connect right path to new tree
            
            fix_size(newNode);//call fix size whenever the size of tree is altered
            return newNode;
        }
        else if (curRank < r){//if key is larger than current key recurse right
            T->right = insert_random(T->right, v, r - curRank - 1);
            fix_size(T);
        }
        else {//if key is smaller than current key recurse left
            T->left = insert_random(T->left, v, r);
            fix_size(T);
        }

    }
    else{
         return insert(T, v, r);//if T is a null pointer create new tree
    }  
    //Implement Node *insert_random(Node *T, int v, int r)
    return T;

}

// Returns true if team x defeated team y
// Leave this function unmodified
bool did_x_beat_y(int x, int y)
{
  assert (x != y);
  if (x > y) return !did_x_beat_y(y,x);
  unsigned long long lx = x;
  unsigned long long ly = y;
  return ((17 + 8321813 * lx + 1861 * ly) % 1299827) % 2 == 0;
}

// Return a BST containing a valid ordering of n teams
Node *order_n_teams(int n)
{
  Node* T = nullptr;
  // start by inserting the first team
  T = insert_random(T, 0, 0);
  int lowRank;	    
  int highRank; 
  int midRank; //= (lowRank + highRank) / 2;
	    
  // now insert the other teams...
  for (int i=1; i<n; i++) {
    // insert team i so the sequence encoded by the BST remains valid
    if (did_x_beat_y(i, select(T,0)->key)) // can we insert at beginning?
      T = insert_random(T, i, 0);
    else if (did_x_beat_y(select(T,T->size-1)->key, i)) // can we insert at end?
	    T = insert_random(T, i, T->size);
    else {
	    // 7 5 4 2 0 3 1 6    (when inserting team i=8)
	    // W W W L L L W L

        lowRank = 0;
	    highRank = T->size - 1;

        while (lowRank + 1 != highRank){
            midRank = (lowRank + highRank) / 2;//calculate mid rank

            if (did_x_beat_y(select(T, midRank)->key , i)){//if W loop through top half
                lowRank = midRank;
            }
            else{//if L loop through lower half
                highRank = midRank;
            }

        }
        
	  	T = insert_random(T, i, highRank);//insert new node at rank between W and L
    }
  }
  return T;
}

void printVector(vector<int> v)
{
    for (int i=0; i<int(v.size()); i++)
    {
        cout << v[i] << endl;
    }
}

int main(void)
{
    
  vector<int> inorder;
  Node *T = nullptr;

  // test insert at beginning
  for (int i=0; i<5; i++)
    T = insert_random(T, i+1, 0);
  cout << "Tree should contain 5 4 3 2 1:\n";
  inorder=inorder_traversal(T);
  printVector(inorder);

  // test insert at end
  for (int i=5; i<10; i++)
    T = insert_random(T, i+1, T->size);
  cout << "Tree should contain 5 4 3 2 1 6 7 8 9 10:\n";
  inorder=inorder_traversal(T);
  printVector(inorder);
  
  // test insert at middle
  for (int i=10; i<15; i++)
    T = insert_random(T, i+1, T->size/2);
  cout << "Tree should contain 5 4 3 2 1 12 14 15 13 11 6 7 8 9 10:\n";
  inorder=inorder_traversal(T);
  printVector(inorder);
  
 

  // once insert is working, the next step is to build the
  // insert_random function -- to test this, just change
  // calls to insert above to insert_random.

  int N = 100000; // this should run quickly even for very large N!
  Node *S = order_n_teams(N);
  if (S == nullptr || S->size != N)
    cout << "Size of tree returned by order_n_teams is wrong\n";
  else {
    cout << "Team ordering:\n";
    //    inorder=inorder_traversal(S);
    //    printVector(inorder);
    for (int i=0; i<N-1; i++) {
      Node *x = select(S, i);
      Node *y = select(S, i+1);
      if (!did_x_beat_y(x->key, y->key)) {
        cout << "Invalid sequence: team " << x->key << " (position " << i <<
	              ") lost to team " << y->key << " (position " << i+1 << ")\n";
      }
    }
  }  

  return 0;
}
