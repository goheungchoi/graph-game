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
  Controller(GameModel* model) : model(model) {};

  void ReceiveCommand(
    const string& cmd, 
    object& data, 
    object& returnValue
  );

  void SendMsgToView(
    const string& event,
    object& msg
  );

private:
  GameModel* model;

  value convert_node_to_JSON(const Node* node);

  value convert_edge_to_JSON(const Edge* edge);
};

#endif