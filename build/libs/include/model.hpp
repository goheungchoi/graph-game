#ifndef _MODEL_HPP_
#define _MODEL_HPP_

#include "graph\game.hpp"
#include "controller.hpp"

//--------------------  Model ----------------------------

/// Simulation Model handling the game data structure.  
/// The model can communicate with the controller.
class GameModel {
public:
  GameModel(Controller& controller) :
  controller(controller), game(Game(0)) {}

  /// Creates a game
  void CreateGame(unsigned int level) {
    game = Game(level);
  }

  /// Updates the game
  // - User chooses a node
  // - Then, the entity chooses a node
  void GetPlayerMove(int layer, int index) {
    game.play_turn(layer, index);
  }

  bool PostIsDone() {
    return game.is_done();
  }

  const state_t& PostGameState() {
    return game.getGameState();
  }

  const entity_action_t& PostEntityMove() {
    return game.getEntityAction();
  }

protected:
  Controller& controller;
  Game game;
};

#endif
