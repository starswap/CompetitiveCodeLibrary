class SegmentTree {
  private:
    vector<int> st;
    vector<bool> lazy;
    int n;
    inline int parent(int a) {return a>>1;}
    inline int lChild(int a) {return a<<1;}
    inline int rChild(int a) {return (a<<1) + 1;}
    inline int compare(int a,int b) {return min(a,b);} //CHANGE THIS TO GO FROM RMQ TO RMQ TO RSQ (RSQ does require a bit more work)

    void build(vector<int> &A,int L,int R,int p) {
      if (L==R) {st[p] = A[L];}
      else if (L > R) {return;}
      else {
        int middle = (L+R)/2;
        build(A,L,middle,lChild(p));
        build(A,middle+1,R,rChild(p));
        st[p] = compare(st[lChild(p)],st[rChild(p)]);
      }
    }

    void propagateLazy(int L, int R, int p) {
      if (L == R) {lazy[p] = false;}
      if (lazy[p] == true) {
        lazy[lChild(p)] = true;
        lazy[rChild(p)] = true;
        st[lChild(p)] = st[p];
        st[rChild(p)] = st[p];
        lazy[p] = false;
      }
    }

    void rangeUpdate(int i,int j,int L, int R, int val,int p) {
        propagateLazy(L,R,p);
        if (L >= i && R <= j) { //we are within the required range
          st[p] = val;
          lazy[p] = true; //may need to popagate lazy flags again here.
        } 
        else {
          int leftMax = (L+R)/2;
          if (i > leftMax) { //desired range fully enclosed by right child of this node
            rangeUpdate(i,j,leftMax+1,R,val,rChild(p));
          } else if (j <= leftMax) { //desired range fully enclosed by left child of this node
            rangeUpdate(i,j,L,leftMax,val,lChild(p));
          } else { //desired range split across both children of this node.
            rangeUpdate(i,leftMax,L,leftMax,val,lChild(p));
            rangeUpdate(leftMax+1,j,leftMax+1,R,val,rChild(p));
          }
          st[p] = compare(st[lChild(p)],st[rChild(p)]);
        }
    }
    
    int RMQ(int i, int j, int L, int R, int p) {
      propagateLazy(L,R,p);
      if (L >= i && R <= j) {return st[p];}
      else {
        int leftMax = (L+R)/2;
        if (i > leftMax) { //desired range fully enclosed by right child of this node
          return RMQ(i,j,leftMax+1,R,rChild(p));
        } else if (j <= leftMax) { //desired range fully enclosed by left child of this node
          return RMQ(i,j,L,leftMax,lChild(p));
        } else { //desired range split across both children of this node.
          return compare(RMQ(i,leftMax,L,leftMax,lChild(p)),RMQ(leftMax+1,j,leftMax+1,R,rChild(p)));
        }
        st[p] = compare(st[lChild(p)],st[rChild(p)]);
      }
    }


  public:
    SegmentTree (vector<int> A) {
      n = A.size();
      st.assign(4*n,-1); //4* should give enough space.
      lazy.assign(4*n,false);
      build(A,0,n-1,1); //NOTE: the internal indexing (on st) should start from 1.
    }

    void rangeUpdate(int i, int j,int val) {
      rangeUpdate(i,j,0,n-1,val,1);
    }

    int RMQ(int i, int j) {
      return RMQ(i,j,0,n-1,1);
    }

};
