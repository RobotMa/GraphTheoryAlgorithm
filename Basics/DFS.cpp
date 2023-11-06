#include <iostream>
#include <ranges>
#include <span>
#include <utility>
#include <vector>

#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/depth_first_search.hpp>
#include <boost/graph/visitors.hpp>

/*
  This calculates the discover finishing time.

  Sample Output

  Tree edge: 0 --> 2
  Tree edge: 2 --> 1
  Back edge: 1 --> 1
  Finish edge: 1 --> 1
  Tree edge: 1 --> 3
  Back edge: 3 --> 1
  Finish edge: 3 --> 1
  Tree edge: 3 --> 4
  Back edge: 4 --> 0
  Finish edge: 4 --> 0
  Back edge: 4 --> 1
  Finish edge: 4 --> 1
  Forward or cross edge: 2 --> 3
  Finish edge: 2 --> 3
  Finish edge: 0 --> 2
  1 10
  3 8
  2 9
  4 7
  5 6

 */

template <class VisitorList>
struct edge_categorizer : public boost::dfs_visitor<VisitorList> {

  using Base = boost::dfs_visitor<VisitorList>;

  explicit edge_categorizer(const VisitorList& v = boost::null_visitor())
      : Base(v) {}

  template <class Edge, class Graph>
  void tree_edge(Edge edge, Graph& G) {
    std::cout << "Tree edge: " << source(edge, G) << " --> " << target(edge, G)
              << '\n';
    Base::tree_edge(edge, G);
  }

  template <class Edge, class Graph>
  void back_edge(Edge e, Graph& G) {
    std::cout << "Back edge: " << source(e, G) << " --> " << target(e, G)
              << '\n';
    Base::back_edge(e, G);
  }

  template <class Edge, class Graph>
  void forward_or_cross_edge(Edge e, Graph& G) {
    std::cout << "Forward or cross edge: " << source(e, G) << " --> "
              << target(e, G) << '\n';
    Base::forward_or_cross_edge(e, G);
  }

  template <class Edge, class Graph>
  void finish_edge(Edge e, Graph& G) {
    std::cout << "Finish edge: " << source(e, G) << " --> " << target(e, G)
              << '\n';
    Base::finish_edge(e, G);
  }
};

template <class VisitorList>
auto categorize_edges(const VisitorList& v) {
  return edge_categorizer<VisitorList>(v);
}

int main(int, char*[]) {

  using Graph = boost::adjacency_list<>;

  const int noVerts = 5;
  Graph graph(noVerts);
  add_edge(0, 2, graph);
  add_edge(1, 1, graph);
  add_edge(1, 3, graph);
  add_edge(2, 1, graph);
  add_edge(2, 3, graph);
  add_edge(3, 1, graph);
  add_edge(3, 4, graph);
  add_edge(4, 0, graph);
  add_edge(4, 1, graph);

  using size_type = boost::graph_traits<Graph>::vertices_size_type;

  std::vector<size_type> d(num_vertices(graph));
  std::vector<size_type> f(num_vertices(graph));
  int t = 0;
  depth_first_search(
      graph, visitor(categorize_edges(std::make_pair(
                 stamp_times(d.data(), t, boost::on_discover_vertex()),
                 stamp_times(f.data(), t, boost::on_finish_vertex())))));

  for (auto i = d.cbegin(), j = f.cbegin(); i != d.cend() and j != f.cend();
       ++i, ++j) {
    std::cout << *i << " " << *j << '\n';
  }

  return 0;
}
