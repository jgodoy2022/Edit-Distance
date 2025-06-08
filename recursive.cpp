#include <iostream>
#include <string>
#include <algorithm>
#include <chrono>
// Función recursiva para encontrar la cantidad de operaciones
// necesarias para convertir un string s1 en un string s2
// Input: s1 y s2 strings, m y n sus largos respectivamente
// Output: cantidad mínima de operaciones para llegar de un string a otro
int editDistRec(std::string& s1, std::string& s2, int m, int n) {
  
    // Si el primer string esta vacio inserta todos
    // los caracteres del segundo string en el primero
    if (m == 0) return n;

    // Si el segundo string esta vacio se eliminan
    // todos los caracteres del primer string 
    if (n == 0) return m;

    // Si el ultimo caracter de dos strings son los mismos
    // se obtiene el recuento para las subcadenas restantes
    if (s1[m - 1] == s2[n - 1]) 
      return editDistRec(s1, s2, m - 1, n - 1);

    // Si los ultimos caracteres no son los mismos calcular el minimo entre
    // insertar un caracter en s1 o eliminar un caracter en s1
    return 1 + std::min({editDistRec(s1, s2, m, n - 1),  
                    editDistRec(s1, s2, m - 1, n)}); 
}

// Funcion para iniciar el calculo recursivo
int editDistanceRecInit(std::string& s1, std::string& s2) {
    return editDistRec(s1, s2, s1.length(), s2.length());
}
/*
int main() {
    std::string s1 = "quijada quesada";
    std::string s3 = "en un lugar de la mancha, de cuyo nombre no quiero acordarme, no ha mucho tiempo que vivía un hidalgo de los de lanza en astillero, adarga antigua, rocín flaco y galgo corredor";
  
 
    auto start = std::chrono::high_resolution_clock::now();
    std::cout << editDistanceRecInit(s1, s3);
    auto end = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double> duration = end - start;

    std::cout << "Tiempo de ejecución: " << duration.count() << " segundos" << std::endl;
    return 0;
}
*/