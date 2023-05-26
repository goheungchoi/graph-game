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
  void update(Node* node);

  /**
   * @brief Helper function for userSelectNode
   * 
   * @param node 
   */
  void createUserPath(Node* node);

  std::vector<Node*>& getSelectedNodes();

  std::vector<Edge*>& getPlayerPath();
private:
  std::vector<Node*> selectedNodes;
  std::vector<Edge*> playerPath;
};

#endif