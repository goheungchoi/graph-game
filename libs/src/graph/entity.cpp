// entity.cpp
#include "entity.hpp"

Entity::Entity() {}

Entity::~Entity() {
  for (Edge* e : entityPath) {
    delete e;
  }
}

int Entity::action(Graph &g) {
  // Reset the achieve vectores that records
  // new nodes and edges
  newConsumedNodes.clear();
  newEntityPath.clear();

  // Find the next node to go
  Node* next = searchNextConsumption(curr);
  std::cout << "Entity::action: search next node" << std::endl;
  if (next == nullptr)  // if the current path is ended
    // Find a new starting node
    next = getNextStartingNode(g);
  // if all the nodes in the web is taken
  if (next == nullptr) return _FAIL;  // notify the game is over
  
  consumeNode(next);
  std::cout << "Entity::action: consume next node" << std::endl;
  consumeClosedPaths(next);
  return _SUCCESS;
}

Node* Entity::getNextStartingNode(Graph &g) {
  std::cout << "Entity::getNextStartingNode: get next starting node" << std::endl;
  for (int i = 3; i > 0; i--) {
    std::vector<Node*> unvisitedNodesOnLayer = g.getUnvisitedNodesOnLayer(i);
    if (unvisitedNodesOnLayer.size() != 0) {
      srand(time(0));
      int ranIndex = rand() % unvisitedNodesOnLayer.size();
      Node* next = unvisitedNodesOnLayer[ranIndex];
      if (i == 3 &&   // if next starting point is on third layer
          origin == nullptr) {  // and origin is not set yet
        // it has to connect it with the entity 
        generateEntity(g, next);
      }
      return next;
    }
  }
  return nullptr;
}

void Entity::generateEntity(Graph &g, Node* n) {
  int index = n->pos[1];      //!< index of the node
  int newi = ((index+1)%12)/2;//!< index of the 4th layer node 
                              //   that will be connected to the node

  g.addNode(Content(), 4, newi);
  origin = g.searchNode(4, newi);
  g.addEdge(origin->pos, n->pos);
  consumeNode(origin);
}


bool Entity::traversal(Node *curr, int &max, int &count, int &closedCount) {
  int temp_color = curr->color;
  curr->color = _BLACK;
  count += 1;
  // goes to adjacent nodes which are not visited or taken
  // check if there is at least one open child path
  // if it is, this path is not closed
  bool deadend = true;
  bool closed = true;
  for (Node* next : curr->getNeighbors()) {
    // if a node is unvisited or not taken
    // visits the node
    if (next->color == _WHITE ||
        next->color == _YELLOW) {  // color = WHITE | YELLOW
      // check if a child path is closed or not
      bool local_closed = traversal(next, max, count, closedCount);
      // check if the current path is closed or not
      closed &= local_closed;
      // this path is not a deadend
      deadend = false;
    }
    // if there is an adjacent node colored red
    // this path is not closed yet
    if (next->color == _RED) {
      closed &= false;
    }
  }
  // if this is a closed path  
  if (closed) { closedCount += 1; } 
  else {  // if not closed path
    // this path reaches at the end
    if (deadend) {
      if (count > max) {  // find the max count
        max = count;
      }
    }
  }
  // reset the color
  curr->color = temp_color;
  // reset the count and localPath
  count -= 1;

  return closed;
}

Node* Entity::searchNextConsumption(Node* s) {
  if (s == nullptr) return nullptr;

  Node* des = nullptr;
  int max = 0;
  int closedCount = 0;
  
  bool localClosed = false;
  bool closed = true;

  std::cout << "Entity::searchNextConsumption: itnum=" << curr->getNeighbors().size() << std::endl;
  for (Node* next : curr->getNeighbors()) {
    // first iteration
    if (des == nullptr) {  
      std::cout << "Entity::searchNextConsumption: des==nullptr" << std::endl;
      std::cout << "next->color=" << next->color << std::endl;
      std::cout << "next->pos=(" << next->getLayer() << ", " 
      << next->getIndex() << ")" << std::endl;
      if (next->color == _WHITE ||
          next->color == _YELLOW) {  // color = WHITE | YELLOW
        des = next;
        int count_ = 1;
        localClosed = traversal(next, max, count_, closedCount);
        closed &= localClosed;
        std::cout << "Entity::searchNextConsumption: local closed?=" << localClosed << std::endl;

        if (localClosed) {  // if it is a closed path => re-initialize
          des = nullptr;
          max = 0;
          closedCount = 0;
        }
      }
    } 
    // other iterations
    else {  
      if (next->color == _WHITE ||
          next->color == _YELLOW) {  // if color = WHITE | YELLOW
        int max_ = 0;
        int count_ = 1;
        int closedCount_ = 0;
        std::cout << "Entity::searchNextConsumption: it=" << count_ << std::endl;

        localClosed = traversal(next, max_, count_, closedCount_);
        if (!localClosed) {   // if next is not a closed path
          if (closedCount_ < closedCount) {   // if next has less consumption
            des = next;
            closedCount = closedCount_;
            max = max_;
          } else if (closedCount_ == closedCount) {   // if same consumption
            if (max_ > max) { // if it travels more nodes
              des = next;
              closedCount = closedCount_;
              max = max_;
            }
          }
        }
      }
    }
  }

  return des;
}

