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




//Another one:
vector<vector<int>> AL; //Adjacency list for tree

int logn; //log(N)= log(n)/log(2);
int dp[800001][23]; //dp[u][2^n] 20 is minimum; give a bit of extra space; for binary lifting
int level[800001]; //number of nodes on shortest path from node n to the root i.e. depth. 

void prepBinLift(int u, int l) {
  //O(NlogN);
  
  level[u] = l; // save level
  
  int i = 0;
  while (dp[u][i] != -1) {
    dp[u][i+1] = dp[dp[u][i]][i];
    i++;
  }
  
  for (int v : AL[u]) {
    if (v != dp[u][0]) { // not parent
      dp[v][0] = u; 
      prepBinLift(v,l+1); 
    }
  }
  
}

int binLiftLCA(int u, int v) {
  //O(logN)
  
  if (level[u] < level[v])
    swap(u,v);
  
  int diff = level[u]-level[v];
  
  //Make same level
  while (diff > 0) {
    int twoPowV = LSOne(diff);
    u = dp[u][__builtin_ctz(twoPowV)];
    diff ^= twoPowV;
  }

  if (u == v) //one was child of other.
    return u;
  
  for (int i=logn;i>=0;i--) {
    if (dp[u][i] != dp[v][i]) {
      u = dp[u][i];
      v = dp[v][i];
    }
  }
  
  //u's Parent = v's parent = LCA.
  return dp[u][0];
}



