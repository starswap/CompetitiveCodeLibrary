#include <bits/stdc++.h>
using namespace std;
template <typename b,typename a>
ostream& operator << (ostream& o, pair<a,b> p) {
  o << "(" << p.first << "," << p.second << ")";
  return o;
}

template <typename T>
ostream& operator << (ostream& o, vector<T> v) {
  o << "[";
  for (auto a : v) {
    o << a << ",";
  }
  o << "]";
  return o;
}

template <typename T>
ostream& operator << (ostream& o, set<T> v) {
  o << "{";
  for (auto a : v) {
    o << a << ",";
  }
  o << "}";
  return o;
}

ostream& operator << (ostream& o, bool b) {
  if (b == true)
    o << "true";
  else
    o << "false";
  return o;
}
