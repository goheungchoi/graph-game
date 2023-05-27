// edge.hpp
#ifndef _EDGE_HPP_
#define _EDGE_HPP_

#include <vector>
#include <stdexcept>

/**
 * @brief Edge class represents the edge between two nodes
 * on a graph.
 * 
 */
class Edge {
public:
  std::vector<int> a; //!< Position of node
  std::vector<int> b; //!< Position of the other node
/**
 * @brief Default Constructor. Initialized positions to be 
 * [-1, -1].
 * 
 */
  Edge() : a(std::vector(2, -1)), b(std::vector(2, -1)) {};
/**
 * @brief Construct a new Edge object
 * 
 * @param a Position of the 'a' node
 * @param b Position of the 'b' node
 */
  Edge(std::vector<int> a, std::vector<int> b) : a(a), b(b) {}
/**
 * @brief Comparison operator
 * 
 * @param other Edge to be compared
 * @return true - Two Edge objects are the same
 * @return false - Two Edge objects are different
 */
  bool operator==(const Edge& other) const;
};

#endif
