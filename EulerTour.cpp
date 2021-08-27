//Check problem description for corner cases:
  //No edges (highly up to problem description - is 0 edges all edges?)
  //Isolated vertices with no connected edges (typically these graphs can still have an Euler tour)

void DFS(vector<vector<int>> &AL,vector<bool>&visited,int v) {
  if (visited[v])
    return;
  else {
    visited[v] = true;
    for (int u : AL[v])
      DFS(AL,visited,u);
  }
}

bool eulerCheck(vector<vector<int>> &AL) {
  //check if an euler tour is possible on undirected graph
  
  //check for even degree
  for (vector<int> v : AL) {
    if (div(v.size(),2).rem == 1)
      return false;
  }

  //check for connected, starting from a vertex with at least one edge.
  vector<bool> visited(AL.size(),false);
  int start;
  for (start=0;AL[start].size()==0;start++) {};
  DFS(AL,visited,start);
  for (int i=0;i<visited.size();i++) {
    if (visited[i] == false && AL[i].size() != 0) //we were unable to reach the vertex and it has an edge attached to it. Therefore the graph is disconnected. If it has no edge attached, while the graph is still not connected to it, this doesn't affect the Euler tour property.
     return false;
  }
  return true;
}
