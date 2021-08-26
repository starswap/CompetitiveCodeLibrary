template<typename T> //Supports varying size numeric types e.g. int / long / long long as necessary
class FenwickTree {
  public:
   FenwickTree(T m) {
     ft.assign(m+1,0);
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

  private:
    inline T LSOne (T i) {return i&(-i);}
    vector<T> ft;
};
