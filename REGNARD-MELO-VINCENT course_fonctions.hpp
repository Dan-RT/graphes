//
//  course_fonctions.hpp
//  Projet Graphes
//
//  Created by Daniel Regnard on 12/12/2016.
//  Copyright © 2016 A. All rights reserved.
//

#ifndef course_fonctions_hpp
#define course_fonctions_hpp

#include <iostream>
#include <stdio.h>
#include <fstream>
#include <map>
#include <vector>

using namespace std;

typedef struct {
    int nbTaches;
    char* nomTaches;
    int* durees;
    map<char, vector<char>> contraintes;
    
}tt_contraintes;

typedef struct
{
    int nbSommets;
    bool** adj;
    int** val;
}tt_graphe;

int loading(string id_graph, tt_contraintes* lesContraintes, tt_graphe* leGraphe);
void ajouterContrainte(tt_contraintes* lesContraintes, char tacheCourante, char contrainteCourante, int cpt);


#endif /* course_fonctions_hpp */
