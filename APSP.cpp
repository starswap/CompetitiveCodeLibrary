vector<vector<int>> FloydWarshall(vector<vector<int>> AM,int N) {
	
	for (int k=0;k<N;k++) {
		for (int i=0;i<N;i++) {
			for (int j=0;j<N;j++) {
				AM[i][j] = min(AM[i][j],AM[i][k] + AM[k][j]);
			}
		}
	}
	
	return AM;
}
