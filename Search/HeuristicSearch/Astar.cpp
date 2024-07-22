#include <algorithm>
#include <cmath>
#include <iostream>
#include <queue>
#include <unordered_map>
#include <vector>

struct Point {
  Point() = default;
  Point(int x, int y) : x(x), y(y) {}
  ~Point() = default;

  bool operator<(const Point& p) const { return x < p.x && y < p.y; }
  bool operator==(const Point& p) const { return x == p.x && y == p.y; }
  bool operator>(const Point& p) const { return x > p.x && y > p.y; }

  int x;
  int y;
};

template <>
struct std::hash<Point> {
  size_t operator()(const Point& p) const {
    return std::hash<int>()(p.x) ^ std::hash<int>()(p.y);
  }
};

class Grid {

 public:
  explicit Grid(int len) : grid_(len, std::vector<int>(len, 0)) {}
  ~Grid() = default;

  void setObstacle(unsigned int x, unsigned int y, int val) {
    grid_[x][y] = val;
  }

  [[nodiscard]] bool isInsideGrid(const Point& p) const {
    return p.x >= 0 && p.x < grid_.size() && p.y >= 0 && p.y < grid_.size();
  }

  [[nodiscard]] bool isObstacle(const Point& p) const {
    return grid_[p.x][p.y] == 1;
  }

  [[nodiscard]] static double cost(const Point& a, const Point& b) {
    return std::hypot(a.x - b.x, a.y - b.y);
  }

  [[nodiscard]] auto getNeighbors(const Point& p) const -> std::vector<Point> {

    std::vector<Point> neighbors;
    neighbors.reserve(directions_.size());

    for (const auto& [dx, dy] : directions_) {
      const Point neighbor{p.x + dx, p.y + dy};

      if (isInsideGrid(neighbor) && !isObstacle(neighbor)) {
        neighbors.emplace_back(neighbor);
      }
    }

    return neighbors;
  }

  friend std::ostream& operator<<(std::ostream& os, const Grid& g) {
    for (const auto& row : g.grid_) {
      for (const auto& cell : row) {
        os << cell << " ";
      }
      os << '\n';
    }
    return os;
  }

 private:
  std::vector<std::vector<int>> grid_;
  const std::vector<std::pair<int, int>> directions_{{0, 1},
                                                     {1, 0},
                                                     {0, -1},
                                                     {-1, 0}};
};

auto heuristic(const Point& a, const Point& b) -> double {
  return std::hypot(a.x - b.x, a.y - b.y);
}

std::vector<Point> aStarSearch(const Grid& grid, const Point& start,
                               const Point& goal) {
  std::priority_queue<std::pair<double, Point>,
                      std::vector<std::pair<double, Point>>, std::greater<>>
      frontier;
  std::unordered_map<Point, Point> cameFrom;
  std::unordered_map<Point, double> costSoFar;

  frontier.emplace(0, start);
  cameFrom[start] = start;
  costSoFar[start] = 0;

  while (!frontier.empty()) {
    auto current = frontier.top().second;
    frontier.pop();

    if (current == goal) {
      break;
    }

    for (const auto& next : grid.getNeighbors(current)) {
      double newCost = costSoFar[current] + Grid::cost(current, next);
      if (!costSoFar.contains(next) || newCost < costSoFar[next]) {
        costSoFar[next] = newCost;
        const double priority = newCost + heuristic(next, goal);
        frontier.emplace(priority, next);
        cameFrom[next] = current;
      }
    }
  }

  std::vector<Point> path;
  if (cameFrom.contains(goal)) {
    for (Point p = goal; p != start; p = cameFrom[p]) {
      path.push_back(p);
    }
    path.push_back(start);
    std::ranges::reverse(path);
  }

  return path;
}

int main() {

  Grid grid{10};
  // Optionally, setup obstacles in the grid here
  grid.setObstacle(5, 5, 1);  // Example obstacle

  std::cout << grid << '\n';

  const Point start{0, 0};
  const Point goal{9, 9};
  const auto path = aStarSearch(grid, start, goal);

  for (auto& p : path) {
    std::cout << "(" << p.x << ", " << p.y << ") ";
  }
  std::cout << std::endl;

  return 0;
}