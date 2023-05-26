// graph.cpp
#include "graph.hpp"
#include "entity.hpp"

Graph::Graph() {
  nodes = new NodeMap();
  edges = new EdgeMap();
  init_web();
}

Graph::Graph(std::vector<Node> _nodes, std::vector<Edge> _edges) {
  nodes = new NodeMap();
  edges = new EdgeMap();
  for (Node& n : _nodes) {
    Node* newNode = new Node(n);
    int layer = n.getLayer();
    int index = n.getIndex();
    // IF first node THEN colored _YELLOW
    if (n.cont.type == _NULL_TYPE && layer == 0 && index == 0)
      newNode->color = _YELLOW;
    // stores the node in the nodes array
    std::pair<std::vector<int>, Node*> p(n.pos, newNode);
    nodes->insert(p);
  }

  for (Edge& e : _edges) {
    Edge* newEdge = new Edge(e);
    edges->insert(newEdge);
    Node* a = searchNode(e.a.at(0), e.a.at(1));
    Node* b = searchNode(e.b.at(0), e.b.at(1));
    if (a == nullptr || b == nullptr) 
      std::invalid_argument("Graph.hpp: node in edges array doesn't exist");
    a->addNeighbor(b);
    b->addNeighbor(a);
  }
}

Graph::~Graph() {
  for (auto it = nodes->begin(); it != nodes->end(); it++) {
    delete it->second;
  }

  for (auto it = edges->begin(); it != edges->end(); it++) {
    delete *it;
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
  return nodes->size();
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
  // Stores the node in the nodes array
  std::pair<std::vector<int>, Node*> p(n->pos, n);
  NodeMap::iterator it = nodes->find(n->pos);
  nodes->insert(p);
  // SUCCESS

  it = nodes->find(n->pos);
  std::cout << "Graph::addNode: node is added successfully" << std::endl;
  std::cout << "node: (" << it->second->getLayer() << ", " << it->second->getIndex() << ") " << std::endl;

  return _SUCCESS;
}
/**
 * @brief Add an edge to the graph.
 * 
 * @param x 2D position array
 * @param y 2D position array
 */
int Graph::addEdge(const std::vector<int> x, const std::vector<int> y) {
  // Prevent cycle on a graph
  if (x == y) return _FAIL;

  auto a_it = nodes->find(x);
  auto b_it = nodes->find(y);
  if (a_it == nodes->end() || b_it == nodes->end()) {
      std::cerr << "Graph::addEdge: err: node is not found" << std::endl;
      std::cerr << "x: (" << x[0] << ", " << x[1] << ") "  "y: (" << y[0] << ", " << y[1] << ") " << std::endl;
      return _FAIL;
  }
  Node* a = a_it->second;
  Node* b = b_it->second;

  // Node* a = nodes.at(x);
  // Node* b = nodes.at(y);
  std::cout << "found nodes" << std::endl;
  std::cout << "x: (" << x[0] << ", " << x[1] << ") "  "y: (" << y[0] << ", " << y[1] << ") " << std::endl;
  a->addNeighbor(b);
  b->addNeighbor(a);
  edges->insert(new Edge(x, y));
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

  NodeMap::const_iterator it = nodes->find(pos);
  if (it == nodes->end()) return nullptr;
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

void Graph::printNodeMap() {
  std::cout << "Graph::printNodeMap: print nodemap" << std::endl;
  for (auto it = nodes->begin(); it != nodes->end(); it++) {
    std::string color = "";
    switch (it->second->color)
    {
    case -1:
      color="black";
      break;
    case 0:
      color="white";
      break;
    case 1:
      color="yellow";
      break;
    case 2:
      color="red";
      break;
    
    default:
      color="null";
      break;
    }

    std::cout << "Graph::printNodeMap: key=(" << it->first[0] << ", " << it->first[1] << ")" <<
    " -> Node(" << color << ", " << it->second->getLayer() << ", " << it->second->getIndex() << ")" << std::endl;
  }
}