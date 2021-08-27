template<typename T> //Supports varying size numeric types e.g. int / long / long long as necessary
class FenwickTree {
  public:
   FenwickTree(T m) {
     ft.assign(m+1,0);
   }
   FenwickTree(vector<T> freqs) {
     build2(freqs);
   }
   void update(T i,T D) {
     for (; i < ft.size();i += LSOne(i)) {
       ft[i] += D;
     }
   }
   T prefixSum(T j) {
    T acc = 0;
    for (;j != 0;j -= LSOne(j)) { 
      acc += ft[j];
    }
    return acc;
   }
    void build1(vector<T> freqs) {
      ft.assign(freqs.size()+1,0);
      for (T i=0;i<freqs.size();i++) { 
        update(i+1,freqs[i]);
      }
    }
    void build2(vector<T> freqs) {
      ft.assign(freqs.size()+1,0);
      for (T i=0;i<freqs.size();i++) { 
        ft[i+1] += freqs[i]; 
        ft[(i+1)+LSOne(i+1)] += ft[i+1]; 
      }
    }  
  

  private:
    inline T LSOne (T i) {return i&(-i);}
    vector<T> ft;
};


//Supporting point update, point query, range query but not range update.
class FenwickTree {
  private:
    inline int LSOne(int S) {return S&(-S);}
    vector<int> ft;
    vector<int> pointQueries;
  public:
    FenwickTree(int n) {
      ft.assign(n+1,0);
      pointQueries.assign(n+1,0);
    }
    void update(int i,int v) {
      pointQueries[i] += v;
      for (;i<ft.size();i+= LSOne(i)) {
        ft[i] += v;
      }
    }
    int rsq(int j) {
      int acc = 0;
      for (;j>0;j-=LSOne(j)) {
        acc += ft[j];
      }
      return acc;
    }
    int rsq(int i, int j) {
      return rsq(j) - rsq(i-1);
    }
    int pointQuery(int i) {
      return pointQueries[i];
    }
};
