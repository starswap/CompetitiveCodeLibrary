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
