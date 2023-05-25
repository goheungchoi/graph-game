#ifndef _PLAYER_HPP_
#define _PLAYER_HPP_

#include <vector>

#include "graph.hpp"

class Player {
public:
  Player() {}
  ~Player();

  int getNumOfSelectedNodes();

  int action(Graph &g, int layer, int index);

  /**
   * @brief 
   * 
   * @param node 
   * @return int 
   */
  int update(Node* node);

  /**
   * @brief Helper function for userSelectNode
   * 
   * @param node 
   */
  void createUserPath(Node* node);

  const std::vector<Node*>& getSelectedNodes();

  const std::vector<Edge*>& getPlayerPath();
private:
  std::vector<Node*> selectedNodes;
  std::vector<Edge*> playerPath;
};

#endif