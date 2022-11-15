#include "Node.hpp"
#include <iostream>
#include <algorithm>
#include <vector>


std::vector<Node<int>*> createRing(Node<int>* start, int num_nodes){
  std::vector<Node<int>*> nodes; 
  nodes.push_back(start);
  Node<int>* last_node = start;
  int value_offset = start->getValue() + 1; // How much should we 
  for(int i = 0; i < num_nodes-1; i++){ // Create another num_nodes-1 nodes
    Node<int>* new_node = new Node<int>(i+value_offset); // Create unique node with unique value
    new_node->addEdge(last_node);
    last_node = new_node;
    nodes.push_back(new_node);
  }
  // Link end back to start
  start->addEdge(last_node);
  return nodes;
}

std::vector<Node<int>*> figure8(Node<int>* a, int num_nodes){
  std::vector<Node<int>*> nodes = createRing(a, num_nodes/2);
  std::vector<Node<int>*> nextNodes = createRing(nodes.at(nodes.size()-1), num_nodes/2); // Create second ring of figure8 starting from end of first ring
  nextNodes.erase(nextNodes.begin());
  nodes.insert(nodes.end(), nextNodes.begin(), nextNodes.end());
  return nodes;
}

// Create a graph of nodes that is in a rectangular grid shape
std::vector<Node<int>*> grid(Node<int>* a, int width, int height){
  std::vector<Node<int>*> nodes = {};
  nodes.push_back(a);
  int num_nodes = width*height;
  // Build grid starting at top row, going from left to right
  for(int i = 1; i < num_nodes; i++){
    Node<int>* new_node = new Node<int>(i);
    // Connect to node above it
    int y = i/width; // Y coordinate
    int x = i%width;
    if(y > 0){
      int above_node_index = (y-1)*width + x;
      new_node->addEdge(nodes.at(above_node_index));
    }
    // Connect to node to the left of it
    if(x > 0){
      int left_node_index = y*width + (x-1);
      new_node->addEdge(nodes.at(left_node_index));
    }
    nodes.push_back(new_node);
  }
  return nodes;
}

// Create a graph where every node is connected to every node
// WARNING: O(n!) run time
std::vector<Node<int>*>  completeGraph(Node<int>* a, int num_nodes){
  std::vector<Node<int>*> nodes = {};
  nodes.push_back(a);
  for(int i = 1; i < num_nodes; i++){ // Create another num_nodes nodes
    Node<int>* new_node = new Node<int>(i); // Create unique node with unique value
    // Connect new node to all existing nodes
    for(int j = 0; j < nodes.size(); j++){
      new_node->addEdge(nodes.at(j));
    }
    nodes.push_back(new_node);
  }
  return nodes;
}

bool Test1(){
  bool didTestPass = false;
  Node<int>* a = new Node<int>(1);
  Node<int>* b = new Node<int>(2);
  Node<int>* c = new Node<int>(3);
  Node<int>* d = new Node<int>(4);
  Node<int>* e = new Node<int>(5);
  Node<int>* f = new Node<int>(6);
  std::vector<Node<int>*> allNodes; 
  allNodes.push_back(a);
  allNodes.push_back(b);
  allNodes.push_back(c);
  allNodes.push_back(d);
  allNodes.push_back(e);
  allNodes.push_back(f);
  allNodes.push_back(a);
  a->addEdge(d);
  d->addEdge(b);
  d->addEdge(c);
  d->addEdge(e);
  b->addEdge(c);
  c->addEdge(e);
  e->addEdge(f);
  f->addEdge(a);
  if(a->isCycleBruteForce(6, allNodes)){
    cout << "Brute Force Test 1 passed" << endl;
    didTestPass = true;
  }
  else { 
    cout << "Brute Force Test 1 failed" << endl;
  }

  if(a->isCycleBacktracking(6)){
    cout << "Backtrack Test 1 passed" << endl;
  } 
  else { 
    cout << "Backtrack Test 1 failed" << endl;
    didTestPass = false;
  }
  return didTestPass;
}

bool Test2(){
  bool didTestPass = false;
  Node<int>* a = new Node<int>(1);
  Node<int>* b = new Node<int>(2);
  Node<int>* c = new Node<int>(3);
 std::vector<Node<int>*> allNodes; 
  allNodes.push_back(a);
  allNodes.push_back(b);
  allNodes.push_back(c);
  allNodes.push_back(a);
  a->addEdge(b);
  b->addEdge(c);
  c->addEdge(a);
  if(a->isCycleBruteForce(3, allNodes)){
    cout << "Brute Force Test 2 passed" << endl;
    didTestPass = true;
  }
  else { 
    cout << "Brute Force Test 2 failed" << endl;
  }

  if(a->isCycleBacktracking(3)){
    cout << "Backtrack Test 2 passed" << endl;
  } 
  else { 
    cout << "Backtrack Test 1 failed" << endl;
    didTestPass = false;
  }
  return didTestPass;
}