bool Entity::local_traversal(Node* curr, bool& closed) {
  int temp_color = curr->color;
  curr->color = _BLACK;
  bool deadend = true;
  for (Node* next : curr->getNeighbors()) {
    // if a node is unvisited or not taken
    // visits the node
    if (next->color == _WHITE ||
        next->color == _YELLOW) {  // color = WHITE | YELLOW
      // check if a child path is closed or not
      bool local_closed = local_traversal(next, closed);
      // check if the current path is closed or not
      closed &= local_closed;
      // this path is not a deadend
      deadend = false;
    }
    // if there is an adjacent node colored red
    // this path is not closed yet
    if (next->color == _RED) {
      closed &= false;
    }
  }
  // if this path is closed -> consume this node
  if (closed) consumeNode(curr);
  // if not, reset the color
  else curr->color = temp_color;
  
  return closed;
}

bool Entity::consumeClosedPaths(Node* curr) {
  for (Node* neigh : curr->getNeighbors()) {
    if (neigh->color == _WHITE ||
        neigh->color == _YELLOW) {
      bool closed = true;
      local_traversal(neigh, closed);
      if (closed) {
        Edge* e = new Edge(curr->pos, neigh->pos);
        // Record the new path
        newEntityPath.push_back(e);
        // Store it in the entity path
        entityPath.push_back(e);
      }
    }
  }
  this->curr = curr;
  return true;
}

void Entity::consumeNode(Node* node) {
  /* validation layer */
  if (node == nullptr) 
    throw std::invalid_argument("Entity.hpp: null pointer node can't be consumed.");

  if (curr != nullptr) {
    bool isAdjacent = false;
    for (Node* neigh : curr->getNeighbors()) {
      if (isAdjacent = (neigh == node)) break;
    }
    
    // connect the prev node and curr node
    // only if they are adjacent.
    if (isAdjacent) { 
      Edge* e = new Edge(curr->pos, node->pos);
      // Record the new path
      newEntityPath.push_back(e);
      // Store it in the entity path
      entityPath.push_back(e);
    } else {
      Node* outer = nullptr;
      if (node->getNeighbors().size() != 0) {  // if there is any neighbor
        for (Node* neigh : node->getNeighbors()) {  // find the outer node
          if (neigh->color == _BLACK) {  // if neigh is a consumed node
            if (outer == nullptr) { // at first, outer = neigh
              outer = neigh;
            } else {  // compare outer and neigh
              // find the one on a higher layer.
              if (neigh->pos[0] > outer->pos[0])
                outer = neigh;
            }
          }
        }
        if (outer != nullptr) { // if outer is found, add an edge
          Edge* e = new Edge(node->pos, outer->pos);
          // Record the new path
          newEntityPath.push_back(e);
          // Store it in the entity path
          entityPath.push_back(e);
        }
      } 
    }
  } 
  else {  // if curr is a new starting point, 
  // find a adjacent consumed node and connect these two
    Node* outer = nullptr;
    for (Node* neigh : node->getNeighbors()) {
      if (neigh->color == _BLACK) {  // if neigh is a consumed node
        outer = neigh;
        break;
      }
    }

    if (outer != nullptr) { // if outer is found, add an edge
      Edge* e = new Edge(node->pos, outer->pos);
      // Record the new path
      newEntityPath.push_back(e);
      // Store it in the entity path
      entityPath.push_back(e);
    } else {
      std::invalid_argument(
        "Entity::consumeNode: The consumed node adjacent to the starting node is not found"
      );
    }
  }
  // Consume the node
  consumedNodes.push_back(node);
  node->color = _BLACK;
  curr = node;

  std::cout << "Entity::consumeNode: curr=("
  << curr->pos[0] << ", " << curr->pos[1] << ")"
  << std::endl;

  // Record the new node
  newConsumedNodes.push_back(node);
}
