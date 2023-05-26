#ifndef _MODEL_HPP_
#define _MODEL_HPP_

#include "game.hpp"
//--------------------  Model ----------------------------

/// Simulation Model handling the game data structure.  
/// The model can communicate with the controller.
class GameModel {
public:
  GameModel() : game(nullptr) {}

  /// Creates a game
  void CreateGame(int level);

  /// Updates the game
  // - User chooses a node
  // - Then, the entity chooses a node
  int GetPlayerMove(int layer, int index);

  void printNodes();

  bool PostIsDone();

  state_t* PostGameState();

  entity_action_t* PostEntityMove();

protected:
  Game* game;
};

#endif
