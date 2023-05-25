#include <boost/beast/core.hpp>
#include <boost/beast/websocket.hpp>
#include <boost/asio/ip/tcp.hpp>

#include <cstdlib>
#include <iostream>
#include <string>

#include "controller.hpp"
#include "json_util.hpp"

namespace beast = boost::beast;
namespace http = beast::http;
namespace websocket = beast::websocket;
namespace net = boost::asio;
using tcp = boost::asio::ip::tcp;
using namespace boost::json;

void do_session(tcp::socket socket, Controller& controller) {
  try {
    // Upgrade TCP protocal to a WebSocket connection
    websocket::stream<tcp::socket> ws{std::move(socket)};
    ws.accept();

    while(1) {
      // Read a message
      beast::flat_buffer buffer;
      ws.read(buffer);

      // Parse the message
      auto data = beast::buffers_to_string(buffer.data());

      // Parse the received data as JSON
      error_code ec;
      value json_data = parse(data);
      if (ec) {
        std::cerr << "Error: " << ec.message() << std::endl;
        return;
      }

      // Check that the JSON data is an object
      if(!json_data.is_object()) {
        std::cerr << "Error: JSON data is not an object" << std::endl;
        return;
      }

      object json_obj = json_data.as_object();
      // Check that the required fields exist
      if(!json_obj.contains("id") ||
        !json_obj.contains("cmd") || 
        !json_obj.contains("data")) {
        std::cerr << "Error: JSON object does not contain required fields" << std::endl;
        return;
      }

      // Use the controller to update the state of the game
      object returnValue;
      controller.ReceiveCommand(
        value_to<string>(json_obj["cmd"]),
        value_to<object>(json_obj["data"]),
        returnValue);

      // Use the controller to post the event corresponding to
      // the command
      object msg;
      msg["id"] = json_obj["id"];
      controller.SendMsgToView(
        value_to<string>(returnValue["event"]),
        msg);

      // Convert 'msg' back into a string
      std::string messageToSend = serialize(msg);

      // Store the string into a buffer
      beast::flat_buffer sendBuffer;
      beast::ostream(sendBuffer) << messageToSend;

      /// Send it back to the server
      // Ensure that the msg to be sent is the same type 
      // as the received msg
      ws.text(ws.got_text()); 
      // Write the send buffer to the WebSocket
      ws.write(sendBuffer.data());
    }
  }
  catch(beast::system_error const& se) {
    if(se.code() != websocket::error::closed)
      std::cerr << "Error: " << se.code().message() << std::endl;
  }
  catch(std::exception const& e) {
    std::cerr << "Error: " << e.what() << std::endl;
  }
}

int main(int argc, char** argv) {
  if (argc < 1) {
    std::cerr <<
      "usage: ./build/app <port>"
      << std::endl;
    return EXIT_FAILURE;
  }
  try {
    // Get the host and port of the server
    auto const host = net::ip::make_address("localhost");
    auto const port = static_cast<unsigned short>(std::atoi(argv[1]));

    // The io_context is required for all I/O
    net::io_context ioc;

    tcp::acceptor acceptor{ioc, {host, port}};
    while(1) {
      tcp::socket socket{ioc};
      acceptor.accept(socket);
      std::thread{std::bind(&do_session, std::move(socket))}.detach();
    }
  } catch(std::exception const& e) {
    std::cerr << "Error: " << e.what() << std::endl;
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}