bool Test3(){
  //a->b->c no cycle
  bool didTestPass = false;
  Node<int>* a = new Node<int>(1);
  Node<int>* b = new Node<int>(2);
  Node<int>* c = new Node<int>(3);
  std::vector<Node<int>*> allNodes; 
  allNodes.push_back(a);
  allNodes.push_back(b);
  allNodes.push_back(c);
  allNodes.push_back(a);
  a->addEdge(b);
  b->addEdge(c);
  if(a->isCycleBruteForce(3, allNodes)){
    cout << "Brute ForceTest 3 failed" << endl;
  }
  else { 
    cout << "Brute Force Test 3 passed" << endl;
    didTestPass = true;
    }

  if(a->isCycleBacktracking(3)){
    cout << "Backtrack Test 3 failed" << endl;
      didTestPass = false;
  } 
  else { 
    cout << "Backtrack Test 3 passed" << endl;
  }
   return didTestPass;
}

bool Test4(){
  bool didTestPass = false;
  Node<int>* a = new Node<int>(1);
  std::vector<Node<int>*> allNodes; 
  allNodes.push_back(a);
  if(a->isCycleBruteForce(1, allNodes)){
    cout << "Brute Force Test 4 passed" << endl;
    didTestPass = true;
  }
  else { 
    cout << "Brute Force Test 4 failed" << endl;
    }
  
  if(a->isCycleBacktracking(1)){
    cout << "Backtrack Test 4 passed" << endl;
      
  } 
  else { 
    cout << "Backtrack Test 4 failed" << endl;
    didTestPass = false;
  }
  return didTestPass;
}


bool Test5(){ 
  bool didTestPass = false; 
  Node<int>* a = new Node<int>(1);
  vector<int> ringSizes = {3, 8, 14, 23, 18, 7}; 
  for(int i = 0; i < ringSizes.size(); i++){
    std::vector<Node<int>*> allNodes = createRing(a, ringSizes.size());
    allNodes.push_back(a);
    if(a->isCycleBruteForce(allNodes.size() - 1, allNodes)){
      didTestPass = true;
    }
    else { 
      cout << "Brute Force Test 5 failed with ring size " << ringSizes[i] << endl;
    }
    if(a->isCycleBacktracking(allNodes.size() - 1)){
    } 
    else { 
      cout << "Backtrack Test 5 failed with ring size " << ringSizes[i] << endl;
      didTestPass = false;
    }
  }
  cout << "Brute Force Test 5 passed" << endl;
  cout << "Backtrack Test 5 passed " << endl;
  return didTestPass;
  
  }


bool Test6(){
  std::vector<int> sizes = {6, 7, 9};
  for(int size: sizes){
    Node<int>* a = new Node<int>(1);
    std::vector<Node<int>*> allNodes = figure8(a, size);
    allNodes.push_back(a);
    if(a->isCycleBacktracking(allNodes.size() - 1)){ // Test fails if Hamiltonian cycle is identified
      cout << "Backtrack Test 6 failed for size " << size << endl;
      return false;
    }
    if(a->isCycleBruteForce(allNodes.size() - 1, allNodes)){ // Test fails if Hamiltonian cycle is identified
      cout << "We have a size of" << allNodes.size() << endl; 
      cout << "Brute Force Test 6 failed for size " << size << endl;
      return false;
    }
  }
  cout << "Brute Force Test 6 passed " << endl;
  cout << "Backtrack Test 6 passed " << endl;
  return true;
}



bool Test7(){
  std::vector<std::pair<int, int>> sizes = { {1, 4}, {1, 5}, {2, 3}, {4, 3}, {3, 3} };
  for(std::pair<int, int> size: sizes){
    Node<int>* startNode = new Node<int>(1);
    std::vector<Node<int>*> allNodes = grid(startNode, size.first, size.second);
    bool isCycle = allNodes.size() %2 == 0 && (size.first > 1 && size.second > 1); // Cycle is present for grid if even number of nodes, as long as both dimensions are > 1
    allNodes.push_back(startNode);
    if(startNode->isCycleBacktracking(allNodes.size() - 1) != isCycle){ 
      cout << "Backtrack Test 7 failed for size " << size.first << " " << size.second << endl;
      return false;
    }
    if(startNode->isCycleBruteForce(allNodes.size() - 1, allNodes) != isCycle){ // Test passes if Hamiltonian cycle is identified
      cout << "Brute Force Test 7 failed for size " << size.first << " " << size.second << endl;
      return false;
    }
  }
  cout << "Brute Force Test 7 passed " << endl;
  cout << "Backtrack Test 7 passed " << endl;
  return true;
}



