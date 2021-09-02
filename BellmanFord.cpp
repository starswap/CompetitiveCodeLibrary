vector<int> dist(N,1e9);
    dist[0] = 0;
    for (int n=0;n<N-1;n++)  {
      bool changed = false;
      for (int u=0;u<N;u++) {
        if (dist[u] != 1e9) {
          for (auto &[v,w] : AL[u]) {
            if (dist[v]>dist[u]+w) {
              dist[v] = dist[u]+w;
              changed = true;
            }
          }
        }
      }
      if (changed == false)
        break; 
    }
    bool hasNegCycle = false;
    for (int u=0;u<N;u++) {
      if (dist[u] != 1e9) {
        for (auto &[v,w] : AL[u]) {
          if (dist[v]>dist[u]+w) {
            hasNegCycle = true;
            break;
          }
        }
      }
      if (hasNegCycle) {
        break;
      }
    }
