class UFDS {
  private:
    vector<int> p;
    vector<int> rank;
    int n;

  public:
    UFDS(int a):n(a) {
      for (int i=0;i<n;i++) {
        p.push_back(i);
      }
      rank.assign(n,1);
    }

    int findSet(int a) {
      if (p[a] == a) 
        return a;
      else {
        int x = findSet(p[a]);
        p[a] = x;
        return x;
      }
    }

    void unionSet(int a,int b) {
      int x = findSet(a);
      int y = findSet(b);

      if (x==y) {return;}

      if (rank[x] > rank[y]) {
        p[y] = x;
      } else if (rank[y] > rank[x]){
        p[x] = y;
      }
      else {
        p[x] = y;
        ++rank[y];
      }
    }

    bool isSameSet(int a,int b) {
      return findSet(a) == findSet(b);
    }

};
