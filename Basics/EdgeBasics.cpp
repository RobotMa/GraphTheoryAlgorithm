#include <algorithm>
#include <boost/graph/adjacency_list.hpp>
#include <iostream>

/*
  Edge Basics

  This example demonstrates the GGCL Edge interface

  There is not much to the Edge interface. Basically just two
  functions to access the source and target vertex:

  source(e)
  target(e)

  and one associated type for the vertex type:

  edge_traits<Edge>::vertex_type

  Sample output:

  (0,1) (0,2) (0,3) (0,4) (2,0) (2,4) (3,0) (3,1)

 */

template <class AdjacencyList>
struct exercise_edge {
  using Edge = typename boost::graph_traits<AdjacencyList>::edge_descriptor;
  using Vertex = typename boost::graph_traits<AdjacencyList>::vertex_descriptor;

  explicit exercise_edge(const AdjacencyList& g) : G(g) {}

  void operator()(Edge e) const {
    // begin
    // Get the associated vertex type out of the edge using the
    // edge_traits class
    // Use the source() and target() functions to access the vertices
    // that belong to Edge e
    const Vertex& src = source(e, G);
    const Vertex& targ = target(e, G);

    // print out the vertex id's just because
    std::cout << '(' << src << ',' << targ << ") ";
    // end
  }

  const AdjacencyList& G;
};

int main() {

  using Graph = boost::adjacency_list<>;

  const std::vector<std::pair<int, int>> edgeArray = {
      {0, 1}, {0, 2}, {0, 3}, {0, 4}, {2, 0}, {2, 4}, {3, 0}, {3, 1}};

  const Graph graph(edgeArray.cbegin(), edgeArray.cend(), 5);

  std::for_each(edges(graph).first, edges(graph).second,
                exercise_edge<Graph>(graph));

  return 0;
}