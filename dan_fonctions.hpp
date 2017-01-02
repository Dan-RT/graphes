//
//  dan_fonctions.hpp
//  Projet Graphes
//
//  Created by Daniel Regnard on 01/01/2017.
//  Copyright © 2017 A. All rights reserved.
//

#ifndef dan_fonctions_hpp
#define dan_fonctions_hpp

#include <stdio.h>
#include "course_fonctions.hpp"

typedef struct element element;
struct element {
    char name;
    int duration;
    int rank;
    vector<element*> previous;
    vector<element*> next;
};


vector<element> fill_graph (tt_contraintes* lesContraintes, vector<element> graph,tt_graphe* leGraphe);
void display_graph_content (vector<element> graph);
vector<element> modify_element (vector<element> graph, tt_contraintes* lesContraintes, tt_graphe* leGraphe, element* current, element* next);

void free_memory (tt_contraintes* lesContraintes, tt_graphe* leGraphe, vector<element> graph, element* current, element* next);
void reading_graph (vector<element> graph);
int scan_graph (vector<element> graph, element* current);
void rank_computation (vector<element> graph);

#endif /* dan_fonctions_hpp */
