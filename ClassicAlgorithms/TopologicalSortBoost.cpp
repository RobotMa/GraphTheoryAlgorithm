// DAG - directed acyclic graph (DAG)
// cycled graph can't have a topological order

#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/graphviz.hpp>
#include <boost/graph/topological_sort.hpp>
#include <iostream>
#include <ranges>
#include <vector>

using Graph = boost::adjacency_list<boost::vecS, boost::vecS, boost::directedS>;
using Vertex = boost::graph_traits<Graph>::vertex_descriptor;

void visualizeGraph(const Graph& g) {

  // Output the graph to a DOT file
  const std::string dot_filename{"graph.dot"};
  std::ofstream dot_file(dot_filename);

  boost::dynamic_properties dp;
  dp.property("node_id", boost::get(boost::vertex_index, g));
  boost::write_graphviz_dp(dot_file, g, dp);
  std::cout << "Graph exported to graph.dot" << '\n';

  // Call Graphviz dot command to generate an image file
  const std::string output_image{"graph.png"};
  std::string command = "dot -Tpng ";
  command += dot_filename;
  command += " -o ";
  command += output_image;

  if (std::system(command.c_str()) != 0) {
    std::cerr << "Error: Could not generate graph image using Graphviz."
              << '\n';
  }

  // Open the image with the default image viewer
  std::string open_command{"xdg-open "};

  open_command += output_image;
  if (std::system(open_command.c_str()) != 0) {
    std::cerr << "Error: Could not open the image with the default viewer."
              << '\n';
  }
}

int main() {
  // Create a graph with 6 vertices
  Graph g(6);

  // Add edges (for example: 5 -> 2, 5 -> 0, 4 -> 0, 4 -> 1, 2 -> 3, 3 -> 1)
  add_edge(5, 2, g);
  add_edge(5, 0, g);
  add_edge(4, 0, g);
  add_edge(4, 1, g);
  add_edge(2, 3, g);
  add_edge(3, 1, g);

  visualizeGraph(g);

  // Vector to store the sorted vertices
  std::vector<Vertex> topoOrder;

  // Perform topological sort
  topological_sort(g, std::back_inserter(topoOrder));

  // Print the topological order
  std::cout << "Topological order:" << '\n';
  for (auto e : std::ranges::reverse_view(topoOrder)) {
    std::cout << e << " ";
  }
  std::cout << '\n';

  return 0;
}