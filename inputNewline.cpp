int main() {
  int T;
  cin >> T;
  string line;
  getline(cin,line); //newline after number of tests
  for (int t=0;t<T;t++) {
    
    //e.g. - anything that comes as the first line
    int x,y;
    cin >> x;
    cin >> y;
    
    //get end of line
    getline(cin,line);
    for (getline(cin,line);line != "" && !cin.eof();getline(cin,line)) {
      //e.g. - anything coming on every line
      int x1,y1,x2,y2;
      sscanf(line.c_str(),"%d %d %d %d",&x1,&y1,&x2,&y2);
      //process...
    }

    
     //compute and output result
    
    
    
    if (t != T-1) {
      cout << "\n";
    }
  }
