// model.hpp
#ifndef _MODEL_HPP_
#define _MODEL_HPP_

#include "game.hpp"
//--------------------  Model ----------------------------

/**
 * @brief Simulation Model handling the game data structure.  
 * The model can communicate with the controller.
 */
class GameModel {
public:
/**
 * @brief Default Contructor
 * 
 */
  GameModel() : game(nullptr) {}
/**
 * @brief Create a new Game object. If the game already exists,
 * destroy the old Game object and create new one.
 * 
 * @param level Level of the new game
 */
  void CreateGame(int level);
/**
 * @brief Get the new selection of the player and 
 * update the game 
 * 
 * @param layer Layer of the selected node
 * @param index Index of the selected node
 * @return int - 1 for success and -1 for fail
 */
  int GetPlayerMove(int layer, int index);
/**
 * @brief Debugging purpose function
 */
  void printNodes();
/**
 * @brief Notify that the game ends
 * 
 * @return true - the game is over
 * @return false - the game is still running
 */
  bool PostIsDone();
/**
 * @brief Send the state of the game
 * 
 * @return state_t* - Pointer to the state struct 
 * that contains information about the game, 
 * such as NodeMap, EdgeMap, player path, 
 * and the entity path
 */
  state_t* PostGameState();
/**
 * @brief Send the new moves of the Entity
 * 
 * @return entity_action_t* - Pointer to the struct
 * that contains information about the new moves of
 * the Entity, such as new consumed nodes and new
 * Entity path
 */
  entity_action_t* PostEntityMove();

protected:
  Game* game;
};

#endif
