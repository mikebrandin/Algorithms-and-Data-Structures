/*
 * Name: Mike Brandin
 * Date Submitted: 11/21/2020   
 * Lab Section: 4 
 * Assignment Name: waterJugs - lab 10
 */

#include <iostream>
#include <vector>
#include <map>
#include <queue>
#include <bitset>

using namespace std;

// Reflects what each node represents...
// First value units of water in A, second units of water in B
typedef pair<int,int> state;

// Each string in edge_label must be one of the following:
const string actions[] = {"Fill A",
                          "Fill B",
                          "Empty A",
                          "Empty B",
                          "Pour A->B",
                          "Pour B->A"};

// GENERIC -- these shouldn't need to be changed...
map<state, bool> visited;         // have we queued up this state for visitation?
map<state, state> pred;           // predecessor state we came from
map<state, int> dist;             // distance (# of hops) from source node
map<state, vector<state>> nbrs;   // vector of neighboring states

map<pair<state,state>, string> edge_label;

// GENERIC (breadth-first search, outward from source_node)
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

// GENERIC
void print_path(state s, state t)
{
  if (s != t) {
    print_path(s, pred[t]);
    cout << edge_label[make_pair(pred[t], t)] << ": " << "[" << t.first << "," << t.second << "]\n";

  } else {
    cout << "Initial state: " << "[" << s.first << "," << s.second << "]\n";

  }
}

void neighborsTest(state jugs){
    vector<state> neighbors(6);
    
    for (int jCount = 0; jCount < 6; jCount++){//iterate through each possible action
        state tmp = jugs;
        
        switch (jCount){
            case 0:
                tmp.first = 3;
                break;
            case 1:
                tmp.second = 4;
                break;
            case 2:
                tmp.first = 0;
                break;
            case 3:
                tmp.second = 0;
                break;
            case 4:
                while (tmp.first > 0 && tmp.second != 4){
                    tmp.second++;
                    tmp.first--;
                }
                break;  
            case 5:
                while (tmp.second > 0 && tmp.first != 3){
                    tmp.second--;
                    tmp.first++;
                }
                break;
        }//switch
        neighbors[jCount] = tmp;//add tmp to neighbors vector of states
    }
    
    nbrs[jugs] = neighbors;//nbrs map is populated for the passed state
    
    for (int i = 0; i < 6; i++){//iterate through edges
        pair<state, state> tempEdge = make_pair(jugs, neighbors[i]);
        edge_label[tempEdge] = actions[i];
    }
    
}

void build_graph(void)
{
  //Implement this function
  for (int i = 0; i < 4; i++){
      for (int j = 0; j < 5; j++){
          state jugs = make_pair(i, j);//make pair for all jug combinations
          neighborsTest(jugs);//test state
      }
  }
  
}

int main(void)
{
  build_graph();

  state start = make_pair(0,0);
  
  for (int i=0; i<5; i++)
    nbrs[make_pair(i,5-i)].push_back(make_pair(-1,-1));
  search (start);
  if (visited[make_pair(-1,-1)]) 
    print_path (start, pred[make_pair(-1,-1)]);
  else
    cout << "No path!\n";
  
  return 0;
}
