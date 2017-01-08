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
    bool flag;
    int rank;
    vector<element*> previous;
    vector<element*> next;
    int earliest_date;
    int sum_e_date_duration;
    int latest_date;
    int diff_l_date_duration;
    int sum_l_date_duration;
};






vector<element> fill_graph (tt_contraintes* lesContraintes, vector<element> graph,tt_graphe* leGraphe);
void display_graph_content (vector<element> graph);
vector<element> modify_element (vector<element> graph, tt_contraintes* lesContraintes, tt_graphe* leGraphe, element* current, element* next);

void free_memory (tt_contraintes* lesContraintes, tt_graphe* leGraphe, vector<element> graph, element* current, element* next);
void reading_graph (vector<element> &graph);
int scan_graph (vector<element> graph, element* current);
void rank_computation (vector<element> graph, map<char, element> &graph_back_up);
void set_graph_cresc (map<char, element> graph_back_up, multimap<int, element> &graph_cresc);
void set_earliest_date (multimap<int, element> &graph_cresc);
void display_graph_cresc (multimap<int, element> &graph_cresc);
void set_latest_date (multimap<int, element> &graph_cresc);
void display_latest_dates (multimap<int, element> &graph_cresc);
#endif /* dan_fonctions_hpp */
