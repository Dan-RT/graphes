 //
//  dan_fonctions.cpp
//  Projet Graphes
//
//  Created by Daniel Regnard on 01/01/2017.
//  Copyright © 2017 A. All rights reserved.
//

#include "dan_fonctions.hpp"

void display_graph_map (map<char, element> graph_back_up);

vector<element> modify_element (vector<element> graph, tt_contraintes* lesContraintes, tt_graphe* leGraphe, element* current, element* next) {
    
    //cette fonction permet de modifier les elements du graphe, notamment en faisant pointer les next et previous de chaque element
    
    //element* current = nullptr;
    //element* next = nullptr;
    
    for (int ligne = 0; ligne <= leGraphe->nbSommets - 2; ligne++) {
        for (int colonne = 1; colonne <= leGraphe->nbSommets - 2; colonne++) {
            if (leGraphe->adj[colonne][ligne] == 1) {
                
                for(vector<element>::iterator it = graph.begin(); it != graph.end(); ++it) {
                    
                    if (lesContraintes->nomTaches[ligne] == it->name) {
                        //cout << "Lettre lue dans le graphe initial : " << lesContraintes->nomTaches[ligne] << endl;
                        //cout << "Lettre lue par le it : " << it->name << endl;
                        current = &*it;
                        
                        for(vector<element>::iterator it_2 = graph.begin(); it_2 != graph.end(); ++it_2) {
                            
                            if (lesContraintes->nomTaches[colonne] == it_2->name) {
                                
                                //cout << "Lettre lue dans le graphe initial : " << lesContraintes->nomTaches[colonne] << endl;
                                //cout << "Lettre lue par le it_2 : " << it_2->name << endl;
                                
                                next = &*it_2;
                                current->next.push_back(next);
                                next->previous.push_back(current);
                                
                            }
                        }
                    }
                }
            }
        }
    }
    cout << "test" << endl;
    display_graph_content(graph);
    //delete previous;
    //delete next;
    
    return graph;
    
}



vector<element> fill_graph (tt_contraintes* lesContraintes, vector<element> graph,  tt_graphe* leGraphe) {
    
    for (int i = 1; i <= lesContraintes->nbTaches; i++) {
        element new_element;
        new_element.name = lesContraintes->nomTaches[i];
        new_element.duration = lesContraintes->durees[i];
        new_element.rank = 0;
        graph.push_back(new_element);

        //create_element(lesContraintes->nomTaches[i], lesContraintes->durees[i], graph);
    }
    
    return graph;
}


void free_memory (tt_contraintes* lesContraintes, tt_graphe* leGraphe, vector<element> graph, element* current, element* next) {
    
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
    for(vector<element>::iterator it = graph.begin(); it != graph.end(); ++it) {
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


int scan_graph (vector<element> graph, element* current) {
    
    cout << current->name;
    
    for(vector<element*>::iterator it = current->next.begin(); it != current->next.end(); ++it) {
        scan_graph(graph, *it);
        cout << "." << endl;
    }
    
    return 0;
}


void reading_graph (vector<element> graph) {
    
    //determiner qui est le premier, le premier element est un élément sans previous
    element test;
    element* first = nullptr;
    
    for(vector<element>::iterator it = graph.begin(); it != graph.end(); ++it) {
        test = *it;
        if (test.previous.size() == 0) {
            first = &*it;
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

void set_rank (map<char, element> &graph_back_up, vector<element> graph, int rank) {
   
    for(vector<element>::iterator it = graph.begin(); it != graph.end(); ++it) {
        graph_back_up[it->name].rank = rank;
    }
    
}


void create_graph_map (vector<element> graph, map<char, element> &graph_back_up) {
    
    for(vector<element>::iterator it = graph.begin(); it != graph.end(); ++it) {
        graph_back_up[it->name] = *it;
    }
}



void rank_computation (vector<element> graph) {
    
    //vector<element> graph_back_up = graph;
    map<char, element> graph_back_up;
    create_graph_map(graph, graph_back_up);
    element* tmp = nullptr;
    int k = 1, flag = 0;
    vector<char> element_to_erase;  //certains éléments sont à effacer en même temps
    map<char, char> previous_to_erase;
    
    
   
    //les rangs sont déjà initialisés
    
    while (graph.size() > 0) {
        
        for(vector<element>::iterator it = graph.begin(); it != graph.end(); ++it) {
            //pour chaque element on regarde son nombre de previous
            if (flag) {
                it = graph.begin();
                //it--;
                flag = 0;
            }
            
            
            cout << "\nLettre testée : " << it->name << " - Size previous : " << it->previous.size() << endl;
            
            
            if (it->previous.size() == 0) {
                
                //s'il n'en a pas il faut regarder tous les éléments pour lequel il est un previous
                
                for(vector<element>::iterator it_1 = graph.begin(); it_1 != graph.end(); ++it_1) {
                    
                    for(vector<element*>::iterator it_2 = it_1->previous.begin(); it_2 != it_1->previous.end(); ++it_2) {
                        cout << it_1->name << endl;
                        tmp = *it_2;
                        if (tmp->name == it->name) {
                            previous_to_erase[it_1->name] = it->name;
                            //it_1->previous.erase(it_2);
                            cout << it->name << " ajouté à la suppresion des previous de " << it_1->name << endl;
                            break;
                        }
                    }
                }
                
                element_to_erase.push_back(it->name);
                cout << "Element " << it->name << " ajouté à la suppresion du graphe" << endl;
                
            
            }
        }
        cout << "Fin des lettres à tester." << endl;
        
        if (element_to_erase.size() > 0) {
            for(vector<char>::iterator it = element_to_erase.begin(); it != element_to_erase.end(); ++it) {
                //ici on supprime les elements, il peut y en avoir plusieurs en même temps
                for(vector<element>::iterator it_1 = graph.begin(); it_1 != graph.end(); ++it_1) {
                    if (it_1->name == *it) {
                        cout << "\n" << it_1->name << " supprimé du graphe." << endl;
                        graph.erase(it_1);
                        break;
                    }
                }
            }
            element_to_erase.clear();
            set_rank(graph_back_up, graph, k);
            flag = 1;
        }
        
        if (previous_to_erase.size() > 0) {
            for(vector<element>::iterator it = graph.begin(); it != graph.end(); ++it) {
                //on teste chaque element du graphe
                for(map<char,char>::iterator it_char = previous_to_erase.begin(); it_char != previous_to_erase.end(); ++it_char) {
                    //chaque element qu'on compare par rapport aux éléments ayant des previous à supprimer
                    if (it_char->first == it->name) {
                        for(vector<element*>::iterator it_2 = it->previous.begin(); it_2 != it->previous.end(); ++it_2) {
                            //on parcourt les previous jusqu'à trouver le bon previous à supprimer
                            element* tmp = *it_2;
                            if (tmp->name == it_char->second) {
                                cout << it_char->second << " supprimé des previous de " << it_char->first << endl;
                                //cout << tmp->name << " supprimé des previous de " << it->name << endl;
                                
                                it->previous.erase(it_2);
                                break;
                            }
                            tmp = nullptr;
                        }
                    }
                    
                }
            }
            previous_to_erase.clear();
        }
        
        if (graph.size() > 0) {
            cout << "\n\nGraph : " << endl;
            display_graph_content(graph);
            cout << "\n\nGraph back-up : " << endl;
            display_graph_map(graph_back_up);
            cout << "Fin tour n°" << k << endl;
        } else {
            break;
        }
        k++;
        
    }
    
    
    //delete tmp;
    tmp = nullptr;
    
}















