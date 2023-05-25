// player.cpp
#include "player.hpp"

Player::~Player() {
    for (Edge* e : playerPath) {
      delete e;
    }
  }

int Player::getNumOfSelectedNodes() {
  return selectedNodes.size();
}


int Player::action(Graph &g, int layer, int index) {
  // find the node
  Node* selectedNode = g.searchNode(layer, index);
  /* validation layer */
  // 1. not found
  if (selectedNode == nullptr)  
    return _FAIL;
  // 2. not adjancent to any user nodes
  if (selectedNode->color != _YELLOW)
    return _FAIL;
  
  // Update the path 
  // and mark the neighbor nodes
  update(selectedNode);
  
  return _SUCCESS;
}

/**
 * @brief 
 * 
 * @param node 
 * @return int 
 */
int Player::update(Node* node) {
  // Creates a path to the node
  createUserPath(node);
  // Select the node
  selectedNodes.push_back(node);
  node->color = _RED;
  // find adjacent nodes
  for (Node* n : node->getNeighbors()) {
    // marks only unvisited nodes
    if (n->color == _WHITE)
      n->color = _YELLOW;
  }
}

/**
 * @brief Helper function for userSelectNode
 * 
 * @param node 
 */
void Player::createUserPath(Node* node) {
  /* validation layer */
  // if there is only one selected node
  // no path
  if (selectedNodes.size() < 1) return;
  
  /// make an edge and add to the user's path
  // Find the recently added "neighbor" node
  Node* prev = nullptr;
  int size = selectedNodes.size();
  int index = -1;
  for (Node* n : node->getNeighbors()) {
    if (n->color != _RED) continue;
    // Max search
    // Time Complexity
    // Best Case:  O(1)
    // Ave. Case:  O(n)
    // Worst Case: O(n)
    // This is suitable in this case, 
    // as recently added nodes will be placed
    // on the top of the vector.
    for (int i = size-1; i>index; i--) {
      if (selectedNodes[i] == n) {
        prev = n;
        index = i;
      }
    }
  }
  // If prev is not found, something is wrong
  // with this algorithm
  if (prev == nullptr) return;
  // Add the path to the playerPath vector
  playerPath.push_back(new Edge(prev->pos, node->pos));
  std::vector<Node*> ref = getSelectedNodes();
}

const std::vector<Node*>& Player::getSelectedNodes() {
  return selectedNodes;
}

const std::vector<Edge*>& Player::getPlayerPath() {
  return playerPath;
}