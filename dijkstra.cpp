//Nodes numbered from 0
//Adjacency list with pairs Source: (Dest,Cost)
int dijkstra(int nodeA, int nodeB, const vector<vector<pair<int,int>>>& AL,int N) {
  priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>>  pq;
  vector<int> upToDateScores(N,MAX_INT);
  upToDateScores[nodeA] = 0;
  pq.push(pair<int,int>(0,nodeA));
  while (pq.size() != 0 && get<1>(pq.top()) != nodeB) {
    pair<int,int> top = pq.top(); pq.pop();
    if (get<0>(top) != upToDateScores[get<1>(top)])
      continue;
    else {
      for (auto e : AL[get<1>(top)]) {
        if (get<0>(top)+get<1>(e) < upToDateScores[get<0>(e)])  {
          upToDateScores[get<0>(e)] = get<0>(top)+get<1>(e);
          pq.push(pair<int,int>(get<0>(top)+get<1>(e),get<0>(e)));
        }
      }
    }

  }
  if (pq.size() == 0)
    return -1;
  else 
    return get<0>(pq.top());
}
