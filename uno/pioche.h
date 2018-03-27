#ifndef PIOCHE_H
#define PIOCHE_H

#include <iostream>
#include<algorithm>
#include<vector>
#include"carte.h"
#include"cartenombre.h"
#include"changementcouleur.h"
#include"changementsens.h"
#include"plus2.h"
#include"plus4.h"
#include"tagueule.h"

#define N_CARTES 108

class Pioche
{
    public:
        Pioche();
        std::vector<Carte> pile;

        void melanger();
        void afficher();
        Carte tirerCarte();
};

#endif // PIOCHE_H