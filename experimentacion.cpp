#include <iostream>
#include <fstream>
#include <chrono>
#include <string>
#include <vector>
#include <cmath>

// Incluye la implementación que deseas medir
#include "dp.cpp"
#include "memo.cpp"
#include "recursive.cpp"
#include "dp_opt.cpp"

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Uso: " << argv[0] << " <archivo_salida.csv>\n";
        return 1;
    }

    std::string archivo_salida = argv[1];

    std::string s1 = "quijada quesada";
    std::string s2 = "don quijote de la mancha";
    std::string s3 = "en un lugar de la mancha, de cuyo nombre no quiero acordarme, no ha mucho tiempo que vivía un hidalgo de los de lanza en astillero, adarga antigua, rocín flaco y galgo corredor";
    std::string s4 = "y, diciendo esto, dio de espuelas a su caballo rocinante, sin atender a las voces que su escudero sancho le daba, advirtiéndole que, sin duda alguna, eran molinos de viento, y no gigantes, aquellos que iba a acometer. pero él iba tan puesto en que eran gigantes, que ni oía las voces de su escudero sancho ni echaba de ver, aunque estaba ya bien cerca, lo que eran; antes, iba diciendo en voces altas: non fuyades, cobardes y viles criaturas, que un solo caballero es el que os acomete";
    const int runs = 10;
    std::vector<double> tiempos;

    for (int i = 0; i < runs; ++i) {
        std::chrono::high_resolution_clock::time_point start = std::chrono::high_resolution_clock::now();

        int resultado = editDistanceRecInit(s1, s3);  // Cambia la función si lo deseas

        std::chrono::high_resolution_clock::time_point end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> dur = end - start;  // Tiempo en segundos
        tiempos.push_back(dur.count());
    }

    // Estadísticas
    double suma = 0.0;
    for (double t : tiempos) suma += t;
    double promedio = suma / runs;

    double varianza = 0.0;
    for (double t : tiempos) varianza += (t - promedio) * (t - promedio);
    double desviacion = std::sqrt(varianza / runs);

    // Mostrar resultados
    std::cout << "Resultado algoritmo: " << editDistanceDp(s1, s2) << std::endl;
    std::cout << "Tiempo promedio: " << promedio << " segundos" << std::endl;
    std::cout << "Desviación estándar: " << desviacion << " segundos" << std::endl;

    // Guardar CSV
    std::ofstream archivo(archivo_salida);
    if (!archivo.is_open()) {
        std::cerr << "No se pudo abrir el archivo: " << archivo_salida << std::endl;
        return 1;
    }

    archivo << "iteracion,tiempo_segundos\n";
    for (int i = 0; i < runs; ++i) {
        archivo << i + 1 << "," << tiempos[i] << "\n";
    }
    archivo << "\nPromedio:," << promedio << "\n";
    archivo << "Desviacion:, " << desviacion << "\n";
    archivo.close();

    return 0;
}