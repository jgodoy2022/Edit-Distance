#include <iostream>
#include <string>
#include <fstream>

#include "../recursive.cpp"
#include "../memo.cpp"
#include "../dp.cpp"
#include "../dp_opt.cpp"

// /usr/bin/time -f "%M" ./programa (peak de memoria en kb)

int main(int argc, char const *argv[])
{
	std::string s4 = "y, diciendo esto, dio de espuelas a su caballo rocinante, sin atender a las voces que su escudero sancho le daba, advirtiéndole que, sin duda alguna, eran molinos de viento, y no gigantes, aquellos que iba a acometer. pero él iba tan puesto en que eran gigantes, que ni oía las voces de su escudero sancho ni echaba de ver, aunque estaba ya bien cerca, lo que eran; antes, iba diciendo en voces altas: non fuyades, cobardes y viles criaturas, que un solo caballero es el que os acomete";
    std::string s1 = "quijada quesada";
    std::string s2 = "don quijote de la mancha";
    std::string s3 = "en un lugar de la mancha, de cuyo nombre no quiero acordarme, no ha mucho tiempo que vivía un hidalgo de los de lanza en astillero, adarga antigua, rocín flaco y galgo corredor";

    editDistanceOpt(s3,s4);
    
	return 0;
}
