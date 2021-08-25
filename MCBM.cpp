int AugPath(int L,vector<vector<int>>& AL,vector<int>& matches,vector<int>& visited) {
  if (visited[L]) return 0;
  visited[L] = 1;
  for (auto &R : AL[L]) {
    if (matches[R] == -1 || AugPath(matches[R],AL,matches,visited)) {
      matches[R] = L;
      return 1;      
    }
  }
  return 0;
}

int MCBM(vector<vector<int>> AL,int Vtot,int VLeft) {
  int totalMatches = 0;
  vector<int> matches(Vtot,-1);
  vector<int> visited;

  for (int L=0;L<VLeft;L++) {
    visited.assign(VLeft,0); 
    totalMatches += AugPath(L,AL,matches,visited);
  }

  return totalMatches;
}
