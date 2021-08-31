class Point {
  public:
    int x;
    int y;
    Point(int a, int b):x(a),y(b) {};
    Point():x(0),y(0) {};
};

bool operator < (Point a, Point b) {
  if (a.x < b.x)
    return true;
  else if (a.x == b.x && a.y < b.y)
    return true;
  else
    return false;
}

ostream& operator << (ostream& o, Point p) {
  o << p.x << " " << p.y;
  return o;
}

float cross(Point a,Point b) {
  return (a.x*b.y - b.x*a.y);
}
bool ccw(Point a,Point b,Point c) {
  Point ab(b.x-a.x,b.y-a.y);
  Point ac(c.x-a.x,c.y-a.y);
  return cross(ab,ac) > 0;
}

vector<Point> AndrewConvexHull(vector<Point> pts) {
  int n = pts.size();
  sort(pts.begin(),pts.end());
  vector<Point> hull(2*n);

  //Build Lower hull
  int top = 0;
  for (int pointToConsider = 0;pointToConsider < n;pointToConsider++) {
    while (top >= 2 && !ccw(hull[top-2],hull[top-1],pts[pointToConsider])) {//while we have at least 2 points to in the hull and adding the next point would maken a non ccw turn we need to remove the top point
      top--;
    }
    hull[top] = pts[pointToConsider];
    top++;
  }
//we already did the furthest away point so start at n-2.
  int endOfFirstHalf = top;
  for (int pointToConsider = n-2;pointToConsider >= 0; pointToConsider--) {
    while (top > endOfFirstHalf && !ccw(hull[top-2],hull[top-1],pts[pointToConsider])) {
      top--;
    }
    hull[top] = pts[pointToConsider];
    top++;
  }
  hull.resize(top-1); //now has the correct size. Remove duplicate reference to first point - change to top depending on what question requires.
  return hull;
}
