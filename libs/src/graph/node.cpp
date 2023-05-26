#include "node.hpp"

Node::Node() {
  color = _WHITE;
  pos = std::vector<int>(2, -1);
}

Node::Node(int layer, int index) {
  color = _WHITE;
  pos = std::vector<int>(2, -1);  // Initialize the size and temp values
  setPosition(layer, index);
}

void Node::setPosition(const int layer, const int index) {
  /* validation layer */
  switch (layer) {
    case 0:
      if (index / 1 > 0)
        throw std::invalid_argument("Node.hpp: index is out of range");
      break;
    case 1:
      if (index / 6 > 0)
        throw std::invalid_argument("Node.hpp: index is out of range");
      break;
    case 2:
      if (index / 12 > 0)
        throw std::invalid_argument("Node.hpp: index is out of range");
      break;
    case 3:
      if (index / 12 > 0)
        throw std::invalid_argument("Node.hpp: index is out of range");
      break;
    case 4:  // Entity
      if (index / 6 > 0)
        throw std::invalid_argument("Node.hpp: index is out of range");
      break;
    default:
      throw std::invalid_argument("Node.hpp: layer is out of range");
  }

  pos[0] = layer;
  pos[1] = index;
}

void Node::setContent(const Content& cont_) {
  cont = cont_;
}

int Node::getLayer() const { return pos.at(0); }

int Node::getIndex() const { return pos.at(1); }

void Node::addNeighbor(Node* const node) {
  neigh.push_back(node);
}