bool Test8(){
  std::vector<int> sizes = {5, 8, 10};
  for(int size: sizes){
    Node<int>* startNode = new Node<int>(1);
    std::vector<Node<int>*> allNodes = completeGraph(startNode, size);
    allNodes.push_back(startNode);
    if(!startNode->isCycleBacktracking(allNodes.size() - 1)){ // Test fails if Hamiltonian cycle is not identified
      cout << "Backtrack Test 8 failed for size " << size << endl;
      return false;
    }
    if(!startNode->isCycleBruteForce(allNodes.size(), allNodes)){ // Test fails if Hamiltonian cycle is not identified
      cout << "Brute Force Test 8 failed for size " << size << endl;
      return false;
    }
  }
  cout << "Brute Force Test 8 passed " << endl;
  cout << "Backtrack Test 8 passed " << endl;
  return true;
}


bool Test9(){
  //a->b->c no cycle
  bool didTestPass = false;
  Node<int>* a = new Node<int>(1);
  Node<int>* b = new Node<int>(2);
  Node<int>* c = new Node<int>(3);
  Node<int>* d = new Node<int>(3);
  Node<int>* e = new Node<int>(3);
  Node<int>* f = new Node<int>(3);
  std::vector<Node<int>*> allNodes; 
  allNodes.push_back(a);
  allNodes.push_back(b);
  allNodes.push_back(c);
  allNodes.push_back(d);
  allNodes.push_back(e);
  allNodes.push_back(f);
  allNodes.push_back(a);
  a->addEdge(b);
  b->addEdge(c);
  c->addEdge(d);
  d->addEdge(e);
  e->addEdge(b);
  e->addEdge(e);
  a->addEdge(d);
  f->addEdge(b);
  if(a->isCycleBruteForce(6, allNodes)){
    cout << "Brute ForceTest 9 failed" << endl;
  }
  else { 
    cout << "Brute Force Test 9 passed" << endl;
    didTestPass = true;
  }

  if(a->isCycleBacktracking(6)){
    cout << "Backtrack Test 9 failed" << endl;
    didTestPass = false;
  } 
  else { 
    cout << "Backtrack Test 9 passed" << endl;
  }
   return didTestPass;
}



bool Test10(){
  bool didTestPass = false;
  Node<int>* a = new Node<int>(1);
  Node<int>* b = new Node<int>(2);
  Node<int>* c = new Node<int>(3);
  Node<int>* d = new Node<int>(3);
  Node<int>* e = new Node<int>(3);
  Node<int>* f = new Node<int>(3);
  std::vector<Node<int>*> allNodes; 
  allNodes.push_back(a);
  allNodes.push_back(b);
  allNodes.push_back(c);
  allNodes.push_back(d);
  allNodes.push_back(e);
  allNodes.push_back(f);
  allNodes.push_back(a);
  a->addEdge(a);
  b->addEdge(c);
  c->addEdge(f);
  d->addEdge(e);
  e->addEdge(c);
  e->addEdge(d);
  a->addEdge(b);
  f->addEdge(b);
  //c->addEdge(a);
  if(a->isCycleBruteForce(6, allNodes)){
    cout << "Brute ForceTest 10 failed" << endl;
  }
  else { 
    cout << "Brute Force Test 10 passed" << endl;
    didTestPass = true;
    }

  if(a->isCycleBacktracking(6)){
    cout << "Backtrack Test 10 failed" << endl;
      didTestPass = false;
  } 
  else { 
    cout << "Backtrack Test 9 passed" << endl;
  }
   return didTestPass;
}

void runTests(){
  Node<int>* a = new Node<int>(1);
  int counter = 0;
  if(Test1()){counter++;}
  if(Test2()){counter++;}
  if(Test3()){counter++;}
  if(Test4()){counter++;}
  if(Test5()){counter++;}
  if(Test6()){counter++;}
  if(Test7()){counter++;}
  if(Test8()){counter++;}
  if(Test9()){counter++;}
  if(Test10()){counter++;}
  cout << "=========================" << endl;
  cout << "                       " << endl;
  cout << "    Tests passed: " << counter << "/10" << endl;
   cout << "                       " << endl;
  cout << "=========================" << endl;
}
