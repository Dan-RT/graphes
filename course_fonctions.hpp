//
//  course_fonctions.hpp
//  Projet Graphes
//
//  Created by Daniel Regnard on 12/12/2016.
//  Copyright © 2016 A. All rights reserved.
//

#ifndef course_fonctions_hpp
#define course_fonctions_hpp

#include <stdio.h>

#include <iostream>
#include <stdio.h>
#include <fstream>
using namespace std;

typedef struct {
    int nbTaches;
    char* nomTaches;
    int *durees;
    char*contrainte;
}tt_contraintes;

typedef struct
{
    int nbSommets;
    bool** adj;
    int** val;
}tt_graphe;

int loading(string id_graph);
void ajouterContrainte(tt_contraintes* lesContraintes, char tacheCourante, char contrainteCourante);

#endif /* course_fonctions_hpp */
