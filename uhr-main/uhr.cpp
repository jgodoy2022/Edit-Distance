/** uhr: generic time performance tester
 * Author: LELE
 *
 * Things to set up:
 * 0. Includes: include all files to be tested,
 * 1. Time unit: in elapsed_time,
 * 2. What to write on time_data,
 * 3. Data type and distribution of RNG,
 * 4. Additive or multiplicative stepping,
 * 5. The experiments: in outer for loop. */

#include <cstdint>
#include <chrono>
#include <cmath>
#include <fstream>
#include <iostream>
#include <random>
#include <vector>

#include "utils.cpp"

// Include to be tested files here
#include "../dp.cpp"
#include "../memo.cpp"
#include "../recursive.cpp"

int main(int argc, char *argv[])
{
    // Validate and sanitize input
    std::int64_t runs, lower, upper, step;
    validate_input(argc, argv, runs, lower, upper, step);

    // Set up clock variables
    std::int64_t n, i, executed_runs;
    std::int64_t total_runs_additive = runs * (((upper - lower) / step) + 1);
    std::int64_t total_runs_multiplicative = runs * (floor(log(upper / double(lower)) / log(step)) + 1);
    std::vector<double> times(runs);
    std::vector<double> q;
    double mean_time, time_stdev, dev;
    auto begin_time = std::chrono::high_resolution_clock::now();
    auto end_time = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::nano> elapsed_time = end_time - begin_time;

    // Set up random number generation
    std::random_device rd;
    std::mt19937_64 rng(rd());
    std::uniform_int_distribution<std::int64_t> u_distr; // change depending on app

    // File to write time data
    std::ofstream time_data;
    time_data.open(argv[1]);
    time_data << "n,t_mean,t_stdev,t_Q0,t_Q1,t_Q2,t_Q3,t_Q4" << std::endl;

    // Begin testing
    std::cerr << "\033[0;36mRunning tests...\033[0m" << std::endl << std::endl;
    executed_runs = 0;
    for (n = lower; n <= upper; n += step) {
        mean_time = 0;
        time_stdev = 0;
        // Test configuration goes here


        std::string s1 = "quijada quesada";
        std::string s2 = "don quijote de la mancha";
        std::string s3 = "en un lugar de la mancha, de cuyo nombre no quiero acordarme, no ha mucho tiempo que vivía un hidalgo de los de lanza en astillero, adarga antigua, rocín flaco y galgo corredor";
        std::string s4 = "y, diciendo esto, dio de espuelas a su caballo rocinante, sin atender a las voces que su escudero sancho le daba, advirtiéndole que, sin duda alguna, eran molinos de viento, y no gigantes, aquellos que iba a acometer. pero él iba tan puesto en que eran gigantes, que ni oía las voces de su escudero sancho ni echaba de ver, aunque estaba ya bien cerca, lo que eran; antes, iba diciendo en voces altas: non fuyades, cobardes y viles criaturas, que un solo caballero es el que os acomete";

        /******************************
         ***Test algoritmo recursivo***
         ******************************/
/*
        // todas las transiciones posibles para recursive: 
        std::cout << editDistanceRecInit(s1, s2);
        std::cout << editDistanceRecInit(s1, s3);
        std::cout << editDistanceRecInit(s1, s4);
        std::cout << editDistanceRecInit(s2, s3);
        std::cout << editDistanceRecInit(s2, s4);
        std::cout << editDistanceRecInit(s3, s4);
*/

        /************************************
         ***Test algoritmo con memoization***
         ************************************/
/*
        std::cout << editDistanceMemoInit(s1, s2);
        std::cout << editDistanceMemoInit(s1, s3);
        std::cout << editDistanceMemoInit(s1, s4);
        std::cout << editDistanceMemoInit(s2, s3);
        std::cout << editDistanceMemoInit(s2, s4);
        std::cout << editDistanceMemoInit(s3, s4);
*/

        /***************************
         ***Test algoritmo con DP***
         ***************************/
/*
        std::cout << editDistanceDp(s1, s2);
        std::cout << editDistanceDp(s1, s3);
        std::cout << editDistanceDp(s1, s4);
        std::cout << editDistanceDp(s2, s3);
        std::cout << editDistanceDp(s2, s4);
        std::cout << editDistanceDp(s3, s4);
*/

        /*******************************
         ***Test algoritmo con DP-opt***
         *******************************/
/*
        std::cout << editDistanceOpt(s1, s2);
        std::cout << editDistanceOpt(s1, s3);
        std::cout << editDistanceOpt(s1, s4);
        std::cout << editDistanceOpt(s2, s3);
        std::cout << editDistanceOpt(s2, s4);
        std::cout << editDistanceOpt(s3, s4);
*/

        // Run to compute elapsed time
        for (i = 0; i < runs; i++) {
            // Remember to change total depending on step type
            display_progress(++executed_runs, total_runs_additive);

            begin_time = std::chrono::high_resolution_clock::now();
            // Function to test goes here
            end_time = std::chrono::high_resolution_clock::now();

            elapsed_time = end_time - begin_time;
            times[i] = elapsed_time.count();

            mean_time += times[i];
        }

        // Compute statistics
        mean_time /= runs;

        for (i = 0; i < runs; i++) {
            dev = times[i] - mean_time;
            time_stdev += dev * dev;
        }

        time_stdev /= runs - 1; // Subtract 1 to get unbiased estimator
        time_stdev = std::sqrt(time_stdev);

        quartiles(times, q);

        time_data << n << "," << mean_time << "," << time_stdev << ",";
        time_data << q[0] << "," << q[1] << "," << q[2] << "," << q[3] << "," << q[4] << std::endl;
    }

    // This is to keep loading bar after testing
    std::cerr << std::endl << std::endl;
    std::cerr << "\033[1;32mDone!\033[0m" << std::endl;

    time_data.close();

    return 0;
}
