#ifndef BENRANDOM
#define BENRANDOM

#include <cstdlib>
#include <ctime>

//  fonction pour la gestion du hazard

void setrand();

//  si pas de parametre renvois un nombre entre 1 et 6 sinon entre 1 et le nombre donné
int de(int FACES=6);

//  renvoi un nombre au hazard entre MIN et MAX. 99 et 0 si pas de parametre
int random(int MAX=99,int MIN=0);

#endif // BEN_RANDOM_H_INCLUDED
