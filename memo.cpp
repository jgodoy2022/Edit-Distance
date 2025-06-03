#include <iostream>
#include <algorithm>
#include <vector>
#include <string>

// Función recursiva que calcula la cantidad de operaciones necesarias
// para convertir s1 en s2.
int editDistRec(std::string& s1, std::string& s2, int m, int n, std::vector<std::vector<int>> &memo){

  // Si s1 está vacío, retorna n porque necesita n inserciones 
  // para transformar s1 a s2. 
  if (m==0){
    return n;
  }

  // Si s2 está vacío, retorna m porque necesita m eliminaciones
  // para transformar s1 a s2. 
  if (n==0){
    return m;
  }

  // Verifica si ya se calculo la distancia para m,n. 
  if (memo[m][n] != -1){
    return memo[m][n];
  }

  // Si los últimos caracteres coinciden, avanzamos recursivamente 
  // sin costo (no se suma 1), hasta alcanzar algún caso base. 
  if (s1[m-1]==s2[n-1]){
    return memo[m][n] = editDistRec(s1, s2, m-1, n-1, memo);
  }

  // Si los últimos caracteres son diferentes, se toma el 
  // mínimo de las dos operaciones y se suma 1. 
  return memo[m][n] = 1 + std::min({editDistRec(s1, s2, m, n-1, memo),
                              editDistRec(s1, s2, m-1, n, memo)});
}


// Función que inicia el calculo recursivo
int editDistance(std::string& s1, std::string& s2){
  int m = s1.length(), n = s2.length();

  // Inicializa la tabla(matriz) con -1. 
  std::vector<std::vector<int>> memo(m+1, std::vector<int>(n+1, -1)); 
  return editDistRec(s1, s2, m, n, memo); 
}


int main(){

  std::string s1 = "intention";
  std::string s2 = "algorithm";

  std::cout << editDistance(s1, s2);

  return 0;
}