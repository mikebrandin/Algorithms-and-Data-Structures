/*
 * Name: Mike Brandin
 * Date Submitted: 11/21/2020   
 * Lab Section: 4 
 * Assignment Name: wolfGoatCabbage - lab 10
 */

#include <iostream>
#include <vector>
#include <map>
#include <queue>
#include <bitset>

using namespace std;

// Reflects what each node represents...
// int with each bit == 0 left of river, bit == 1 right of river
typedef int state;

// Bit position representation for wolf/goat/cabbage/me
bool bit(int x, int i) { return (x>>i) & 1; }
const int wolf=0, goat=1, cabbage=2, me=3;

// GENERIC -- these shouldn't need to be changed...
map<state, bool> visited;         // have we queued up this state for visitation?
map<state, state> pred;           // predecessor state we came from
map<state, int> dist;             // distance (# of hops) from source node
map<state, vector<state>> nbrs;   // vector of neighboring states

map<pair<state,state>, string> edge_label;

// GENERIC (breadth-first search, outward from curnode)
void search(state source_node)
{
  queue<state> to_visit;
  to_visit.push(source_node);
  visited[source_node] = true;
  dist[source_node] = 0;
  
  while (!to_visit.empty()) {
    state curnode = to_visit.front();
    to_visit.pop();
    for (state n : nbrs[curnode])
      if (!visited[n]) {
	pred[n] = curnode;
	dist[n] = 1 + dist[curnode];
	visited[n] = true;
	to_visit.push(n);
      }
  }
}

string state_string(state s)
{
  string items[4] = { "wolf", "goat", "cabbage", "you" }, result = "";
  for (int i=0; i<4; i++)
    if (!bit(s, i)) result += items[i] + " ";
  result += " |river| ";
  for (int i=0; i<4; i++)
    if (bit(s, i)) result += items[i] + " ";
  return result;
}

// GENERIC
void print_path(state s, state t)
{
  if (s != t) {
    print_path(s, pred[t]);
    cout << edge_label[make_pair(pred[t], t)] << ": " << state_string(t) << "\n";
  } else {
    cout << "Initial state: " << state_string(s) << "\n";
  }
}

string neighbor_label(int s, int t)
{
  string items[3] = { "wolf", "goat", "cabbage" }, which_cross;
  if (bit(s,me) == bit(t,me)) return "";  // must cross river
  int cross_with = 0;
  for (int i=0; i<3; i++) {
    if (bit(s,i) != bit(t,i) && bit(s,i)==bit(s,me)) { cross_with++; which_cross = items[i]; }
    if (bit(s,i) != bit(t,i) && bit(s,i)!=bit(s,me)) return "";
  }
  if (cross_with > 1) return "";
  if (cross_with == 0) return "Cross alone";
  else return "Cross with " + which_cross;
}

bool edgeTest(bitset<4> bits){
    if (bits[goat] == bits[cabbage] && bits[cabbage] != bits[me]){//bad state
        return false;
    }
    if (bits[wolf] != bits[me] && bits[goat] == bits[wolf]){//bad state
        return false;
    }
    
    return true;//return if good state
}

void neighborsTest(bitset<4> bits){
    vector<state> neighbors;
    
    for (int i = 0; i < 4; i++){
        bitset<4> tmp = bits;
        
        if (bits[i] == bits[me]){
            tmp.flip(i);
            
            if (i != 3){
                tmp.flip(me);
            }
            if (edgeTest(tmp)){//good state add to neighbors
                neighbors.push_back(tmp.to_ulong());
                
                pair<state, state> statePair;
                statePair.first = bits.to_ulong();
                statePair.second = tmp.to_ulong();
                
                edge_label[statePair] = neighbor_label(tmp.to_ulong(), bits.to_ulong());
            }
            else{//bad state 
                tmp.flip(i);
                if (i != 3){
                    tmp.flip(me);
                }
            }
            
        }//if(bits[me == bits[i])
    }//for loop
    
    nbrs[bits.to_ulong()] = neighbors;
}

void build_graph(void)
{//Implement this function

    for (int i = 0; i < 16; i++){//populate bitset
        bitset<4> bits(i);
        if (edgeTest(bits)){//check if passes edge test
            neighborsTest(bits);//call neighborstest function for each bit
        }
    }
  
}

int main(void)
{
  build_graph();

  state start = 0, end = 15;
  
  search(start);
  if (visited[end])
    print_path (start, end);
  else
    cout << "No path!\n";
  
  return 0;
}
