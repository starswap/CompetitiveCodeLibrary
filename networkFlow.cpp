pair<int,vector<int>> augPath(const vector<vector<int>> AL,const int source, const int sink,const int N,const vector<vector<int>> AM) { //BFS
  queue<tuple<int,int,vector<int>>> q;//vertex, minVal, route.
  q.push(tuple<int,int,vector<int>>(source,INT_MAX/2,vector<int>(1,source)));
  vector<bool> visited(N,false);
  visited[source] = true;
  while (q.size() != 0) {
    tuple<int,int,vector<int>> top = q.front(); q.pop();
    if (get<0>(top) == sink) {
      return pair<int,vector<int>>(get<1>(top),get<2>(top));
    }
    for (auto nextVertex : AL[get<0>(top)]) {
      int cost = AM[get<0>(top)][nextVertex];
      if (cost > 0 && !(visited[nextVertex])) {
        int minCost = min(get<1>(top),cost);
        get<2>(top).push_back(nextVertex);
        q.push(tuple<int,int,vector<int>>(nextVertex,minCost,get<2>(top)));
        get<2>(top).pop_back(); //MUTABLE STATE :((()))
        visited[nextVertex] = true; 
      }
    }
  }
  return pair<int,vector<int>>(-1,vector<int>(0)); 
}

int edmondsKarp(vector<vector<int>> res,int N,vector<vector<int>> AM) {
  int mf = 0;
  while (true) {
    auto [cost, path] = augPath(res,N,N+1,N,AM);
    if (cost == -1)
      break;
    for (int i=0;i<path.size()-1;++i) { 
      AM[path[i]][path[i+1]] -= cost;
      AM[path[i+1]][path[i]] += cost;
    }
    mf += cost;
  } 
  return mf;
}
