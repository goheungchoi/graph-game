// game.cpp
#include "game.hpp"

Game::Game(int level_) : 
level(level_) {
  if (level_ > 0) {
    state = _IN_PROGRESS;
    // 1. Init the graph
    initGraphWithRandomNodes();
    // 2. Player choose the center
    player.action(graph, 0, 0);
    // 3. Init the game state
    initGameState();
  }
}

Game::Game(int level_, 
std::vector<Node> nodes, 
std::vector<Edge> edges) : 
level(level_) {
  if (level_ > 0) {
    state = _IN_PROGRESS;
    // 1. Init the graph
    graph = Graph(nodes, edges);
    // 2. Player choose the center
    player.action(graph, 0, 0);
    // 3. Init the game state
    initGameState();
  }
}

Game::~Game() {}

state_t* Game::getGameState() {
  return gameState;
}

entity_action_t* Game::getEntityAction() {
  return new_entity_action;
}


int Game::play_turn(int layer, int index) {
  if (is_done()) return -1;

  /* Entity's behavior */
  // 5 -> appears on the web
  // >5 -> consumes one by one
  
  std::cout << "Game::play_turn: num_turn="
  << num_turn << std::endl;
  if (level >= 10 && num_turn > 3) {
    // Player's action
    if (player.action(graph, layer, index) == _FAIL) {
      return -1;
    }
    std::cout << "Game::play_turn: player action done" << std::endl;
    // Entity's follow-up action
    if (entity.action(graph) == _FAIL) {
      state = _DONE;
      return -1;
    }
    std::cout << "Game::play_turn: entity action done" << std::endl;
  } else {
    if (player.action(graph, layer, index) == _FAIL) {
      return -1;
    }
  }

  int numOfSelectedNodes = player.getNumOfSelectedNodes();
  int numOfConsumedNodes = entity.getNumOfConsumedNodes();

  if (numOfSelectedNodes + numOfConsumedNodes >= graph.getNumOfNodes())
    state = _DONE;

  num_turn++;
  return 1;
}

bool Game::is_done() {
  return state == _DONE;
}

void Game::initGameState() {
  gameState = new state_t{};
  new_entity_action = new entity_action_t{};

  gameState->selected_nodes = &player.getSelectedNodes();
  gameState->player_edges = &player.getPlayerPath();
  gameState->consumed_nodes = &entity.getConsumedNodes();
  gameState->entity_edges = &entity.getEntityPath();

  gameState->nodemap = graph.getNodeMap();
  gameState->edgemap = graph.getEdgeMap();

  new_entity_action->new_entity_nodes = &entity.getNewConsumedNodes();
  new_entity_action->new_entity_edges = &entity.getNewEntityPath();
}

void Game::initGraphWithRandomNodes() {

  std::cout << "game level: " << level << std::endl;
  std::vector<int> v_0_0{0, 0};
  graph.addNode(Content(), 1, 0);
  std::vector<int> v_1_0{1, 0};
  graph.addNode(Content(), 1, 2);
  std::vector<int> v_1_2{1, 2};
  graph.addNode(Content(), 1, 3);
  std::vector<int> v_1_3{1, 3};
  graph.addNode(Content(), 1, 4);
  std::vector<int> v_1_4{1, 4};

  graph.addNode(Content(), 2, 0);
  std::vector<int> v_2_0{2, 0};
  graph.addNode(Content(), 2, 1);
  std::vector<int> v_2_1{2, 1};
  graph.addNode(Content(), 2, 3);
  std::vector<int> v_2_3{2, 3};
  graph.addNode(Content(), 2, 6);
  std::vector<int> v_2_6{2, 6};
  graph.addNode(Content(), 2, 8);
  std::vector<int> v_2_8{2, 8};
  graph.addNode(Content(), 2, 10);
  std::vector<int> v_2_10{2, 10};

  graph.addNode(Content(), 3, 0);
  std::vector<int> v_3_0{3, 0};
  graph.addNode(Content(), 3, 1);
  std::vector<int> v_3_1{3, 1};
  graph.addNode(Content(), 3, 2);
  std::vector<int> v_3_2{3, 2};
  graph.addNode(Content(), 3, 6);
  std::vector<int> v_3_6{3, 6};
  graph.addNode(Content(), 3, 7);
  std::vector<int> v_3_7{3, 7};
  graph.addNode(Content(), 3, 10);
  std::vector<int> v_3_10{3, 10};

  graph.addEdge(v_0_0, v_1_0);
  graph.addEdge(v_0_0, v_1_2);
  graph.addEdge(v_0_0, v_1_3);
  graph.addEdge(v_0_0, v_1_4);

  graph.addEdge(v_1_2, v_1_3);
  graph.addEdge(v_1_3, v_1_4);

  graph.addEdge(v_1_0, v_2_0);
  graph.addEdge(v_1_0, v_2_1);
  graph.addEdge(v_1_0, v_2_10);
  graph.addEdge(v_1_2, v_2_3);
  graph.addEdge(v_1_3, v_2_6);
  graph.addEdge(v_1_4, v_2_8);

  graph.addEdge(v_2_0, v_3_0);
  graph.addEdge(v_2_0, v_3_1);
  graph.addEdge(v_2_1, v_3_2);
  graph.addEdge(v_2_6, v_3_6);
  graph.addEdge(v_2_6, v_3_7);
  graph.addEdge(v_2_10, v_3_10);
  
}