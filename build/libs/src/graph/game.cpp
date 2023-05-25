#include "game.hpp"

Game::Game(unsigned int level_) : 
level(level_) {
  state = _IN_PROGRESS;
  // 1. Init the graph
  initGraphWithRandomNodes();
  // 2. Player choose the center
  player.action(graph, 0, 0);
  // 3. Init the game state
  initGameState();
}

Game::Game(unsigned int level_, 
  std::vector<Node> nodes, 
  std::vector<Edge> edges) : 
level(level_) {
  state = _IN_PROGRESS;
  // 1. Init the graph
  graph = Graph(nodes, edges);
  // 2. Player choose the center
  player.action(graph, 0, 0);
  // 3. Init the game state
  initGameState();
}

Game::~Game() {

}

const state_t& Game::getGameState() {
  return gameState;
}

const entity_action_t& Game::getEntityAction() {
  return new_entity_action;
}


int Game::play_turn(int layer, int index) {
  if (is_done()) return -1;

  /* Entity's behavior */
  // 5 -> appears on the web
  // >5 -> consumes one by one
  if (level >= 10 && num_turn > 4) {
    // Player's action
    if (player.action(graph, layer, index) == _FAIL) {
      return -1;
    }
    // Entity's follow-up action
    if (entity.action(graph) == _FAIL) {
      state = _DONE;
      return -1;
    }
  } else {
    if (player.action(graph, layer, index) == _FAIL) {
      state = _DONE;
      return -1;
    }
  }

  int numOfSelectedNodes = player.getNumOfSelectedNodes();
  int numOfConsumedNodes = entity.getNumOfConsumedNodes();

  if (numOfSelectedNodes + numOfConsumedNodes >= graph.getNumOfNodes())
    state = _DONE;

  return 1;
}

bool Game::is_done() {
  return state == _DONE;
}

void Game::initGameState() {
  gameState.selected_nodes = &player.getSelectedNodes();
  gameState.player_edges = &player.getPlayerPath();
  gameState.consumed_nodes = &entity.getConsumedNodes();
  gameState.entity_edges = &entity.getEntityPath();

  gameState.nodemap = &graph.getNodeMap();
  gameState.edgemap = &graph.getEdgeMap();
}

void Game::initGraphWithRandomNodes() {
  
}