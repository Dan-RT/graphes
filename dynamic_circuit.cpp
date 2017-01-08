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








void delete_circuit (vector<element*> &graph_dynamic, char depart, char destination) {
    
    int flag = 0;
    
    for(vector<element*>::iterator it = graph_dynamic.begin(); it != graph_dynamic.end(); ++it) {
        
        element* it_element = *it;
        
        if (depart == it_element->name) {
            for(vector<element*>::iterator it_1 = it_element->next.begin(); it_1 != it_element->next.end(); ++it_1) {
                
                element* tmp = *it_1;
                if (tmp != nullptr) {
                    if (tmp->name == destination) {
                        //cout << "\n" << endl;
                        cout << "Circuit détecté, suppression de l'élément " << tmp->name << " de la liste des next de " << it_element->name << endl;
                        it_element->next.erase(it_1);
                        flag++;
                    }
                    
                } else {
                    break;
                }
                tmp = nullptr;
                delete tmp;
            }
        }
        if (destination == it_element->name) {
            for(vector<element*>::iterator it_1 = it_element->previous.begin(); it_1 != it_element->previous.end(); ++it_1) {
                
                element* tmp = *it_1;
                if (tmp != nullptr) {
                    if (tmp->name == depart) {
                        cout << "Circuit détecté, suppression de l'élément " << tmp->name << " de la liste des previous de " << it_element->name << endl;
                        it_element->previous.erase(it_1);
                        flag++;
                    }
                } else {
                    break;
                }
                
                tmp = nullptr;
                delete tmp;
            }
        }
        if (flag > 1) {
            break;
        }
        
        it_element = nullptr;
        delete it_element;
        
    }
}







int circuit (vector<element*> &graph_dynamic, element* first, element* current, element* previous, bool surface) {
    
    cout << current->name << endl;
    int flag = 0;
    
    for (int i = 0; i < current->next.size(); i++) {
        
        
        if (current->flag == true) {
            
            //si on est déjà passé par cette lettre il y a un circuit
            
            cout << current->name << endl;
            
            cout << "Circuit détecté. " << endl;
            /*
             if (surface) {
             delete_circuit(graph, previous->name, current->name);
             //set_flag_false(graph, current->next[i], i-1, true, flag, 0);
             }*/
            flag = 2;
            break;
            
            
            
        } else {
            
            //Si y'a pas de circuit
            
            current->flag = true;
            //On met un flag pour signaler qu'on est déjà passé sur cet élément
            
            int check = circuit(graph_dynamic, first, current->next[i], current, false);
            
            //dès qu'on trouve un circuit on sort de la recherche
            //vérifier ce que renvoie la fonction circuit permet de savoir si on doit supprimer l'arc ou non, si on fait pas gaffe et supprime tous les axes testés par réccurence
            
            if (check > 1) {
                
                flag = 1;
                delete_circuit(graph_dynamic, previous->name, current->name);
                //delete_circuit(graph, current->name, current->previous[i]->name);
                cout << "\n" << endl;
                //display_graph_content(graph);
                //set_flag_false(graph, current, i, true, flag, 0);
                
                /*
                 if (surface == true && i == 0) {
                 check = 0;
                 flag = 0;
                 break;
                 }*/
                
            } else if (check == 1)  {
                flag = 1;
                
                break;
            } else if (check == 0) {
                
                current->flag = 0;
            }
            
            cout << "." << endl;
            
            
        }
    }
    
    if (flag > 1) {
        return flag;
    } else if (flag == 1) {
        return 1;
    } else {
        return 0;
    }
    
}




void reading_graph_dynamic (vector<element*> &graph_dynamic) {
    
    //determiner qui est le premier, le premier element est un élément sans previous
    
    element* first;
    
    for(vector<element*>::iterator it = graph_dynamic.begin(); it != graph_dynamic.end(); ++it) {
        first = *it;
        
        cout << "Element de départ testés : " << first->name << endl;
        
        circuit(graph_dynamic, first, first, first, true);
        
    }
    
    
    
    first = nullptr;
    delete first;
}



void copy_dynamic_to_static (vector<element*> &graph_dynamic, vector<element> &graph) {
    
    
    for (int i = 0; i < graph_dynamic.size() && i < graph.size(); i++) {
        
        cout << graph_dynamic[i]->name << " " << graph[i].name << endl;
        
        if (graph_dynamic[i]->name == graph[i].name) {
            graph[i].duration = graph_dynamic[i]->duration;
            graph[i].rank = graph_dynamic[i]->rank;
            graph[i].earliest_date = graph_dynamic[i]->earliest_date;
            graph[i].sum_e_date_duration = graph_dynamic[i]->sum_e_date_duration;
            graph[i].latest_date = graph_dynamic[i]->latest_date;
            graph[i].diff_l_date_duration = graph_dynamic[i]->diff_l_date_duration;
            graph[i].sum_l_date_duration = graph_dynamic[i]->sum_l_date_duration;
            
            if (graph_dynamic[i]->next.size() > 0) {
                for (int j = 0; j < graph_dynamic[i]->next.size(); j++) {
                    element* new_element = new element;
                    new_element->name = graph_dynamic[i]->next[j]->name;
                    new_element->duration = graph_dynamic[i]->next[j]->duration;
                    new_element->rank = graph_dynamic[i]->next[j]->rank;
                    new_element->earliest_date = graph_dynamic[i]->next[j]->earliest_date;
                    new_element->latest_date = graph_dynamic[i]->next[j]->latest_date;
                    new_element->sum_e_date_duration = graph_dynamic[i]->next[j]->sum_e_date_duration;
                    new_element->diff_l_date_duration = graph_dynamic[i]->next[j]->diff_l_date_duration;
                    new_element->sum_l_date_duration = graph_dynamic[i]->next[j]->sum_l_date_duration;
                    graph[i].next.push_back(new_element);
                }
            }
            
            if (graph_dynamic[i]->previous.size() > 0) {
                for (int j = 0; j < graph_dynamic[i]->previous.size(); j++) {
                    element* new_element = new element;
                    new_element->name = graph_dynamic[i]->previous[j]->name;
                    new_element->duration = graph_dynamic[i]->previous[j]->duration;
                    new_element->rank = graph_dynamic[i]->previous[j]->rank;
                    new_element->earliest_date = graph_dynamic[i]->previous[j]->earliest_date;
                    new_element->latest_date = graph_dynamic[i]->previous[j]->latest_date;
                    new_element->sum_e_date_duration = graph_dynamic[i]->previous[j]->sum_e_date_duration;
                    new_element->diff_l_date_duration = graph_dynamic[i]->previous[j]->diff_l_date_duration;
                    new_element->sum_l_date_duration = graph_dynamic[i]->previous[j]->sum_l_date_duration;
                    graph[i].previous.push_back(new_element);
                }
            }
            
        }
        
    }
    
    
    
    
}

























