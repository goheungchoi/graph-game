#ifndef _CONTROLLER_HPP_
#define _CONTROLLER_HPP_

#include "model.hpp"

#include "json_util.hpp"

using namespace boost::json;

//--------------------  Controller ----------------------------

// class IController {
//   virtual ~IController() {}

//   virtual void ReceiveCommand(
//     const std::string& cmd, 
//     object& data, 
//     object& returnValue
//   ) = 0;

//   virtual void SendMsgToView(
//     const std::string& event,
//     object& data
//   ) = 0;
// };

class Controller {
public:
  Controller(GameModel& model) : model(model) {};

  void ReceiveCommand(
    const string& cmd, 
    object& data, 
    object& returnValue
  ) {
    
      if (cmd == "CreateGame") {
        unsigned int level;
        obj::extract(data, "level", level);
        model.CreateGame(level);
        returnValue = {{
          "event", "PostGameState"
        }};
      }

      else if (cmd == "GetPlayerMove") {
        // User choose a node
        int layer, index;
        obj::extract(data, "layer", layer);
        obj::extract(data, "index", index);
        model.GetPlayerMove(layer, index);
        returnValue = {{
          "event", "PostEntityMove"
        }};
      }

  };

  void SendMsgToView(
    const string& event,
    object& msg
  ) {
    /* POST Game State */
    if (event == "PostGameState") {
      /// Make nodeMap JSON
      object nodemap;
      array nodes;
      for (const std::pair<std::vector<int>, Node*>& pair : 
      *model.PostGameState().nodemap) {
        Node* node = pair.second;
        value v = convert_node_to_JSON(node);
        nodes.emplace_back(v);
      }
      nodemap.emplace( "nodemap ", std::move(nodes) );

      /// Make edgeMap JSON
      object edgemap;
      array edges;
      for (const Edge& e : *model.PostGameState().edgemap) {
        value v = convert_edge_to_JSON(&e);
        edges.emplace_back(v);
      }
      edgemap.emplace( "edgemap ", std::move(edges) );
    
      /// Post the gamestate JSON
      msg["event"] = "gamestate";
      msg["details"] =
            {{"nodemap", std::move(nodemap)}, 
            {"edgemap", std::move(edgemap)}};
    }
    
    /* POST Entity Move */
    else if (event == "PostEntityMove") {
      /// Check if the game is over
      bool isdone = model.PostIsDone();

      /// Make player nodes JSON
      object playernodes;
      array player_nodes;
      for (const Node* node : 
      *model.PostGameState().selected_nodes) {
        value v = convert_node_to_JSON(node);
        player_nodes.emplace_back(v);
      }
      playernodes = {{"playernodes", std::move(player_nodes)}};

      /// Make player path JSON
      object playeredges;
      array player_edges;
      for (const Edge* edge : 
      *model.PostGameState().player_edges) {
        value v = convert_edge_to_JSON(edge);
        player_edges.emplace_back(v);
      }
      playeredges = {{"playeredge", std::move(player_edges)}};

      /// Make new nodes JSON
      object newnodes;
      array nodes;
      for (const Node* node : 
      *model.PostEntityMove().new_entity_nodes) {
        value v = convert_node_to_JSON(node);
        nodes.emplace_back(v);
      }
      newnodes = {{"newnodes", std::move(nodes)}};
    
      /// Make new edges JSON
      object newedges;
      array edges;
      for (const Edge* edge : 
      *model.PostEntityMove().new_entity_edges) {
        value v = convert_edge_to_JSON(edge);
        edges.emplace_back(v);
      }
      newedges = {{"newedges", std::move(edges)}};

      /// Post the new entity move JSON
      msg["event"] = "entitymove";
      msg["details"] = 
            {{"isdone", isdone},
              playernodes,
              playeredges,
              newnodes, 
              newedges};
    }
  }

private:
  GameModel& model;

  value convert_node_to_JSON(const Node* node) {
    // Color
    string color;
    switch (node->color) {
      case _WHITE:
      case _YELLOW:
        color = "white";
        break;
      case _RED:
        color = "red";
        break;
      case _BLACK:
        color = "black";
        break;
    }
    // Position
    int layer = node->getLayer();
    int index = node->getIndex();
    object pos{{"pos", {layer, index}}};
    // Content
    string type, rarity;
    switch (node->cont.type) {
      case _ITEM:
        type = "item";
        break;
      case _ADD_ON:
        type = "addon";
        break;
      case _OFFERING:
        type = "offering";
        break;
      case _PERK:
        type = "perk";
        break;
      default:
        type = "null";
    }
    switch (node->cont.rarity) {
      case _COMMON:
        rarity = "common";
        break;
      case _UNCOMMON:
        rarity = "uncommon";
        break;
      case _RARE:
        rarity = "rare";
        break;
      case _VERY_RARE:
        rarity = "very rare";
        break;
      case _ULTRA_RARE:
        rarity = "ultra rare";
        break;
      default:
        rarity = "null";
    }
    object cont{{"cont", {type, rarity}}};
    
    return value{
      std::move(color),
      std::move(pos),
      std::move(cont)
    };
  }

  value convert_edge_to_JSON(const Edge* edge) {
    return value{
      {array{edge->a[0], edge->a[1]}},
      {array{edge->b[0], edge->b[1]}}
    };
  }
};

#endif