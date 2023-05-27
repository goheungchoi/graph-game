// player.hpp
#ifndef _PLAYER_HPP_
#define _PLAYER_HPP_

#include <vector>

#include "graph.hpp"

class Player {
public:
  Player() {}
  ~Player();

/**
 * @brief Get the number of selected nodes
 * 
 * @return int - the number of selected nodes
 */
  int getNumOfSelectedNodes();

  std::vector<Node*>& getSelectedNodes();

  std::vector<Edge*>& getPlayerPath();
/**
 * @brief Basic movement pattern of the player.
 * 
 * @param g 
 * @param layer 
 * @param index 
 * @return int 
 */
  int action(Graph &g, int layer, int index);

private:
  std::vector<Node*> selectedNodes;
  std::vector<Edge*> playerPath;

/**
 * @brief Helper function for action()
 * 
 * @param node 
 */
  void update(Node* node);
/**
 * @brief Helper function for action()
 * 
 * @param node 
 */
  void createUserPath(Node* node);
};

#endif