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
#include "dynamic_circuit.hpp"

void display_earliest_dates (multimap<int, element> &graph_cresc);

string chooseGraph(string number);



int main(int argc, const char * argv[]) {
   
    string id_graph = "";
    
    cout << "ENTER THE NAME OF YOUR GRAPH : " << endl;
    cin >> id_graph;
    
    tt_contraintes* lesContraintes = new tt_contraintes;
    tt_graphe* leGraphe =  new tt_graphe;
    element* current = nullptr;
    element* next = nullptr;
    
    
    
    
    vector<element> graph;
    map<char, element> graph_back_up;
    multimap<int, element> graph_cresc;
    vector<element*> graph_dynamic;
    
    id_graph = chooseGraph(id_graph);
    cout << id_graph << endl;
    
    if (loading(id_graph, lesContraintes, leGraphe)) {
        
        cout << "Loading successed\n" << endl;
        
        print_graph_bool(lesContraintes, leGraphe);
        print_graph_adjacence(lesContraintes, leGraphe);
        
        
        graph = fill_graph(lesContraintes, graph, leGraphe);
        
        graph = modify_element(graph, lesContraintes, leGraphe, current, next);
        
        fill_graph_dynamic(lesContraintes, graph_dynamic);
        modify_element_dynamic(graph_dynamic, lesContraintes, leGraphe);
        display_graph_dynamic_content(graph_dynamic);
        free_dynamic_memory(graph_dynamic);
        
        //reading_graph(graph);
        
        cout << "\n\n-----------------CALCUL DES RANGS-----------------" << endl;
        rank_computation(graph, graph_back_up);
        set_graph_cresc(graph_back_up, graph_cresc);
        cout << "\n\n-----------------FIN DU CALCUL DES RANGS-----------------\n\n\n" << endl;
        
        
        
        set_earliest_date(graph_cresc);
        display_graph_cresc(graph_cresc);
        display_earliest_dates(graph_cresc);
        
        set_latest_date(graph_cresc);
        display_latest_dates(graph_cresc);
        
        
        free_memory(lesContraintes, leGraphe, graph, current, next);
        
        
        
    } else {
        cout << "\nLoading failed" << endl;
    }
    
    return 0;
}













