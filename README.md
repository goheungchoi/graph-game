# Graph Game Web 

**Author**: Goheung Choi

**Version**: *`0.8.0`*

**Last Update**: *05/26/23*

This project was bootstrapped with [Create React App](https://github.com/facebook/create-react-app).

## Overview

Inspired by the Blood Web system in Dead By Daylight, one of the most popular games on Steam.
The Blood Web is a unique shopping system of Dead By Daylight. A player purchases items and perks on the web, and after a certain amount of moves from the player, the Entity, the mighty and evil being that rules the DBD worldview, awakens and starts interfering player's moves.

This game follows slightly different rules. It involves selecting nodes on a graph as many as you can. After the 10th level, the Entity emerges and starts consuming nodes after your 5th move. However, instead of maximizing the player's spending of Blood points, the Entity tries to consume as many points as possible, similar to standard zero-sum games.

This is a project designed just for the personal practice of building a program based on the MVC model. The project is not yet complete and will require further development. 
Nevertheless, this project is well-structured enough to present the basic concepts of the MVC model and WebSocket connection between the server side and client side.

Here is the list of noticeable features of this project.

### Key Features

#### 1. Server written in C++
The whole server-side source files, including all the logic of the game and communication with the front-end, are implemented in C++ for efficient memory management and speed of the program.

#### 2. Use of Boost Library in C++
This project utilizes low-level I/O, WebSocket, and JSON object constructors/parsers provided by the [Boost Libary](https://www.boost.org/).

#### 3. Connection Threads
Theoretically, the server can handle multiple connections from clients, as it launches a thread every time it receives a WebSocket connection request.

#### 4. MVC Model
The server adheres to the MVC(Model-View-Controller) design pattern. The controller object transmits commands and data between the model and view, ensuring low-coupling among objects and clarity of the structure of this program.

#### 5. Use of React
The front-end is built in React JS, enhancing the reusability of objects and code.

#### 6. Use of Redux
The front-end uses Redux to maintain the state of the Graph object, preventing loss of data when refreshing the page.

## How to Use

**NOTE: The server can be run only on Linux Env**

(Future updates will include a CMake builder for cross-platform development)

**NOTE: Boost library must be installed on your local machine**

[Download Boost](https://www.boost.org/users/history/version_1_82_0.html)

1. Clone this repo `git clone https://github.com/goheungchoi/graph-game.git` in your preferred directory.
2. Open up two Linux Terminals: one for launching the server and the other for the browser UI.
3. For the Server, run
  ```
  bash> make 
  bash> ./bin/app 8080 
  ```
4. For the UI, run 
  ```
  bash> npm install
  bash> npm start
  ```
5. Once you start selecting nodes, the server, and UI will print logs of connection.

### How to Download Boost on Linux
Follow the walkthrough instructions on this [website](https://linux.how2shout.com/how-to-install-boost-c-on-ubuntu-20-04-or-22-04/).
Change the version of the library to 1.82.0.

## Documentation

Further details about key algorithms and the program structure are still under development and will be added to the following sections:

### Consumption of Entity
`TODO: fill this section`

### MVC Structure of Program
`TODO: fill this section`

## Future Development Roadout

The following enhancements are planned for future updates

- Addition of a CMake builder
- Bug Fix: Integration of UI and Redux.
  - Currently, integrating the app and Redux is not completely done yet.
- Development of the Random Node Generator in the Graph object in C++.
- Bug Fix: Extra attempt to send the 'CreateGame' command from the front-end
  - Currently, the UI sends the 'CreateGame' command twice when a level stage ends, demanding unnecessary resources from the server. 
  - I left it unchanged as it didn't affect the logic of the game.
- Development of the Entity Action Corresponding to Diverse Types and Rarity of Nodes
- Improvement of UI
  - More interactive and diverse functionality of the UI is required.
- Addition of a Log-in System and Data Storage
