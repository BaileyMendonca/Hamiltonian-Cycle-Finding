#include <vector>
#include <algorithm>
#include <iostream>
#include <bits/stdc++.h>
using namespace std;

#ifndef NODE
#define NODE


template <class Element>
class Node{
public:
  Node(Element);
  bool isCycleBruteForce(int, std::vector<Node<Element>*>);
  bool isCycleBacktracking(int);
  // Node functions
  void addEdge(Node*);
  // Getters
  Element getValue();
  std::vector<Node*>* getEdges();
  // Setters
  void setValue(Element);
  // virtual bool isCycle(int, std::vector<Node<Element>*>);
private:
  std::vector<Node*> edges;
  Element value;
  bool isCycleBruteForce(Node*, int, int, std::vector<Node<Element>*>);
  bool isCycleBacktracking(Node*, int, int, std::vector<Node*>);
  bool checkPermutationForCycle(int, int, std::vector<Node<Element>*>);
};

template <class Element>
Node<Element>::Node(Element e){
  value = e;
  edges = {};
};
// Node functions
template <class Element>
void Node<Element>::addEdge(Node* node){
  edges.push_back(node);
  node->edges.push_back(this);
};
// Getters
template <class Element>
Element Node<Element>::getValue(){
  return value;
};
template <class Element>
std::vector<Node<Element>*>* Node<Element>::getEdges(){
  return &edges;
};
// Setters
template <class Element>
void Node<Element>::setValue(Element e){
  value = e;
};
#endif


//========================
// Brute Force Solution 
//========================

template <class Element>
bool Node<Element>::checkPermutationForCycle(int expectedSize, int counter, std::vector<Node<Element>*> allNodes){
  //for all nodes in the permutation
    for(int i = 1; i < allNodes.size(); i++){
      //check the trivial case where a node has no edges (impossible to have a hamiltonian cycle)
      if(allNodes[i]->edges.size() == 0){
        return false;
      }
      bool isEdge = false;
      // Search current nodes edges to see if the previous node is connected to it
      for(int j = 0; j < allNodes[i]->edges.size(); j++){ 
        if(allNodes[i - 1] == allNodes[i]->edges[j]){
          isEdge = true;
          break;
        }
      }
      if(!isEdge){ // If the current node is not connected to the previous node
        return false; // Immediately return false
      }
    }

  return true;
}

template <class Element>
bool Node<Element>::isCycleBruteForce(Node* node, int expectedSize, int counter, std::vector<Node<Element>*> allNodes){
  //checks base case
   if(checkPermutationForCycle(expectedSize, counter, allNodes)){return true;}
  //permutates every value apart from the first node and last node
  while(next_permutation(allNodes.begin() + 1, allNodes.end() - 1)){
    //checks all following permutations
    if(checkPermutationForCycle(expectedSize, counter, allNodes)){return true;}
  }
  //if base case or perms don't have a cycle then return fasle
  return false;
};

// g++ main.cpp -o main.o
// ./main.o
template <class Element>
//entry function
bool Node<Element>::isCycleBruteForce(int expectedSize, std::vector<Node<Element>*> allNodes){
  return this->isCycleBruteForce(this, expectedSize, 0, allNodes);
};




//========================
// Backtracking solution
//========================
template <class Element>
bool Node<Element>::isCycleBacktracking(Node* node, int count, int expectedSize, std::vector<Node*> visited){
  if(!node){
    return false;
  }
  // A singular node is counted as a Hamiltonian cycle
  if(node->getEdges()->size() == 0){
    return true;
  }
  std::vector<Node*> newVisited = visited; // TODO: double check memory handling with visited
  newVisited.push_back(node);
  bool unvisitedNodeFound = false;
  for(Node* n : *node->getEdges()){
    // If the node is unfound in "visited", i.e. is it unvisited in the current path
    if(std::find(newVisited.begin(), newVisited.end(), n) == newVisited.end()){
      unvisitedNodeFound = true;
      if(isCycleBacktracking(n, count+1, expectedSize, newVisited)){
        return true;
      }
    }
  }
  
  if(!unvisitedNodeFound){ // If there are no nodes left to visit
    // Check if the current node connects back to the start
    // Return true if it does, return false if it doesn't
    return count == expectedSize && std::find(node->getEdges()->begin(), node->getEdges()->end(), this) != node->getEdges()->end();
  }
  return false;
};
template <class Element>
bool Node<Element>::isCycleBacktracking(int expectedSize){
  std::vector<Node*> visited = {};
  return isCycleBacktracking(this, 1, expectedSize, visited);
};


//Questions for Luke. 
//is 1 node a ham cycle?