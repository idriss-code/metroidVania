#include "benrandom.h"

void setrand()
{
    srand(time(NULL));
}

int de(int FACES)
{
    return rand()%FACES+1;
}

int random(int MAX,int MIN)
{
    int NB=MAX-MIN+1;
    return rand()%NB+MIN;
}
