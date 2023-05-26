#ifndef _GRAPH_
#define _GRAPH_

#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>

#include "node.hpp"
#include "edge.hpp"
#include "content.hpp"

#define _SUCCESS 1
#define _FAIL 0

const int LAYER_NUM_NODES[] = {1,6,12,12,6};

// NodeMap hash function
struct vector_hash_function {
  size_t operator()(const std::vector<int> &v) const {
    std::hash<int> hasher;
    size_t answer = 0;

    for (int i : v) {
      answer ^= hasher(i) + 0x9e3779b9 + (answer << 6) + (answer >> 2);
    }
    return answer;
  }
};
// EdgeMap hash function
struct edge_hash_function {
  size_t operator()(const Edge *edge) const {
    const std::vector<int> a(edge->a);
    const std::vector<int> b(edge->b);
    struct vector_hash_function hf;
    size_t a_sum = hf(a);
    size_t b_sum = hf(b);
    return a_sum + b_sum;
  }
};

// key: node->pos, value: Node*
// NodeMap[pos(layer, index)] => return Node* 
typedef std::unordered_map<std::vector<int>, Node*, vector_hash_function> 
  NodeMap;
// key: Edge(pos1, pos2)
typedef std::unordered_set<Edge*, edge_hash_function> 
  EdgeMap;

class Graph {
public:
  Graph();
  Graph(std::vector<Node> _nodes, std::vector<Edge> _edges);
  ~Graph();
  /*** GETTERS ***/
  std::vector<Node*> getUnvisitedNodesOnLayer(int layer);
  int getNumOfNodes() const;
  /***************/
  // tasks to be done prior to user selection
  // 1. add nodes
  // 2. add edges
  /**
   * @brief add a node to the graph.
   * 
   * @param cont 
   * @param layer 
   * @param index 
   */
  int addNode(const Content& cont, int layer, int index);
  /**
   * @brief add an edge to the graph.
   * 
   * @param x 2D position array
   * @param y 2D position array
   */
  int addEdge(const std::vector<int> x, const std::vector<int> y);
  /**
   * @brief search for a node at a certain position.
   * 
   * @param layer 
   * @param index 
   * @return Node* if found, returns Node* at the position. Otherwise, 
   * returns nullptr.
   */
  Node* searchNode(int layer, int index);

  NodeMap* getNodeMap() {
    std::cout << "Graph::getNodeMap: " << nodes << std::endl;
    return nodes;
  }

  void printNodeMap();

  EdgeMap* getEdgeMap() {
    return edges;
  }

private:
  unsigned int numOfNodes = 0;
  NodeMap* nodes;
  EdgeMap* edges;

  void init_web();
};

#endif