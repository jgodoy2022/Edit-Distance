#include <bits/stdc++.h>

// Calcula la distancia de edicion entre s1 y s2,
// considerando solo inserciones y eliminaciones.
int editDistance(std::string &s1, std::string &s2) {

    // Largo de las cadenas
    int m = s1.size();
    int n = s2.size();
    
    // Almacena dp[i-1][j-1]
    int prev; 

    // Vector que representa la fila actual de la matriz de DP
    std::vector<int> curr(n + 1, 0); 

    // Inicializa la primera fila con la distancia desde cadena vacia a s2
    for (int j = 0; j <= n; j++)
        curr[j] = j;
    
    // Itera sobre cada caracter de s1   
    for (int i = 1; i <= m; i++) {
        prev = curr[0]; 
        curr[0] = i;

        // Itera sobre cada caracter de s2
        for (int j = 1; j <= n; j++) {
            int temp = curr[j];

            // Si el ultimo caracter de ambos strings son el mismo
            // no se necesitan operaciones
            if (s1[i - 1] == s2[j - 1])
                curr[j] = prev;

            // Si no son los mismos se elige la operacion mas barata entre 
            // eliminar de s1 (curr[j]) o insertar en s1 (curr[j-1])
            else
                curr[j] = 1 + std::min({curr[j - 1], curr[j]});
            prev = temp;
        }
    }
    
    // Distancia de edicion completa
    return curr[n];
}

int main() {
    std::string s1 = "intention";
    std::string s2 = "execution";

    std::cout << editDistance(s1, s2);

    return 0;
}