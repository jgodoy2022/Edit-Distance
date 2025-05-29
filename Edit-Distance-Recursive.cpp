#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

// Función recursiva para encontrar la cantidad de operaciones
// necesarias para convertir un string s1 en un string s2
int editDistRec(string& s1, string& s2, int m, int n) {
  
    // Si el primer string esta vacio inserta todos
    // los caracteres del segundo string en el primero
    if (m == 0) return n;

    // Si el segundo string esta vacio se eliminan
    // todos los caracteres del primer string 
    if (n == 0) return m;

    // si el ultimo caracter de dos strings son los mismos
    // se toma la diagonal de la matriz (Representa la cantidad de operaciones realizadas anteriormente)
    if (s1[m - 1] == s2[n - 1]) 
      return editDistRec(s1, s2, m - 1, n - 1);

    // Si los ultimos caracteres no son los mismos considerar la
    // cantidad de operaciones de las dos cadenas adyacentes (izquierda y arriba)
    // de manera recursiva y retornar el minimo entre ambas operaciones y sumarle 1
    return 1 + min({editDistRec(s1, s2, m, n - 1),  
                    editDistRec(s1, s2, m - 1, n)}); 
}

// Funcion para iniciar el calculo recursivo
int editDistance(string& s1, string& s2) {
    return editDistRec(s1, s2, s1.length(), s2.length());
}

int main() {
    
    string s1 = "intention";
    string s2 = "algorithm";

    cout << editDistance(s1, s2);

    return 0;
}