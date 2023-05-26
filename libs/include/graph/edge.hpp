#ifndef _EDGE_HPP_
#define _EDGE_HPP_

#include <vector>
#include <stdexcept>

class Edge {
public:
  std::vector<int> a;   // init: {-1. -1}
  std::vector<int> b;

  Edge() : a(std::vector{2, -1}), b(std::vector{2, -1}) {};
  Edge(std::vector<int> a, std::vector<int> b) : a(a), b(b) {}

  bool operator==(const Edge& other) const {
    return a[0] == other.a[0] && a[1] == other.a[1] 
      && b[0] == other.b[0] && b[1] == other.b[1];
  }
};

#endif
