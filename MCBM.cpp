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




//String mode:

int augPath(unordered_map<string,vector<string>> &AL,unordered_set<string> &visited,unordered_map<string,string> &matches, string L) {
  if (visited.count(L) == 1) return 0;
  visited.insert(L);
  for (auto R : AL[L]) {
    if (matches.count(R) == 0 || augPath(AL,visited,matches,matches[R])) {
      matches[R] = L;
      return 1;
    }
  }
  return 0;
}

int MCBM(unordered_map<string,vector<string>> &AL,vector<string> leftSet) {
  unordered_map<string,string> matches;
  unordered_set<string> visited;
  int totalMatches = 0;
  for (auto L : leftSet) {
    totalMatches += augPath(AL,visited,matches,L);
    visited.clear();
  }
  return totalMatches;
} 
