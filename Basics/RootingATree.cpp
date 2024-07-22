#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/depth_first_search.hpp>
#include <boost/graph/visitors.hpp>
#include <iostream>
#include <vector>

using Graph =
    boost::adjacency_list<boost::vecS, boost::vecS, boost::undirectedS>;
using Vertex = boost::graph_traits<Graph>::vertex_descriptor;

// Visitor to set parent-child relationships during DFS
class dfs_root_visitor : public boost::default_dfs_visitor {
 public:
  explicit dfs_root_visitor(std::vector<Vertex>& parentMap)
      : parentMap_(parentMap) {}

  template <typename Edge, typename Graph>
  void tree_edge(Edge e, const Graph& g) const {
    Vertex u = source(e, g);
    Vertex v = target(e, g);
    parentMap_[v] = u;  // Set parent of v to be u
  }

 private:
  std::vector<Vertex>& parentMap_;
};

int main() {
  // Create a graph with 6 vertices
  Graph g(6);

  // Add edges to form a tree (e.g., 0-1, 0-2, 1-3, 1-4, 2-5)
  add_edge(0, 1, g);
  add_edge(0, 2, g);
  add_edge(1, 3, g);
  add_edge(1, 4, g);
  add_edge(2, 5, g);

  // Designate vertex 0 as the root
  Vertex root = 0;

  // Vector to store parent of each vertex, initialize with itself
  std::vector<Vertex> parent_map(num_vertices(g));
  for (size_t i = 0; i < num_vertices(g); ++i) {
    parent_map[i] = i;
  }

  // Perform DFS to establish parent-child relationships
  dfs_root_visitor vis(parent_map);
  depth_first_search(g, visitor(vis).root_vertex(root));

  // Output the parent-child relationships
  std::cout << "Parent-Child Relationships:" << std::endl;
  for (size_t i = 0; i < parent_map.size(); ++i) {
    if (i != root) {
      std::cout << "Parent of " << i << " is " << parent_map[i] << std::endl;
    } else {
      std::cout << i << " is the root" << std::endl;
    }
  }

  return 0;
}
