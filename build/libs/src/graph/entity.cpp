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
  if (next == nullptr)  // if the current path is ended
    // Find a new starting node
    next = getNextStartingNode(g);
  // if all the nodes in the web is taken
  if (next == nullptr) return _FAIL;  // notify the game is over
  
  consumeNode(next);
  consumeClosedPaths(next);
  return _SUCCESS;
}

Node* Entity::getNextStartingNode(Graph &g) {
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
  // 0 -> [11  0  1]
  // 1 -> [ 1  2  3]
  // 2 -> [ 3  4  5]  = A
  // 3 -> [ 5  6  7]
  // 4 -> [ 7  8  9]
  // 5 -> [ 9 10 11]
  // ---------------------------
  //     [-11 -11 -11]
  // A + [-11 -11 -11] = A`
  //     [    ...    ]
  //     [-11 -11 -11]
  // ---------------------------
  // transpose(A`).scale(-1) = A``
  // ---------------------------
  // basis(A``.scale(1/3)) = ans_vector
  // ---------------------------
  int index = n->pos[1];
  
  int newi = ((index + (((index - 11) + 6) * (-2))) * (-1)) / 3;

  g.addNode(Content(), 4, newi);
  origin = g.searchNode(4, newi);
  g.addEdge(origin->pos, n->pos);
  consumeNode(origin);
}


bool Entity::traversal(Node *curr, int &max, int &count, int &closedCount) {
  
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
    if (next->color != _BLACK &&
        next->color != _RED) {  // color = WHITE | YELLOW
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
  curr->color = _WHITE;
  // reset the count and localPath
  count -= 1;

  return closed;
}

Node* Entity::searchNextConsumption(Node* s) {
  Node* des = nullptr;
  int max = 0;
  int closedCount = 0;
  
  bool localClosed = false;
  bool closed = true;

  for (Node* next : curr->getNeighbors()) {
    // initialization
    if (des == nullptr) {  
      if (next->color != _BLACK &&
          next->color != _RED) {  // color = WHITE | YELLOW
        des = next;
        int count_ = 1;
        localClosed = traversal(next, max, count_, closedCount);
        closed &= localClosed;
        if (localClosed) {  // if it is a closed path => re-initialize
          des = nullptr;
          max = 0;
          closedCount = 0;
        }
      }
    } 
    // after initialization
    else {  
      if (next->color != _BLACK &&
          next->color != _RED) {  // if color = WHITE | YELLOW
        int max_ = 0;
        int count_ = 1;
        int closedCount_ = 0;
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

  return closed ? nullptr : des;
}

bool Entity::local_traversal(Node* curr) {
  curr->color = _BLACK;
  bool deadend = true;
  bool closed = true;
  for (Node* next : curr->getNeighbors()) {
    // if a node is unvisited or not taken
    // visits the node
    if (next->color != _BLACK &&
        next->color != _RED) {  // color = WHITE | YELLOW
      // check if a child path is closed or not
      bool local_closed = local_traversal(next);
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
  else curr->color = _WHITE;
  
  return closed;
}

bool Entity::consumeClosedPaths(Node* curr) {
  for (Node* neigh : curr->getNeighbors()) {
    local_traversal(neigh);
  }
  return true;
}

void Entity::consumeNode(Node* node) {
  /* validation layer */
  if (node == nullptr) 
    throw std::invalid_argument("Entity.hpp: null pointer node can't be consumed.");

  if (curr != nullptr) {
    Edge* e = new Edge(curr->pos, node->pos);
    // Record the new path
    newEntityPath.push_back(e);
    // Store it in the entity path
    entityPath.push_back(e);
  } 
  else {  // if curr is a new starting point, 
  // find a adjacent consumed node and connect these two
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
        Edge* e = new Edge(curr->pos, outer->pos);
        // Record the new path
        newEntityPath.push_back(e);
        // Store it in the entity path
        entityPath.push_back(e);
      }
    } 
  }
  // Consume the node
  consumedNodes.push_back(node);
  node->color = _BLACK;
  curr = node;

  // Record the new node
  newConsumedNodes.push_back(node);
}
