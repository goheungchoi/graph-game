// controller.hpp
#ifndef _CONTROLLER_HPP_
#define _CONTROLLER_HPP_

#include "model.hpp"

#include "json_util.hpp"

using namespace boost::json;

//--------------------  Controller ----------------------------

/**
 * @brief Controller object for MVC model architecture of
 * the application
 * 
 */
class Controller {
public:
/**
 * @brief Construct a new Controller object
 * 
 * @param model pointer to a GameModel
 */
  Controller(GameModel* model) : model(model) {};

/**
 * @brief Receive a command from the view and execute 
 * a corresponding process
 * @details
 * <Command List>
 * - CreateGame: Discard the current game and create 
 * a new game in the model.
 * - GetPlayerMove: Receive a selected node from the view
 * and update the game in the model.
 * 
 * @param cmd Command line
 * @param data Data to be processed
 * @param returnValue (OPTIONAL) Returned value 
 * followed by a process of the command
 */
  void ReceiveCommand(
    const string& cmd, 
    object& data, 
    object& returnValue
  );
/**
 * @brief Send an event that happened in the model to
 * the view and request update of UI
 * 
 * @param event Any update or change that took place 
 * in the model
 * @param msg Details about the event
 */
  void SendMsgToView(
    const string& event,
    object& msg
  );

private:
  GameModel* model; //!< Model that communicates with the controller
/**
 * @brief Convert a node object to JSON value
 * 
 * @param node Pointer to Node to be converted
 * @return value - JSON value that contains information of the node
 */
  value convert_node_to_JSON(const Node* node);
/**
 * @brief Convert an edge object to JSON value
 * 
 * @param edge Pointer to Edge to be converted
 * @return value - JSON value that contains information of the edge
 */
  value convert_edge_to_JSON(const Edge* edge);
};

#endif