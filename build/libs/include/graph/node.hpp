#ifndef _NODE_
#define _NODE_

#include <vector>
#include <stdexcept>

#include "content.hpp"

// color
#define _WHITE 0  // Neutral
#define _YELLOW 1
#define _RED 2    // Chosen by the player
#define _BLACK -1 // Consumed by Entity

class Node {
public:
  int color;              // init: _WHITE
  std::vector<int> pos;   // init: {-1. -1}

  Content cont;

  Node();
  Node(int layer, int index);

  void setPosition(int layer, int index);
  void setContent(const Content& cont_);
  int getLayer() const;
  int getIndex() const;
  const std::vector<Node*>& getNeighbors() const { return neigh; };
  void addNeighbor(Node* const node);

private:
  std::vector<Node*> neigh;
};




#endif