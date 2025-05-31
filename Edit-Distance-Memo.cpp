#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
using namespace std;

int editDistRec(string& s1, string& s2, int m, int n, vector<vector<int>> &memo){

  if (m==0){
    return n;
  }

  if (n==0){
    return m;
  }

  if (memo[m][n]!=-1){
    return memo[m][n];
  }

  if (s1[m-1]==s2[n-1]){
    return memo[m][n] = editDistRec(s1, s2, m-1, n-1, memo);
  }

  return memo[m][n] = 1 + min({editDistRec(s1, s2, m, n-1, memo),
                              editDistRec(s1, s2, m-1, n, memo)});
}


int editDistance(string& s1, string& s2){
  int m = s1.length(), n = s2.length();
  vector<vector<int>> memo(m+1, vector<int>(n+1, -1));
  return editDistRec(s1, s2, m, n, memo); 
}


int main(){

  string s1 = "intention";
  string s2 = "algorithm";

  cout << editDistance(s1, s2);

  return 0;
}