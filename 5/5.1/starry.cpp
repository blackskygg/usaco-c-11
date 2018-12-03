/*
  ID: blacksk2
  TASK: starry
  LANG: C++11
*/

#include <algorithm>
#include <fstream>
#include <string>
#include <unordered_map>
#include <vector>

class DJSet {
public:
  DJSet(int n) : p(n, -1) {
    for (int i = 0; i < p.size(); ++i) {
      p[i] = i;
    }
  };

  int Find(int x) {
    int px = x;
    while (p[px] != px) {
      px = p[px];
    }

    int curr = x;
    while (curr != px) {
      int t = p[curr];
      p[curr] = px;
      curr = t;
    }
    return px;
  }

  int Union(int x, int y) { return p[Find(x)] = Find(y); }

private:
  std::vector<int> p;
};

struct Cluster {
  int m;
  int n;
  std::vector<std::pair<int, int>> points;

  void Normalize() {
    if (points.empty()) {
      return;
    }
    int lx = points[0].first, ly = points[0].second;
    m = lx + 1;
    n = ly + 1;
    for (const auto &p : points) {
      m = std::max(m, p.first + 1);
      n = std::max(n, p.second + 1);
      lx = std::min(lx, p.first);
      ly = std::min(ly, p.second);
    }
    m -= lx;
    n -= ly;
    for (auto &p : points) {
      p.first -= lx;
      p.second -= ly;
    }
    std::sort(points.begin(), points.end());
  }

  void TurnRight() {
    for (auto &p : points) {
      int x = p.first, y = p.second;
      p.first = y;
      p.second = m - x - 1;
    }
    std::sort(points.begin(), points.end());
    std::swap(m, n);
  }

  void Flip() {
    for (auto &p : points) {
      p.first = m - p.first - 1;
    }
    std::sort(points.begin(), points.end());
  }

  bool operator==(const Cluster &rhs) {
    return m == rhs.m && n == rhs.n && points == rhs.points;
  }
};

static std::vector<std::string> stars;
static int m, n;

DJSet mark_points() {
  const std::vector<std::vector<int>> dirs = {
      {0, 1}, {0, -1}, {1, 0}, {-1, 0}, {1, -1}, {-1, -1}, {-1, 1}, {1, 1}};
  auto is_valid = [&](int x, int y) {
    return x >= 0 && x < m && y >= 0 && y < n && stars[x][y] == '1';
  };

  DJSet clusters(m * n);
  for (int x = 0; x < m; ++x) {
    for (int y = 0; y < n; ++y) {
      if (stars[x][y] == '0') {
        continue;
      }
      const int curr_id = x * n + y;
      for (const auto &dir : dirs) {
        int tx = x + dir[0], ty = y + dir[1];
        if (!is_valid(tx, ty)) {
          continue;
        }
        clusters.Union(curr_id, tx * n + ty);
      }
    }
  }

  return clusters;
}

void normalize(std::vector<int> &points, int n) {
  int lx = points[0] / n, ly = points[1] % n;
  for (int p : points) {
    int x = p / n, y = p % n;
    lx = std::min(lx, x);
    ly = std::min(ly, y);
  }
  for (int &p : points) {
    p = (p / n - lx) * n + p % n - ly;
  }
}

std::unordered_map<int, Cluster> cluster_points(DJSet &points_mark) {
  std::unordered_map<int, Cluster> clusters;
  std::unordered_map<int, int> cluster_ids;

  for (int x = 0; x < m; ++x) {
    for (int y = 0; y < n; ++y) {
      if (stars[x][y] == '0') {
        continue;
      }
      int id = points_mark.Find(x * n + y);
      if (clusters.count(id) == 0) {
        clusters[id] = Cluster();
      }
      clusters[id].points.emplace_back(x, y);
    }
  }

  for (auto &kv : clusters) {
    kv.second.Normalize();
  }

  return clusters;
}

bool compare(Cluster &ca, Cluster &cb) {
  for (int f = 0; f < 2; ++f) {
    for (int d = 0; d < 4; ++d) {
      if (ca == cb) {
        return true;
      }
      cb.TurnRight();
    }
    cb.Flip();
  }
  return false;
}

DJSet mark_clusters(std::unordered_map<int, Cluster> &clusters) {
  std::vector<int> ids;
  for (const auto &kv : clusters) {
    ids.push_back(kv.first);
  }

  DJSet id_cluster(m * n);
  for (int i = 0; i < ids.size(); ++i) {
    for (int j = i + 1; j < ids.size(); ++j) {
      if (compare(clusters[ids[i]], clusters[ids[j]])) {
        id_cluster.Union(ids[i], ids[j]);
      }
    }
  }
  return id_cluster;
}

void get_stars(std::ifstream &fin) {
  fin >> n >> m;
  stars.resize(m);
  for (auto &l : stars) {
    fin >> l;
  }
}

void recolor_stars(DJSet &points_mark, DJSet &clusters_mark) {
  std::unordered_map<int, char> id2char;
  char curr_char = 'a';
  for (int x = 0; x < m; ++x) {
    for (int y = 0; y < n; ++y) {
      if (stars[x][y] == '0') {
        continue;
      }
      int id = clusters_mark.Find(points_mark.Find(x * n + y));
      if (id2char.count(id) == 0) {
        id2char[id] = curr_char++;
      }
      stars[x][y] = id2char[id];
    }
  }
}

void print_stars(std::ofstream &fout) {
  for (const auto &l : stars) {
    fout << l << std::endl;
  }
}

int main() {
  std::ifstream fin("starry.in");
  std::ofstream fout("starry.out");

  get_stars(fin);
  DJSet points_mark = mark_points();
  std::unordered_map<int, Cluster> clusters = cluster_points(points_mark);
  DJSet clusters_mark = mark_clusters(clusters);
  recolor_stars(points_mark, clusters_mark);
  print_stars(fout);

  return 0;
}