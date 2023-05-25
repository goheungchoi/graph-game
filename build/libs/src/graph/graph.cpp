#include "graph.hpp"
#include "entity.hpp"

Entity entity;

Graph::Graph() {
  init_web();
}

Graph::Graph(std::vector<Node> _nodes, std::vector<Edge> _edges) {
  for (Node& n : _nodes) {
    int layer = n.getLayer();
    int index = n.getIndex();
    // IF first node THEN colored _YELLOW
    if (n.cont.type == _NULL_TYPE && layer == 0 && index == 0)
      n.color = _YELLOW;
    // stores the node in the nodes array
    std::pair<std::vector<int>, Node*> p(n.pos, &n);
    nodes.insert(p);
    // increment the number of nodes on the web
    numOfNodes++;
  }

  for (Edge& e : _edges) {
    edges.insert(e);
    Node* a = searchNode(e.a.at(0), e.a.at(1));
    Node* b = searchNode(e.b.at(0), e.b.at(1));
    if (a == nullptr || b == nullptr) 
      std::invalid_argument("Graph.hpp: node in edges array doesn't exist");
    a->addNeighbor(b);
    b->addNeighbor(a);
  }
}

Graph::~Graph() {
  for (auto it = nodes.begin(); it == nodes.end(); it++) {
    delete it->second;
  }
}
/*** GETTERS ***/
std::vector<Node*> Graph::getUnvisitedNodesOnLayer(int layer) {
  /* validation layer */
  if (layer < 0 || layer / 5 > 0)
    throw std::invalid_argument("Graph.hpp: layer is out of range");

  std::vector<Node*> unvisitedNodesOnLayer;
  
  for (int i = 0; i < LAYER_NUM_NODES[layer]; i++) {
    Node* n = searchNode(layer, i);
    if (n != nullptr && (n->color == _WHITE || n->color == _YELLOW))
      unvisitedNodesOnLayer.push_back(n);
  }
  return unvisitedNodesOnLayer;
}

int Graph::getNumOfNodes() const {
  return numOfNodes;
}
/***************/
// tasks to be done prior to user selection
// 1. add nodes
// 2. add edges
/**
 * @brief Add a node to the graph.
 * 
 * @param cont 
 * @param layer 
 * @param index 
 */
int Graph::addNode(const Content& cont, int layer, int index) {
  /* varification layer */
  if (searchNode(layer, index) != nullptr) 
    return _FAIL;
  // initialize the node
  // nodes will be stored on heap
  // and other data structures share 
  // their addresses
  Node* n = new Node(layer, index);
  n->setContent(cont);
  // IF first node THEN colored _YELLOW
  if (cont.type == _NULL_TYPE && layer == 0 && index == 0)
    n->color = _YELLOW;
  // stores the node in the nodes array
  std::pair<std::vector<int>, Node*> p(n->pos, n);
  nodes.insert(p);
  // increment the number of nodes on the web
  numOfNodes++;
  // SUCCESS
  return _SUCCESS;
}
/**
 * @brief Add an edge to the graph.
 * 
 * @param x 2D position array
 * @param y 2D position array
 */
int Graph::addEdge(const std::vector<int> x, const std::vector<int> y) {
  if (x == y) return _FAIL;
  edges.insert(Edge(x, y));
  Node* a = nodes.at(x);
  Node* b = nodes.at(y);
  a->addNeighbor(b);
  b->addNeighbor(a);
  return _SUCCESS;
}

/**
 * @brief Search for a node at a certain position.
 * 
 * @param layer 
 * @param index 
 * @return Node* if found, returns Node* at the position. Otherwise, 
 * returns nullptr.
 */
Node* Graph::searchNode(int layer, int index) {
  std::vector<int> pos{layer, index};

  NodeMap::const_iterator it = nodes.find(pos);
  if (it == nodes.end()) return nullptr;
  else return it->second;
}

/**
 * @brief Initializes the web
 * 
 */
void Graph::init_web() {
  // select the origin as the first node
  addNode(Content(), 0, 0);
}