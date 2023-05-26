#ifndef _GAME_HPP_
#define _GAME_HPP_

#include <cstdlib>
#include <ctime>

#include "graph.hpp"
#include "player.hpp"
#include "entity.hpp"

#define _DONE 0
#define _IN_PROGRESS 1


struct state_t {
  std::vector<Node*>* selected_nodes;
  std::vector<Edge*>* player_edges;
  std::vector<Node*>* consumed_nodes;
  std::vector<Edge*>* entity_edges;

  NodeMap* nodemap;
  EdgeMap* edgemap;
};

struct entity_action_t {
  std::vector<Node*>* new_entity_nodes; 
  std::vector<Edge*>* new_entity_edges;
};

class Game {
public:
  Game(int level_);

  Game(int level_, 
    std::vector<Node> nodes, 
    std::vector<Edge> edges);

  ~Game();

  state_t* getGameState();

  entity_action_t* getEntityAction();


  int play_turn(int layer, int index);

  bool is_done();

  void print() {
    graph.printNodeMap();
  }

private:
  state_t* gameState;
  entity_action_t* new_entity_action;

  Graph graph;
  Player player;
  Entity entity;

  
  int level = 0;
  int num_turn;
  int state;

  void initGameState();

  void initGraphWithRandomNodes();

};

#endif
