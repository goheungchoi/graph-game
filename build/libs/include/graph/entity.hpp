#ifndef _ENTITY_
#define _ENTITY_

#include <vector>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include "graph.hpp"

class Entity {
public:
  Entity();
  ~Entity();

  int getNumOfConsumedNodes() {
    return consumedNodes.size();
  }

  /**
   * @brief Describes how Entity behaves after the user's move
   * 
   * @param g the web
   * @return int _FAIL if there is no more node left
   * _SUCCESS if Entity consumes a node
   */
  int action(Graph &g);
  /**
   * @brief A helper function for entity.behave. When the current path is ended,
   * find the next starting node. This function always searches from higher
   * layer to lower layer. Also, a node is chosen randomly from its layer.
   * 
   * @return Node* 
   */
  Node* getNextStartingNode(Graph &g);
  /**
   * @brief A helper function for getNextStartingNode(). If the next starting
   * node is on the third layer, it will search the closest node on the outer
   * layer and consume it first. Next, this function connects the origin of
   * Entity with the next starting node.
   * If there exists Entity at the node that this function tries to generate
   * Entity at, it will just connect the origin of Entity with the next starting
   * node.
   * 
   * @param g the web
   */
  void generateEntity(Graph &g, Node* n);
  /**
   * @brief travels a graph and finds the longest opened path that minimizes
   * consumption.
   * 
   * @param curr the current node
   * @param max the largest number of traveled nodes
   * @param count how many nodes are traveled
   * @param closedCount how many closed node exists on a path
   * @return true if the path is closed
   * @return false if the path is not closed
   */
  bool traversal(Node *curr, int &max, int &count, int &closedCount);
  /**
   * @brief searches for the next destination node of Entity
   * 
   * @param s 
   * @return Node* 
   */
  Node* searchNextConsumption(Node* s);
  /**
   * @brief This function shortly visits local paths and consumes closed paths
   * 
   * @param curr the node this function is visiting
   * @return true a path is closed
   * @return false a path is opened
   */
  bool local_traversal(Node* curr);
  /**
   * @brief A helper function for behave(). It finds closed paths of
   * the current node and automatically consumes them.
   * 
   * @param curr current node
   * @return true finished travarsel
   * @return false 
   */
  bool consumeClosedPaths(Node* curr);
  /**
   * @brief consumes nodes and connects each paths
   * 
   * @param node the node to be consumed
   */
  void consumeNode(Node* node);

  const std::vector<Node*>& getNewConsumedNodes() {
    return newConsumedNodes;
  }

  const std::vector<Edge*>& getNewEntityPath() {
    return newEntityPath;
  }

  const std::vector<Node*>& getConsumedNodes() {
    return consumedNodes;
  }

  const std::vector<Edge*>& getEntityPath() {
    return entityPath;
  }
private:
  Node* origin = nullptr;
  Node* curr = nullptr;
  std::vector<Node*> consumedNodes;
  std::vector<Edge*> entityPath;

  std::vector<Node*> newConsumedNodes;
  std::vector<Edge*> newEntityPath;
};

#endif