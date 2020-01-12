/*
 * @Date: 2020-01-02 14:22:34
 * @Author: creedowl
 * @Description: transportation planning
 */
#include <fstream>
#include <iostream>
#include <map>
#include <queue>
#include <sstream>
#include <stack>
#include <vector>

using namespace std;

class Station {
public:
  int id;
  string name;
  // neighbor id, line id
  vector<pair<int, int>> route;

  Station(int id, string name) : id(id), name(name) {}
};

vector<string> lines;
vector<Station *> stations;
vector<vector<bool>> table(5200, vector<bool>(5200, false));
map<string, int> stationName;
int shortest{0};

void init(string file_name) {
  fstream f(file_name, ios::in);
  if (!f) {
    cout << "can't open file " << file_name << endl;
    exit(1);
  }
  string data, lineName, stationN;
  istringstream is;
  int no{0}, curLineId{-1}, curStationId{0}, preStationId{-1};
  Station *s{nullptr};
  while (!f.eof()) {
    getline(f, data);
    is = istringstream(data);
    is >> lineName;
    lines.push_back(lineName);
    curLineId++;
    preStationId = -1;
    while (!is.eof()) {
      is >> stationN;
      if (stationName.count(stationN) == 0) {
        stationName[stationN] = no++;
        curStationId = no - 1;
        s = new Station{curStationId, stationN};
        stations.push_back(s);
        // cout << curStationId << " " << stationN << endl;
      } else {
        curStationId = stationName[stationN];
        s = stations[curStationId];
      }
      if (preStationId != -1) {
        stations[preStationId]->route.push_back(
            make_pair(curStationId, curLineId));
        s->route.push_back(make_pair(preStationId, curLineId));
        table[curStationId][preStationId] = true;
        table[preStationId][curStationId] = true;
      }
      preStationId = curStationId;
      is >> ws;
      if (is.eof()) break;
    }
    f >> ws;
    if (f.eof()) break;
  }
  f.close();
}

void destroy() {
  for (auto &i : stations) delete i;
}

void showRoute(vector<int> &route) {
  int curLine{-1};
  for (size_t i = 0; i < route.size() - 1; i++) {
    if (i == 0) cout << "从 " << stations[route[i]]->name << " 出发, ";
    for (auto &s : stations[route[i]]->route) {
      if (s.first == route[i + 1] and curLine != s.second) {
        cout << "在 " << stations[route[i]]->name << " 换乘 " << lines[s.second]
             << " ,";
        curLine = s.second;
        break;
      }
    }
  }
  shortest = route.size();
  cout << "最后到达目标站点 " << stations[route[route.size() - 1]]->name
       << ", 共 " << route.size() - 1 << " 站" << endl;
}

void bfs(int from, int to) {
  vector<bool> visited(stations.size(), false);
  vector<int> route;
  queue<pair<int, vector<int>>> q;
  int cur{-1};
  q.push({from, {}});
  while (!q.empty()) {
    cur = q.front().first;
    route = q.front().second;
    q.pop();
    route.push_back(cur);
    if (visited[cur]) continue;
    visited[cur] = true;
    if (stations[cur]->id == to) {
      // vector<int> route, path;
      // vector<pair<vector<int>, int>> ans;
      // dfs2(route, 0, 0, );
      showRoute(route);
      return;
    }
    for (size_t i = 0; i < table[cur].size(); i++) {
      if (table[cur][i] and !visited[i]) {
        q.push({i, route});
      }
    }
  }
}

int total{0}, depth{0};

void dfs(vector<bool> &visited, vector<int> &route, vector<vector<int>> &result,
         int from, int to) {
  if (from == to) {
    route.push_back(to);
    result.push_back(route);
    route.pop_back();
    total++;
    return;
  }
  if (total > 10 or route.size() > shortest) return;
  route.push_back(from);
  for (size_t i = 0; i < table[from].size(); i++) {
    if (table[from][i] and !visited[i]) {
      visited[i] = true;
      depth++;
      dfs(visited, route, result, i, to);
      visited[i] = false;
      depth--;
    }
  }
  route.pop_back();
}

void dfs2(vector<int> &route, int cur, int index, vector<int> &path,
          vector<pair<vector<int>, int>> &ans) {
  if (cur >= route.size() - 1) {
    ans.push_back({path, index});
    return;
  }
  for (auto &i : stations[route[cur]]->route) {
    if (i.first == route[cur + 1]) {
      path.push_back(i.second);
      dfs2(route, cur + 1, index, path, ans);
      path.pop_back();
    }
  }
}

void leastTransferRoute(string from, string to) {
  if (stationName.count(from) == 0) {
    cout << "no station " << from << " found";
    return;
  }
  if (stationName.count(to) == 0) {
    cout << "no station " << to << " found";
    return;
  }
  vector<bool> visited(stations.size());
  vector<int> route, path;
  vector<vector<int>> result;
  vector<pair<vector<int>, int>> ans;
  dfs(visited, route, result, stationName[from], stationName[to]);
  // for (auto &i : result) dfs2(i, 0, path, ans);
  for (size_t i = 0; i < result.size(); i++) {
    if (result[i].size() > shortest + 40) continue;
    dfs2(result[i], 0, i, path, ans);
  }

  int mini{0x3ffff}, index{0};
  for (size_t i = 0; i < ans.size() - 1; i++) {
    int count{0};
    for (size_t j = 0; j < ans[i].first.size() - 1; j++) {
      if (ans[i].first[j] != ans[i].first[j + 1]) count++;
    }
    if (count < mini) {
      mini = count;
      index = i;
    }
  }
  int curLine{-1};
  for (size_t i = 0; i < ans[index].first.size(); i++) {
    if (i == 0)
      cout << "从 " << stations[result[ans[index].second][i]]->name
           << " 出发, ";
    if (curLine != ans[index].first[i]) {
      curLine = ans[index].first[i];
      cout << "在 " << stations[result[ans[index].second][i]]->name << " 换乘 "
           << lines[ans[index].first[i]] << " ,";
    }
  }
  cout << "最后到达目标站点 " << to << ", 共 "
       << result[ans[index].second].size() - 1 << " 站, 共换乘 " << mini
       << " 次" << endl;
}

void shortestRoute(string from, string to) {
  if (stationName.count(from) == 0) {
    cout << "no station " << from << " found";
    return;
  }
  if (stationName.count(to) == 0) {
    cout << "no station " << to << " found";
    return;
  }
  bfs(stationName[from], stationName[to]);
}

int main() {
  init("data.txt");
  shortestRoute("南堡公园站", "燕江路站");
  leastTransferRoute("南堡公园站", "燕江路站");
  destroy();
}
