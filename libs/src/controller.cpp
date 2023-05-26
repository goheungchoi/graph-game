#include "controller.hpp"

void Controller::ReceiveCommand(
  const string& cmd, 
  object& data, 
  object& returnValue
) {
  
    if (cmd == "CreateGame") {
      unsigned int level;
      obj::extract(data, "level", level);
      model->CreateGame(level);
      returnValue = {{
        "event", "PostGameState"
      }};
    }

    else if (cmd == "GetPlayerMove") {
      // User choose a node
      int layer, index;
      obj::extract(data, "layer", layer);
      obj::extract(data, "index", index);
      int res = model->GetPlayerMove(layer, index);

      returnValue = {{
        "event", "PostEntityMove"
      }};
      std::cout << "Controller::ReceiveCommand: pos=(" 
      << layer << ", " << index<<")" << std::endl;
    }

}

void Controller::SendMsgToView(
  const string& event,
  object& msg
) {
  /* POST Game State */
  if (event == "PostGameState") {
    object details;
    /// Make nodeMap JSON
    array nodes;
    std::cout << "Controller::SendMsgToView: loop start" << std::endl;
    NodeMap* nodesp = model->PostGameState()->nodemap;
    std::cout << "Controller::SendMsgToView: " << nodesp << std::endl;

    model->printNodes();
    // bool isempty = nodesp->empty();
    // std::cout << "Controller::SendMsgToView: nodemap.empty? " << isempty << std::endl;
    for (auto it = nodesp->begin(); it != nodesp->end(); it++) {
      std::cout << "Controller::SendMsgToView: " 
      << "Node(" << it->second->getLayer() << ", " << it->second->getIndex() << ")" << std::endl;
      value v = convert_node_to_JSON(it->second);
      nodes.emplace_back(v);
    }

    details.emplace( "nodemap", std::move(nodes) );
    std::cout << "Controller::SendMsgToView: nodemap created" << std::endl;

    /// Make edgeMap JSON
    array edges;
    for (const Edge* e : *model->PostGameState()->edgemap) {
      std::cout << "Controller::SendMsgToView: " 
      << "Edge([" << e->a[0] << ", " << e->a[1] << "], [" 
      << e->b[0] << ", " << e->b[1] << "])" << std::endl;
      value v = convert_edge_to_JSON(e);
      edges.emplace_back(v);
    }
    details.emplace( "edgemap", std::move(edges) );
    std::cout << "Controller::SendMsgToView: edgemap created" << std::endl;
  
    /// Post the gamestate JSON
    msg["event"] = "gamestate";
    msg["details"] = std::move(details);
  }
  
  /* POST Entity Move */
  else if (event == "PostEntityMove") {
    model->printNodes();
    object details;
    /// Check if the game is over
    bool isdone = model->PostIsDone();
    std::cout << "Controller::SendMsgToView: isdone?=" << isdone << std::endl; 
    details.emplace( "isdone" , isdone );

    /// Make player nodes JSON
    object playernodes;
    array player_nodes;
    for (const Node* node : 
    *model->PostGameState()->selected_nodes) {
      std::cout << "Controller::SendMsgToView: " 
      << "PlayerNode(" << node->getLayer() << ", " 
      << node->getIndex() << ")" << std::endl;
      value v = convert_node_to_JSON(node);
      player_nodes.emplace_back(v);
    }
    details.emplace( "playernodes", std::move(player_nodes) );
    std::cout << "Controller::SendMsgToView: playernodes created" << std::endl;

    /// Make player path JSON
    object playeredges;
    array player_edges;
    for (const Edge* edge : 
    *model->PostGameState()->player_edges) {
      std::cout << "Controller::SendMsgToView: " 
      << "PlayerEdge([" << edge->a[0] << ", " << edge->a[1] << "], [" 
      << edge->b[0] << ", " << edge->b[1] << "])" << std::endl;
      value v = convert_edge_to_JSON(edge);
      player_edges.emplace_back(v);
    }
    details.emplace( "playeredges", std::move(player_edges) );
    std::cout << "Controller::SendMsgToView: playeredges created" << std::endl;

    /// Make new nodes JSON
    object newnodes;
    array nodes;
    for (const Node* node : 
    *model->PostEntityMove()->new_entity_nodes) {
      std::cout << "Controller::SendMsgToView: " 
      << "EntityNode(" << node->getLayer() << ", " 
      << node->getIndex() << ")" << std::endl;
      value v = convert_node_to_JSON(node);
      nodes.emplace_back(v);
    }
    details.emplace( "newnodes", std::move(nodes) );
    std::cout << "Controller::SendMsgToView: newnodes created" << std::endl;
  
    /// Make new edges JSON
    object newedges;
    array edges;
    for (const Edge* edge : 
    *model->PostEntityMove()->new_entity_edges) {
      std::cout << "Controller::SendMsgToView: " 
      << "EntityEdge([" << edge->a[0] << ", " << edge->a[1] << "], [" 
      << edge->b[0] << ", " << edge->b[1] << "])" << std::endl;
      value v = convert_edge_to_JSON(edge);
      edges.emplace_back(v);
    }
    details.emplace( "newedges", std::move(edges) );
    std::cout << "Controller::SendMsgToView: newedges created" << std::endl;

    /// Post the new entity move JSON
    msg["event"] = "entitymove";
    msg["details"] = std::move(details);
  }
}

value Controller::convert_node_to_JSON(const Node* node) {
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

value Controller::convert_edge_to_JSON(const Edge* edge) {
  return value{
    {array{edge->a[0], edge->a[1]}},
    {array{edge->b[0], edge->b[1]}}
  };
}
