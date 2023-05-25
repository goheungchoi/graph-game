#ifndef _GAME_HPP_
#define _GAME_HPP_

#include "graph.hpp"
#include "player.hpp"
#include "entity.hpp"

#define _DONE 0
#define _IN_PROGRESS 1


struct state_t {
  const std::vector<Node*>* selected_nodes;
  const std::vector<Edge*>* player_edges;
  const std::vector<Node*>* consumed_nodes;
  const std::vector<Edge*>* entity_edges;

  const NodeMap* nodemap;
  const EdgeMap* edgemap;
};

struct entity_action_t {
  const std::vector<Node*>* new_entity_nodes; 
  const std::vector<Edge*>* new_entity_edges;
};

class Game {
public:
  Game(unsigned int level_);

  Game(unsigned int level_, 
    std::vector<Node> nodes, 
    std::vector<Edge> edges);

  ~Game();

  const state_t& getGameState();

  const entity_action_t& getEntityAction();


  int play_turn(int layer, int index);

  bool is_done();

private:
  state_t gameState;
  entity_action_t new_entity_action;

  Graph graph;
  Player player;
  Entity entity;

  
  unsigned int level = 0;
  int num_turn;
  int state;

  void initGameState();

  void initGraphWithRandomNodes();

};

#endif
