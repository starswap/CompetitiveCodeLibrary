//Newline between test cases
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
  
  
//function call style input with variable number of arguments
vector<int> args;
for (int q=0;q<Q;q++) {
    char action[50]; //May need to update to max line length.
    args.clear();

    scanf("\n%[^\(](",action); //Read the function name up to the bracket
    int nextArg;
    while (scanf("%d,",&nextArg) != 0) { //pull in each argument
      args.push_back(nextArg);
    }
    scanf(")"); //consume the end line
  
    if (strcmp(action,"shift") == 0) { 
      MANIPULATESOMETHING(args); //e.g.
    } else {
      printf("%d\n",DOSOMETHINGTOOUTPUT(args[0],args[1])); //e.g.
    }
}
