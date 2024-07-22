// O (V + E) time complexity
// can work for both postive and negative weights unlike Dijkstra's algorithm

#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/graph_traits.hpp>
#include <boost/graph/topological_sort.hpp>
#include <boost/property_map/property_map.hpp>
#include <iostream>
#include <limits>
#include <ranges>
#include <vector>

using Graph = boost::adjacency_list<boost::vecS, boost::vecS, boost::directedS,
                                    boost::no_property,
                                    boost::property<boost::edge_weight_t, int>>;
using Vertex = boost::graph_traits<Graph>::vertex_descriptor;

void single_source_shortest_path(const Graph& g, Vertex source,
                                 std::vector<int>& distances) {
  const auto num_vertices = boost::num_vertices(g);

  // good use fo assign function
  distances.assign(num_vertices, std::numeric_limits<int>::max());
  distances[source] = 0;

  std::vector<Vertex> topoVertices;
  topoVertices.reserve(num_vertices);

  // Topologically sort the vertices
  boost::topological_sort(g, std::back_inserter(topoVertices));

  // Relax the edges in topological order
  for (Vertex u : topoVertices | std::views::reverse) {

    if (distances[u] != std::numeric_limits<int>::max()) {

      for (auto [ei, ei_end] = boost::out_edges(u, g); ei != ei_end; ++ei) {

        const Vertex v = boost::target(*ei, g);
        const int weight = boost::get(boost::edge_weight, g, *ei);

        if (distances[u] + weight < distances[v]) {
          distances[v] = distances[u] + weight;
        }
      }
    }
  }
}

int main() {
  // Create the graph
  Graph g;

  // Add edges to the graph (source, target, weight)
  boost::add_edge(0, 1, 5, g);
  boost::add_edge(0, 2, 3, g);
  boost::add_edge(1, 3, 6, g);
  boost::add_edge(1, 2, 2, g);
  boost::add_edge(2, 4, 4, g);
  boost::add_edge(2, 5, 2, g);
  boost::add_edge(2, 3, 7, g);
  boost::add_edge(3, 4, -1, g);
  boost::add_edge(4, 5, -2, g);

  // Define the source vertex
  Vertex source = 0;

  // Vector to store the distances
  std::vector<int> distances;

  // Find the shortest paths
  single_source_shortest_path(g, source, distances);

  // Output the distances
  std::cout << "Shortest paths from source vertex " << source << " are:\n";
  for (size_t i = 0; i < distances.size(); ++i) {
    std::cout << "Vertex " << i << ": " << distances[i] << '\n';
  }

  return 0;
}