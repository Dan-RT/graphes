//
//  main.cpp
//  Projet Graphes
//
//  Created by Daniel Regnard on 12/12/2016.
//  Copyright © 2016 A. All rights reserved.
//

#include <iostream>
#include "load.hpp"
#include "course_fonctions.hpp"
#include "display.hpp"
#include "dan_fonctions.hpp"

void display_earliest_dates (multimap<int, element> &graph_cresc);

int main(int argc, const char * argv[]) {
   
    string id_graph = "";
    
    cout << "ENTER THE NUMBER OF YOUR GRAPH :" << endl;
    cin >> id_graph;
    
    tt_contraintes* lesContraintes = new tt_contraintes;
    tt_graphe* leGraphe =  new tt_graphe;
    element* current = nullptr;
    element* next = nullptr;
    
    vector<element> graph;
    map<char, element> graph_back_up;
    multimap<int, element> graph_cresc;
    
    id_graph = chooseGraph(id_graph);
    cout << id_graph << endl;
    
    //if (loading_graph(id_graph)) {
    if (loading(id_graph, lesContraintes, leGraphe)) {
        
        cout << "\nLoading successed" << endl;
        
        print_graph_bool(lesContraintes, leGraphe);
        print_graph_adjacence(lesContraintes, leGraphe);
        
        
        graph = fill_graph(lesContraintes, graph, leGraphe);
        
        graph = modify_element(graph, lesContraintes, leGraphe, current, next);
        //display_graph_content(graph);
        //reading_graph(graph);
        
        rank_computation(graph, graph_back_up);
        set_graph_cresc(graph_back_up, graph_cresc);
        set_earliest_date(graph_cresc);
        display_earliest_dates(graph_cresc);
        free_memory(lesContraintes, leGraphe, graph, current, next);
        
        
        
    } else {
        cout << "\nLoading failed" << endl;
    }
    
    return 0;
}














