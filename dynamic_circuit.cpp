//
//  dynamic_circuit.cpp
//  Projet Graphes
//
//  Created by Daniel Regnard on 08/01/2017.
//  Copyright © 2017 A. All rights reserved.
//

#include "dynamic_circuit.hpp"


void fill_graph_dynamic (tt_contraintes* lesContraintes, vector<element*> &graph_dynamic) {
    
    for (int i = 1; i <= lesContraintes->nbTaches; i++) {
        element* new_element = new element;
        new_element->name = lesContraintes->nomTaches[i];
        new_element->duration = lesContraintes->durees[i];
        new_element->rank = 0;
        new_element->earliest_date = 0;
        new_element->latest_date = 0;
        new_element->sum_e_date_duration = 0;
        new_element->diff_l_date_duration = 0;
        new_element->sum_l_date_duration = 0;
        new_element->safe = false;
        graph_dynamic.push_back(new_element);
    }
    
}

void modify_element_dynamic (vector<element*> &graph_dynamic, tt_contraintes* lesContraintes, tt_graphe* leGraphe) {
    
    element* current = new element;
    element* next = new element;

    for (int ligne = 1; ligne <= leGraphe->nbSommets - 2; ligne++) {
        //cout << "\nLETTRE DE BASE : " << lesContraintes->nomTaches[ligne] << endl;
        
            for(vector<element*>::iterator it = graph_dynamic.begin(); it != graph_dynamic.end(); ++it) {
                
                current = *it;
                //cout << "Lettre testée : " << current->name << endl;
                
                if (lesContraintes->nomTaches[ligne] == current->name) {
                    
                    for (int colonne = 1; colonne <= leGraphe->nbSommets - 2; colonne++) {
                        //cout << "Lettre lue dans le graphe initial : " << lesContraintes->nomTaches[ligne] << endl;
                        //cout << "Lettre lue par le it : " << it->name << endl;
                        
                        
                        if (leGraphe->adj[colonne][ligne] == 1) {
                            for(vector<element*>::iterator it_2 = graph_dynamic.begin(); it_2 != graph_dynamic.end(); ++it_2) {
                                next = *it_2;
                                
                                
                                if (lesContraintes->nomTaches[colonne] == next->name) {
                                    
                                    //cout << current->name <<  " ne peut commencer que lorsque la tache " << next->name << " est terminee. " << endl;
                                    
                                    //cout << "Lettre lue dans le graphe initial : " << lesContraintes->nomTaches[colonne] << endl;
                                    //cout << "Lettre lue par le it_2 : " << it_2->name << endl;
                                    
                                    current->next.push_back(next);
                                    next->previous.push_back(current);
                                    
                                }
                            }

                        }
                        
                        
                    }
                }
                
            }
        
    }
    
    next = nullptr;
    current = nullptr;
    
    delete next;
    delete current;
    
    
}








void display_graph_dynamic_content (vector<element*> graph_dynamic) {
    
    element* current = new element;
    cout << endl;
    
    for(vector<element*>::iterator it = graph_dynamic.begin(); it != graph_dynamic.end(); ++it) {
        
        current = *it;
        
        cout << "Task : " << current->name << " - Duration : " << current->duration;
        
        cout << " - Next : ";
        
        for(vector<element*>::iterator it2 = current->next.begin(); it2 != current->next.end(); ++it2) {
            element next = **it2;
            cout << next.name << " ";
        }
        
        cout << " - Previous : ";
        
        for(vector<element*>::iterator it2 = current->previous.begin(); it2 != current->previous.end(); ++it2) {
            element previous = **it2;
            cout << previous.name << " ";
        }
        cout << endl;
    }
    
    current = nullptr;
    delete current;
}


























void free_dynamic_memory (vector<element*> &graph_dynamic) {
    
    /*for (int i = 0; i < graph_dynamic.size(); i++) {
        delete graph_dynamic[i];
    }*/
    
    for (std::vector<element*>::iterator it = graph_dynamic.begin() ; it != graph_dynamic.end(); ++it) {
        delete *it;
        //marche pas
    }
    graph_dynamic.clear();
}



