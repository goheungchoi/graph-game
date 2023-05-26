#include "model.hpp"

/// Creates a game
void GameModel::CreateGame(int level) {
  game = new Game(level);
}

/// Updates the game
// - User chooses a node
// - Then, the entity chooses a node
int GameModel::GetPlayerMove(int layer, int index) {
  int res = game->play_turn(layer, index);
  return res != -1 ? _SUCCESS : _FAIL;
}

void GameModel::printNodes() {
  game->print();
}

bool GameModel::PostIsDone() {
  return game->is_done();
}

state_t* GameModel::PostGameState() {
  return game->getGameState();
}

entity_action_t* GameModel::PostEntityMove() {
  return game->getEntityAction();
}
