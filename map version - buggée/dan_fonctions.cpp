 //
//  dan_fonctions.cpp
//  Projet Graphes
//
//  Created by Daniel Regnard on 01/01/2017.
//  Copyright © 2017 A. All rights reserved.
//

#include "dan_fonctions.hpp"


map<char, element> modify_element (map<char, element> graph, tt_contraintes* lesContraintes, tt_graphe* leGraphe, element* current, element* next) {
    
    //cette fonction permet de modifier les elements du graphe, notamment en faisant pointer les next et previous de chaque element
    
    //element* current = nullptr;
    //element* next = nullptr;
    
    for (int ligne = 0; ligne <= leGraphe->nbSommets - 2; ligne++) {
        for (int colonne = 1; colonne <= leGraphe->nbSommets - 2; colonne++) {
            if (leGraphe->adj[colonne][ligne] == 1) {
                
                for(map<char, element>::iterator it = graph.begin(); it != graph.end(); ++it) {
                    
                    if (lesContraintes->nomTaches[ligne] == it->second.name) {
                        cout << "Lettre lue dans le graphe initial : " << lesContraintes->nomTaches[ligne] << endl;
                        cout << "Lettre lue par le it : " << it->second.name << endl;
                        current = &it->second;
                        
                        for(map<char, element>::iterator it_2 = graph.begin(); it_2 != graph.end(); ++it_2) {
                            
                            if (lesContraintes->nomTaches[colonne] == it_2->second.name) {
                                
                                cout << "Lettre lue dans le graphe initial : " << lesContraintes->nomTaches[colonne] << endl;
                                cout << "Lettre lue par le it_2 : " << it_2->second.name << endl;
                                
                                next = &it_2->second;
                                current->next.push_back(next);
                                next->previous.push_back(current);
                                
                            }
                        }
                    }
                }
            }
        }
    }
    cout << "\nGraph succefully modified" << endl;
    display_graph_content(graph);
    //delete previous;
    //delete next;
    
    return graph;
    
}



map<char, element> fill_graph (tt_contraintes* lesContraintes, map<char, element> graph,  tt_graphe* leGraphe) {
    
    for (int i = 1; i <= lesContraintes->nbTaches; i++) {
        element new_element;
        new_element.name = lesContraintes->nomTaches[i];
        new_element.duration = lesContraintes->durees[i];
        new_element.rank = 0;
        
        graph[new_element.name] = new_element;
        //graph.push_back(new_element);

        //create_element(lesContraintes->nomTaches[i], lesContraintes->durees[i], graph);
    }
    
    return graph;
}


void free_memory (tt_contraintes* lesContraintes, tt_graphe* leGraphe, map<char, element> graph, element* current, element* next) {
    
    delete lesContraintes->nomTaches;
    lesContraintes->nomTaches = NULL;
    delete lesContraintes->durees;
    lesContraintes->durees = NULL;
    delete lesContraintes;
    lesContraintes = NULL;
    
    for (int ligne = 1; ligne <= leGraphe->nbSommets; ligne++)
    {
        delete leGraphe->adj[ligne];
        leGraphe->adj[ligne] = NULL;
        delete leGraphe->val[ligne];
        leGraphe->val[ligne] = NULL;
        //où sont les colonnes?
    };
    
    delete leGraphe;
    leGraphe = NULL;
    
    
    /*
    for(map<char, element>::iterator it = graph.begin(); it != graph.end(); ++it) {
        current = &*it;
        for(vector<element*>::iterator it2 = current->next.begin(); it2 != current->next.end(); ++it2) {
            //aucune idée, à reprendre
        }
    }
     */
    
    //delete current;
    //delete next;

    
    cout << "\n\nMemory partially freed." <<endl;
}


int scan_graph (map<char, element> graph, element* current) {
    
    cout << current->name;
    
    for(vector<element*>::iterator it = current->next.begin(); it != current->next.end(); ++it) {
        scan_graph(graph, *it);
        cout << "." << endl;
    }
    
    return 0;
}


void reading_graph (map<char, element> graph) {
    
    //determiner qui est le premier, le premier element est un élément sans previous
    element test;
    element* first = nullptr;
    
    for(map<char, element>::iterator it = graph.begin(); it != graph.end(); ++it) {
        
        test = it->second;
        if (test.previous.size() == 0) {
            first = &it->second;
            break;
        }
    }
    if (first == nullptr) {
        cout << "No starting element." << endl;
        exit(0);
    }
    
    cout << "First element : " << first->name << endl;
    
    
    cout << "Liste of paths : " << endl;
    scan_graph(graph, first);
    
    //delete first;
    
}

void set_rank (map<char, element> &graph_back_up, bool initialization) {
    for(map<char, element>::iterator it = graph_back_up.begin(); it != graph_back_up.end(); ++it) {
        
        
    }
    
}

void rank_computation (map<char, element> graph) {
    
    map<char, element> graph_back_up = graph;
    element* tmp = nullptr;
   
    //les rangs sont déjà initialisés
    
    while (graph.size() > 0) {
        
        for(map<char, element>::iterator it = graph.begin(); it != graph.end(); ++it) {
            //pour chaque element on regarde son nombre de previous
            
            cout << "size : " << it->second.previous.size() << endl;
            if (it->second.previous.size() == 0) {
                
                cout << it->first << endl;
                
                //s'il n'en a pas il faut regarder tous les autres éléments next et supprimer le pointeur
                
                /*
                for(vector<element*>::iterator it_1 = it->second.next.begin(); it_1 != it->second.next.end(); ++it_1) {
                    tmp = *it_1;
                    
                    for(vector<element*>::iterator it_2 = tmp->previous.begin(); it_2 != tmp->previous.end(); ++it_2) {
                    
                        if (it_2 == it->first) {
                            
                        }
                    }
                    
                    if (tmp->name == it->first) {
                        
                    }
                 
                    //tmp = &graph[it->second.name];
                    
                    //*it_1.previous.erase(tmp);
                }
                */
                for(map<char, element>::iterator it_1 = graph.begin(); it_1 != graph.end(); ++it_1) {
                    
                    for(vector<element*>::iterator it_2 = it_1->second.previous.begin(); it_2 != it_1->second.previous.end(); ++it_2) {
                        
                        cout << it_1->second.name << endl;
                        tmp = *it_2;
                        if (tmp->name == it->second.name) {
                            it_1->second.previous.erase(it_2);
                            break;
                        }
                    }
                }
                
                graph.erase(it);
                //set_rank(graph_back_up, 0);
                cout << "\n\nGraph back-up : " << endl;
                display_graph_content(graph_back_up);
                
            }
            if (graph.size() > 0) {
                cout << "\n\nNew graph : " << endl;
                display_graph_content(graph);
            } else {
                break;
            }
            
            
        }
        
    }
    
    //delete tmp;
    tmp = nullptr;
    
}















