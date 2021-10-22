//IDA* notes: Remember to actually do the heuristic
//Complexity not known - estimate branch factor!
//Check does h=0 and not does puzzle=end
//Can increase limit by 2 at a time?
//**Don't allocate any memory inside the heuristic delta function - just return and inline it. 
//Remember to not consider zero / do consider zero as required.
//pass by reference
//make path global.
//**Avoid going back on previous paths.
//Don't pass puzzle around even by reference.
//USE 1D array - not 2D and not vector.
//Can use the dr dc arrays techinque for less code
//Add two to lim not 1 per time?
//**Get the right heuristic
//*****Can check whether it is solvable before actually trying to sovle it. - use parity
//Remember to reset path.

#include <bits/stdc++.h>
using namespace std;
const int CAP = 45; //Doesn't really matter what value we put here - if the puzzle is unsolvable we will know without going this far. If not, we need to go as far as possible anyway. 
char path[CAP];
int puzzle[9];

inline int k(int i, int j) {
  return 3*i+j;
}

inline int h1() {
  int h1 = 0;
  for (int i=0;i<3;++i) {
    for (int j=0;j<3;++j) {
      if (puzzle[k(i,j)] != 0) {
        int goalI = (puzzle[k(i,j)]-1)/3;
        int goalJ = (puzzle[k(i,j)]-1)%3;
        h1 += abs(i-goalI);
        h1 += abs(j-goalJ);
      }
    }
  }
  return h1;
}

inline int newH(int h1,int s1i, int s1j, int s2i, int s2j) {
  return h1-abs((puzzle[k(s1i,s1j)]-1)/3-s1i)-abs((puzzle[k(s1i,s1j)]-1)%3-s1j)+abs((puzzle[k(s1i,s1j)]-1)/3-s2i)+abs((puzzle[k(s1i,s1j)]-1)%3-s2j);
}


bool dfs(int max,int zI, int zJ,int h,int g, int prev) {
  //cout << puzzle << h << endl;
  if (g+h > max)
    return false;
  if (h == 0) {
   // cout << puzzle << endl;
    return true;
  }
  //move up
  if (zI != 0 && prev != 1) {
    int h2 = newH(h,zI-1,zJ,zI,zJ); 
    swap(puzzle[k(zI,zJ)],puzzle[k(zI-1,zJ)]);
    if (dfs(max,zI-1,zJ,h2,g+1,0)) {
      path[g] = 'u';
      return true;
    }
    swap(puzzle[k(zI,zJ)],puzzle[k(zI-1,zJ)]);
  }
  //move down
  if (zI != 2 && prev != 0) {
    int h2 = newH(h,zI+1,zJ,zI,zJ); 
    swap(puzzle[k(zI,zJ)],puzzle[k(zI+1,zJ)]);
    if (dfs(max,zI+1,zJ,h2,g+1,1)) {
      path[g] = 'd';
      return true;
    }    
    swap(puzzle[k(zI,zJ)],puzzle[k(zI+1,zJ)]);
  }
  if (zJ != 0 && prev != 3) {
    int h2 = newH(h,zI,zJ-1,zI,zJ); 
    swap(puzzle[k(zI,zJ)],puzzle[k(zI,zJ-1)]);
    if (dfs(max,zI,zJ-1,h2,g+1,2)) {
      path[g] = 'l';
      return true;
    }      
    swap(puzzle[k(zI,zJ)],puzzle[k(zI,zJ-1)]);
  }  
  if (zJ != 2 && prev != 2) {
    int h2 = newH(h,zI,zJ+1,zI,zJ); 
    swap(puzzle[k(zI,zJ)],puzzle[k(zI,zJ+1)]);
    if (dfs(max,zI,zJ+1,h2,g+1,3)) {
      path[g] = 'r';
      return true;
    }    
    swap(puzzle[k(zI,zJ)],puzzle[k(zI,zJ+1)]);
  }
  return false;
}

bool IDA_Star(int zI, int zJ) {
  int max = h1();
  while (max < CAP) {
    if (dfs(max,zI,zJ,h1(),0,-1))
      return true;
    max += 2;
    //cout << max << endl;
  }
  return false; 
}


int main() {
  ios::sync_with_stdio(false);
  cin.tie(NULL);
  int N; cin >> N;
  for (int n=0;n<N;++n) {
    memset(path,0,45);
    int zI; int zJ;
    for (int i=0;i<3;++i) {
      for (int j=0;j<3;++j) {
        char a;
        cin >> a;
        if (a == 'x') {
          puzzle[k(i,j)] = 0;
          zI = i;
          zJ = j;
        }
        else
          puzzle[k(i,j)] = a - 48;
      }
    }

    int noInversions = 0;
    for (int b=0;b<9;b++) {
      if (puzzle[b] == 0) continue;
      else {
        for (int c=0;c<b;c++) {
          if (puzzle[c] == 0) continue;
          noInversions += (puzzle[c] < puzzle[b]);
        }
      }
    }
    
    if (noInversions % 2 == 1 || !IDA_Star(zI,zJ))
      cout << "unsolvable" << endl;
    else {
      for (int i=0; i < CAP; ++i) {
        if (path[i] == 'l' || path[i] == 'r' || path[i] == 'u' || path[i] == 'd')
        cout << path[i];
      }
      cout << endl;
    }
    if (n != N-1)
      cout << endl;
  }
}
