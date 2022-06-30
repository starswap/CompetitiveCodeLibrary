void preprocessBinLift(int u,vector<int> &lvl,vector<vector<int>> &dp,vector<vector<int>> &AL,vector<int> &visited, int cc) {
    visited[u] = cc; //stores which conc it is in.
    
    for (int i=1;i<LN;++i) {
        if (dp[u][i-1] != -1) //if it is -1 then you can't jump that far
            dp[u][i] = dp[dp[u][i-1]][i-1];
    }
    
    for (int v : AL[u]) {
        dp[v][0] = u; //***
        lvl[v] = lvl[u] + 1;
        preprocessBinLift(v,lvl,dp,AL,visited,cc);
    }
    
}

int binLiftLCA(int u, int v,vector<int> &lvl,vector<vector<int>> &dp,vector<vector<int>> &AL) {
    if (lvl[u] < lvl[v])
        swap(u,v);
    
    int diff = lvl[u] - lvl[v];
    for (int i=0;i<LN;++i) {
        if (diff & 1<<i) //need to jump by this one NOT i but 1<<i
            u = dp[u][i];
    }
    
    
    //now at same level
    
    if (u == v) // DONT FORGET
        return u;
    
    
    for (int i=LN-1;i>=0;--i) {
        if (dp[u][i] != dp[v][i]) { //not the same after jump, so jump both up
            u = dp[u][i];
            v = dp[v][i];
        }
    }
    return dp[u][0]; // == dp[v][0] - parent is LCA. 
    
}
