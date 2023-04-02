#ifndef __INTERFERENCE_GRAPH__HPP
#define __INTERFERENCE_GRAPH__HPP

#include <exception>
#include <string>
#include <unordered_set>
#include <unordered_map>


class UnknownVertexException : public std::runtime_error {
public:
  UnknownVertexException(const std::string &v)
      : std::runtime_error("Unknown vertex " + v) {}
};

class UnknownEdgeException : public std::runtime_error {
public:
  UnknownEdgeException(const std::string &v, const std::string &w)
      : std::runtime_error("Unknown edge " + v + " - " + w) {}
};

// InterferenceGraph
//
// This is a class representing an interference graph
// as described in "Part 1: Interference Graph" of the README.md
// file.
template <typename T> class InterferenceGraph {
public:
  // Custom type used to represent edges. This is mainly
  // used in the utility function for reading and writing
  // the graph structure to/from files. You don't need to use it.
  using EdgeTy = std::pair<T, T>;

  InterferenceGraph();

  ~InterferenceGraph();

  void addEdge(const T &v, const T &w);

  void addVertex(const T &vertex) noexcept;

  void removeEdge(const T &v, const T &w);

  void removeVertex(const T &vertex);

  std::unordered_set<T> vertices() const noexcept;

  std::unordered_set<T> neighbors(const T &vertex) const;

  unsigned numVertices() const noexcept;

  unsigned numEdges() const noexcept;

  bool interferes(const T &v, const T &w) const;

  unsigned degree(const T &v) const;

private:
  int vertexes;
  int edges;
  std::unordered_set<T> vertexSet;
  std::unordered_map<T, std::unordered_set<T>> neighborMap;
};

template <typename T> InterferenceGraph<T>::InterferenceGraph() {
  vertexes = 0;
  edges = 0;
  vertexSet = {};
  neighborMap = {};
}

template <typename T> InterferenceGraph<T>::~InterferenceGraph() {}

template <typename T>
std::unordered_set<T> InterferenceGraph<T>::neighbors(const T &vertex) const {
  if (vertexSet.find(vertex) != vertexSet.end()){
    return neighborMap.at(vertex);
  }
  else{
    throw UnknownVertexException(vertex);
  }
}

template <typename T>
std::unordered_set<T> InterferenceGraph<T>::vertices() const noexcept {
  return vertexSet;
}

template <typename T>
unsigned InterferenceGraph<T>::numVertices() const noexcept {
  return vertexes;
}

template <typename T> unsigned InterferenceGraph<T>::numEdges() const noexcept {
  return edges;
}

template <typename T>
void InterferenceGraph<T>::addEdge(const T &v, const T &w) {
  if (vertexSet.find(v) == vertexSet.end())
  {
    throw UnknownVertexException(v);
  }
  if (vertexSet.find(w) == vertexSet.end())
  {
    throw UnknownVertexException(w);
  }
  neighborMap.at(v).insert(w);
  neighborMap.at(w).insert(v);
  edges++;
}

template <typename T>
void InterferenceGraph<T>::removeEdge(const T &v, const T &w) {
  if (vertexSet.find(v) == vertexSet.end())
  {
    throw UnknownVertexException(v);
  }
  if (vertexSet.find(w) == vertexSet.end())
  {
    throw UnknownVertexException(w);
  }
  if(neighborMap.at(v).find(w) == neighborMap.at(v).end()){
    throw UnknownEdgeException(v,w);
  }
  neighborMap.at(v).erase(w);
  neighborMap.at(w).erase(v);
  edges--;
}

template <typename T>
void InterferenceGraph<T>::addVertex(const T &vertex) noexcept {
  if (vertexSet.find(vertex) != vertexSet.end()){
    return;
  }
  vertexSet.insert(vertex);
  neighborMap[vertex] = {};
  vertexes++;
}

template <typename T>
void InterferenceGraph<T>::removeVertex(const T &vertex) {
  if (vertexSet.find(vertex) != vertexSet.end()){
    for (T w: neighborMap[vertex]){
      removeEdge(vertex,w);
    }
    neighborMap.erase(vertex);
    vertexSet.erase(vertex);
    vertexes--;
  }
  else{
    throw UnknownVertexException(vertex);
  }
}

template <typename T>
bool InterferenceGraph<T>::interferes(const T &v, const T &w) const { 
  if (vertexSet.find(v) == vertexSet.end())
  {
    throw UnknownVertexException(v);
  }
  if (vertexSet.find(w) == vertexSet.end())
  {
    throw UnknownVertexException(w);
  }

  if (neighborMap.at(v).find(w) != neighborMap.at(v).end()){
    return true;
  }
  
  return false; }

template <typename T>
unsigned InterferenceGraph<T>::degree(const T &v) const { 
  if (vertexSet.find(v) == vertexSet.end())
  {
    throw UnknownVertexException(v);
  }
  return neighborMap.at(v).size();
 }

#endif
