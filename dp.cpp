#include <iostream>
#include <vector>
#include <algorithm>

int editDistanceDp(std::string &s1, std::string &s2){

  int m = s1.length();
  int n = s2.length();

  // Se crea una matriz para guardar los resultados de
  // la cantidad de operaciones
  std::vector<std::vector<int>> dp(m+1, std::vector<int>(n+1));

  // inicializa la primera fila y columna, con 0 a m y con 0 a n, 
  // respectivamente. 
  for(int i=0; i<=m; i++){
    dp[i][0] = i;
  }
  for(int j=0; j<=n; j++){
    dp[0][j] = j;
  }

  // llena el resto de la matriz, calculando la cantidad.
  for(int i=1; i<=m; i++){
    for(int j=1; j<=n; j++){
      if(s1[i-1] == s2[j-1]){
        dp[i][j] = dp[i-1][j-1];
      }
      else{
        dp[i][j] = 1 + std::min({dp[i][j-1], dp[i-1][j]});
      }
    }
  }

  return dp[m][n];
}
/*
int main(){
  
  std::string s1 = "intention";
  std::string s2 = "algorithm";

  std::cout << editDistanceDp(s1, s2);

  return 0;
}
*/