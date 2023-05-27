// edge.cpp
#include "edge.hpp"

bool Edge::operator==(const Edge& other) const {
  return 
    (a[0] == other.a[0] && a[1] == other.a[1] 
    && b[0] == other.b[0] && b[1] == other.b[1]) ||
    (a[0] == other.b[0] && a[1] == other.b[1] 
    && b[0] == other.a[0] && b[1] == other.a[1]);
}