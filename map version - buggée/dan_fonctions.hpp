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


map<char, element> fill_graph (tt_contraintes* lesContraintes, map<char, element> graph,tt_graphe* leGraphe);
void display_graph_content (map<char, element> graph);
map<char, element> modify_element (map<char, element> graph, tt_contraintes* lesContraintes, tt_graphe* leGraphe, element* current, element* next);

void free_memory (tt_contraintes* lesContraintes, tt_graphe* leGraphe, map<char, element> graph, element* current, element* next);
void reading_graph (map<char, element> graph);
int scan_graph (map<char, element> graph, element* current);
void rank_computation (map<char, element> graph);

#endif /* dan_fonctions_hpp */
