vector<bool> visited;
vector<int> postOrder;
void dfs(vector<vector<int>>&AL,int u) {
  visited[u] = true;
  for (int v : AL[u]) {
    if (!visited[v]) 
      dfs(AL,v);
  }
  postOrder.push_back(u);
}

int Kosaraju(vector<vector<int>>&AL,vector<vector<int>> &AL_T) {
  int n = AL.size();
  visited.assign(n,false);
  postOrder.clear();

  for (int i=0;i<n;i++) {
    if (!visited[i]) {
      dfs(AL,i);
    }
  }
  visited.assign(n,false);
  int SCCs = 0;
  for (int i=n-1;i>=0;i--) {
    if (!visited[postOrder[i]]) {
      dfs(AL_T,postOrder[i]);
      SCCs++;
    }
  }
  return SCCs;
}
