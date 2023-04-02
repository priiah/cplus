#include "proj6.hpp"
#include "CSVReader.hpp"
#include "InterferenceGraph.hpp"
#include <vector>

using namespace proj6;

// assignRegisters
//
// This is where you implement the register allocation algorithm
// as mentioned in the README. Remember, you must allocate at MOST
// d(G) + 1 registers where d(G) is the maximum degree of the graph G.
// If num_registers is not enough registers to accomodate the passed in
// graph you should return an empty map. You MUST use registers in the
// range [1, num_registers] inclusive.
RegisterAssignment proj6::assignRegisters(const std::string &path_to_graph,
                                          int num_registers) noexcept {
  InterferenceGraph<Variable> ig = CSVReader::load(path_to_graph);

  // TODO: You implement this!
  std::vector<int> colors = {};

  for (int i = 1; i <= num_registers; i++){
    colors.push_back(i);
  }
  RegisterAssignment r = {};

  for (std::string vertex:ig.vertices()){
    int i = 0;
    for(std::string neighbor: ig.neighbors(vertex)){
      if (r.find(neighbor) != r.end()){
        if (r[neighbor] == colors[i]){
          i++;
          if (i >= num_registers){
            return {};
          }
        }
      }
    }
    r[vertex] = colors[i];
  }

  return r;
}