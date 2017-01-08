//
//  dynamic_circuit.hpp
//  Projet Graphes
//
//  Created by Daniel Regnard on 08/01/2017.
//  Copyright © 2017 A. All rights reserved.
//

#ifndef dynamic_circuit_hpp
#define dynamic_circuit_hpp

#include <stdio.h>
#include "dan_fonctions.hpp"


void fill_graph_dynamic (tt_contraintes* lesContraintes, vector<element*> &graph_dynamic);
void modify_element_dynamic (vector<element*> &graph_dynamic, tt_contraintes* lesContraintes, tt_graphe* leGraphe);
void free_dynamic_memory (vector<element*> &graph_dynamic);
void display_graph_dynamic_content (vector<element*> graph_dynamic);
int reading_graph_dynamic (vector<element*> &graph_dynamic);
void copy_dynamic_to_static (vector<element*> &graph_dynamic, vector<element> &graph);
void display_graph_dynamic_map (map<char, element*> graph_dynamic_back_up);
void delete_circuit_dynamic (vector<element*> &graph_dynamic, char depart, char destination) ;
#endif /* dynamic_circuit_hpp */
