#include <bits/stdc++.h>
using namespace std;

vector<int> dfsParent;
vector<int> dfsDepth; 
int dfs(vector<vector<int>> &AL,int u,int d) {
  dfsDepth[u] = d;
  int maxD = d;
  for (int v : AL[u]) {
    if (dfsParent[u] != v) {
      dfsParent[v] = u;
      maxD = max(maxD,dfs(AL,v,d+1));
    }
  }
  return maxD;
}

vector<vector<int>> genLiftTable(int N) {
  vector<vector<int>> lift(N,vector<int>(ceil(log2(N)),-1));
  for (int n=0;n<N;n++)
    lift[n][0] = dfsParent[n];
  
  for (int e=1;e<log2(N);e++) {
    for (int n=0;n<N;n++) {  
      if (lift[n][e-1] != -1)
        lift[n][e] = lift[lift[n][e-1]][e-1];
    }
  }
  return lift;
}

int liftByN(vector<vector<int>> &LiftTable,int u,int n) {
  int a = 0;
  while (n != 0) {
    if (n % 2 == 1)
      u = LiftTable[u][a];
    n /= 2;
    a += 1;
  } 
  return u;
}

int binaryLiftingLCA(vector<vector<int>> &LiftTable, int u, int v) {
  if (dfsDepth[u] > dfsDepth[v]) {
    u = liftByN(LiftTable,u,dfsDepth[u]-dfsDepth[v]);
  } else {
    v = liftByN(LiftTable,v,dfsDepth[v]-dfsDepth[u]);
  }
  if (u == v)
    return v;
  else if (dfsParent[u] == dfsParent[v])
    return dfsParent[u];
  else {
    int a = 1;
    while (LiftTable[u][a] != LiftTable[v][a])
      a += 1;
    a -= 1;
    return binaryLiftingLCA(LiftTable,LiftTable[u][a],LiftTable[v][a]);
  }
}

int main() {
  int N;
  vector<vector<int>> AL(N);
  for (int n=0;n<N-1;n++) {
    int a,b; cin >> a; cin >> b; --a; --b;
    AL[a].push_back(b);
    AL[b].push_back(a);
  }
  dfsParent.assign(N,-1);
  dfsDepth.assign(N,-1);
  dfs(AL,0,0);
  vector<vector<int>> lift = genLiftTable(N);
  
  cout << binaryLiftingLCA(lift,4,7) << endl;
}
