/*
 * Name: Mike Brandin   
 * Date Submitted: 10/28/2020
 * Lab Section: 4
 * Assignment Name: lab 7
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

// insert key k into tree T, returning a pointer to the resulting tree
Node *insert(Node *T, int k)
{
  if (T == nullptr) return new Node(k);
  if (k < T->key) T->left = insert(T->left, k);
  else T->right = insert(T->right, k);
  fix_size(T);
  return T;
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

// return a pointer to the node with key k in tree T, or nullptr if it doesn't exist
Node *find(Node *T, int k)
{
  //Implement Node *find(Node *T, int k)
  if (T == nullptr || T->key == k){//if T is null or key is found return the node
      return T;
  }
  if (k < T->key){ //key is less than node -- recurse left
      return find(T->left, k);
  }
  
  return find(T->right, k);//key is greater than node - recurse right
}

// return pointer to node of rank r (with r'th largest key; e.g. r=0 is the minimum)
Node *select(Node *T, int r)
{
    assert(T!=nullptr && r>=0 && r<T->size);
    int curRank;
    
    if (T->left){//if the left node exists set the current rank to the size of that node
        curRank = T->left->size;
    }
    else{
        curRank = 0;//otherwise bst is empty
    }
    
    if (curRank > r){//recurse to check if current rank is larger than the desired rank
        if (T->left){
            return select(T->left, r);
        }
        else{
            return nullptr;
        }
    }
    else if (curRank < r){//recurse to check if current rank is smaller than the desired rank
        if (T->right){
            return select(T->right, r - curRank - 1);
        }
        else{
            return nullptr;
        }
    }
    else{
        return T;//we have arrived at correct node so return it
    }
        
  //Implement Node *select(Node *T, int r)
}

// Join trees L and R (with L containing keys all <= the keys in R)
// Return a pointer to the joined tree.  
Node *join(Node *L, Node *R)
{
  // choose either the root of L or the root of R to be the root of the joined tree
  // (where we choose with probabilities proportional to the sizes of L and R)
    Node* temp = nullptr;
    
    srand (time(NULL));//create random seed
    
    if (!L){//if left is a null pointer
        return temp = R;
    }
    else if (!R){//if right is a null pointer
        return temp = L;
    }
    double rando = rand() % 101 / 100.0;//creates random double number from 0 to 1

    double form = double(L->size) / (double(L->size) + double(R->size));//calculate formula in lab slides
    

    if (rando <= form){//root of left tree will become the root of the joined tree
        L->right = join(L->right, R); 
        temp = L;
        fix_size(temp);
    }
    else {//root of right tree will become the root of the joined tree
        R->left = join(L, R->left); 
        temp = R;
        fix_size(temp);

    }
  
  //Implement Node *join(Node *L, Node *R)
    return temp;
}

void printVector(vector<int> v)
{
    for (int i=0; i<int(v.size()); i++)
    {
        cout << v[i] << endl;
    }
}

// remove key k from T, returning a pointer to the resulting tree.
// it is required that k be present in T
Node *remove(Node *T, int k)
{
  assert(T != nullptr);
  
    if (T->key == k) {//if we have arrived at the correct node
        Node* temp = T;//store value of node and then later delte it 
    
        T = join(T->left, T->right);//call join excluding the current node

        delete temp;
        return T;
        
    }
    else if (k < T->key){//if current key is too large recurse through left trees
        if (T->left){
            T->left = remove(T->left , k);
        }
    }
    else if (k > T->key){//if current key is too small recurse through right trees
        if (T->right){
            T->right = remove(T->right, k);
        }
    }
    
  //Implement Node *remove(Node *T, int k)
    fix_size(T);
    return T;//return full tree excluding the deleted node

}


// Split tree T on key k into tree L (containing keys <= k) and a tree R (containing keys > k)
void split(Node *T, int k, Node **L, Node **R)
{
  //Implement void split(Node *T, int k, Node **L, Node **R)
  
    if (!T){//if T is a nullptr
        *L = nullptr;
        *R = nullptr;
    }
    else if (k < T->key){//recurse through left tree 
        split(T->left, k, L, &(T->left)); 
        *R = T;//set node pointer to right side to T
        fix_size(*R);
    }
    else{
        split(T->right, k, &(T->right), R);//recurse through right tree   
        *L = T;//set node pointer to left side to T
        fix_size(*L);
    }

}

// insert key k into the tree T, returning a pointer to the resulting tree
Node *insert_random(Node *T, int k)
{
  // If k is the Nth node inserted into T, then:
  // with probability 1/N, insert k at the root of T
  // otherwise, insert_random k recursively left or right of the root of T
    
    if (T){//if T is not a nullptr
        if ((rand() % T->size) == 0){//if random number mod size of tree is 0, that will be the root
            Node *L, *R;
            split(T, k, &L, &R);//split the array at this node
            
            Node* newNode = nullptr;
            newNode = insert(newNode, k);//create a new tree
           

            newNode->left = L;//connect left path to new tree
            newNode->right = R;//connect right path to new tree
            
            fix_size(newNode);//calk fix size whenever the size of tree is altered
            return newNode;
        }
        else if (k < T->key){//if key is smaller than current key recurse left
            T->left = insert_random(T->left, k);
            fix_size(T);
        }
        else if (k > T->key){//if key is larger than current key recurse right
             T->right = insert_random(T->right, k);
            fix_size(T);
        }
    }
    else{
         return insert(T, k);//if T is a null pointer create new tree
    }
    //Implement Node *insert_random(Node *T, int k)
    return T;
}


int main(void)
{
  vector<int> inorder;
  vector<int> A(10,0);
  
  // put 0..9 into A[0..9] in random order
  for (int i=0; i<10; i++) A[i] = i;
  for (int i=9; i>0; i--) swap(A[i], A[rand()%i]);
  cout << "Contents of A (to be inserted into BST):\n";
  printVector(A);
  
  // insert contents of A into a BST
  Node *T = nullptr;
  for (int i=0; i<10; i++) T = insert(T, A[i]);
  
  
  // print contents of BST (should be 0..9 in sorted order)
  cout << "Contents of BST (should be 0..9 in sorted order):\n";
  inorder=inorder_traversal(T);
  printVector(inorder);

  // test select
  for (int i=0; i<10; i++) {
    Node *result = select(T, i);
    if (!result || result->key != i) cout << "Select test failed for select(" << i << ")!\n";
  }

  // test find: Elements 0..9 should be found; 10 should not be found
  cout << "Elements 0..9 should be found; 10 should not be found:\n";
  for (int i=0; i<11; i++) 
    if (find(T,i)) cout << i << " found\n";
    else cout << i << " not found\n";

  // test split
  Node *L, *R;
  split(T, 4, &L, &R);
  cout << "Contents of left tree after split (should be 0..4):\n";
  inorder=inorder_traversal(L);
  printVector(inorder);
  cout << "Left tree size " << L->size << "\n";
  cout << "Contents of right tree after split (should be 5..9):\n";
  inorder=inorder_traversal(R);
  printVector(inorder);
  cout << "Right tree size " << R->size << "\n";
 
  
  // test join
  T = join(L, R);
  cout << "Contents of re-joined tree (should be 0..9)\n";
  inorder=inorder_traversal(T);
  printVector(inorder);
  cout << "Tree size " << T->size << "\n";

  // test remove
  for (int i=0; i<10; i++) A[i] = i;
  for (int i=9; i>0; i--) swap(A[i], A[rand()%i]);
  for (int i=0; i<10; i++) {
    T = remove(T, A[i]);
    cout << "Contents of tree after removing " << A[i] << ":\n";
    inorder=inorder_traversal(T);
    printVector(inorder);
    if (T != nullptr)
      cout << "Tree size " << T->size << "\n";
  }

  // test insert_random
  cout << "Inserting 1 million elements in order; this should be very fast...\n";
  for (int i=0; i<1000000; i++) T = insert_random(T, i);
  cout << "Tree size " << T->size << "\n";
  cout << "Done\n";

  return 0;
}
