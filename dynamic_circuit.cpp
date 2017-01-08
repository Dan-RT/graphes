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

    //for (int ligne = 1; ligne <= leGraphe->nbSommets - 2; ligne++) {
        //cout << "\nLETTRE DE BASE : " << lesContraintes->nomTaches[ligne] << endl;
    for (int colonne = 1; colonne <= leGraphe->nbSommets - 2; colonne++) {
        for(vector<element*>::iterator it = graph_dynamic.begin(); it != graph_dynamic.end(); ++it) {
            
            current = *it;
            //cout << "Lettre testée : " << current->name << endl;
            
            if (lesContraintes->nomTaches[colonne] == current->name) {
                
                //for (int colonne = 1; colonne <= leGraphe->nbSommets - 2; colonne++) {
                for (int ligne = 1; ligne <= leGraphe->nbSommets - 2; ligne++) {
                    if (leGraphe->adj[colonne][ligne] == 1) {
                        
                        for(vector<element*>::iterator it_2 = graph_dynamic.begin(); it_2 != graph_dynamic.end(); ++it_2) {
                            next = *it_2;
                            
                            if (lesContraintes->nomTaches[ligne] == next->name) {
                                
                                if (current->name == 'J') {
                                    cout << "test" << endl;
                                }
                                
                                cout << "\n" << current->name <<  " ne peut commencer que lorsque la tache " << next->name << " est terminee. " << endl;
                                
                                current->next.push_back(next);
                                next->previous.push_back(current);
                                display_graph_dynamic_content(graph_dynamic);
                                if (reading_graph_dynamic(graph_dynamic) == 1) {
                                    delete_circuit_dynamic(graph_dynamic, next->name, current->name);
                                }
                            
                                
                                display_graph_dynamic_content(graph_dynamic);
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




void delete_circuit_dynamic (vector<element*> &graph_dynamic, char depart, char destination) {
    
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
        
        //on regarde pour chaque next de l'élément testé
        
        if (current->flag == true) {
            
            //si on est déjà passé par cette lettre il y a un circuit
            
            cout << current->name << endl;
            
            cout << "Circuit détecté. " << endl;
            
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
                //delete_circuit(graph_dynamic, previous->name, current->name);
                return 1;
                
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




int reading_graph_dynamic (vector<element*> &graph_dynamic) {
    
    //determiner qui est le premier, le premier element est un élément sans previous
    
    element* first;
    
    for(vector<element*>::iterator it = graph_dynamic.begin(); it != graph_dynamic.end(); ++it) {
        first = *it;
        
        cout << "Element de départ testés : " << first->name << endl;
        
        if (circuit(graph_dynamic, first, first, first, true) == 1) {
            first = nullptr;
            delete first;
            return 1;
        }
        
    }
    
    first = nullptr;
    delete first;
    
    return 0;
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



void create_graph_dynamic_map (vector<element*> graph_dynamic, map<char, element*> &graph_dynamic_back_up) {
    
    element* tmp;
    for(vector<element*>::iterator it = graph_dynamic.begin(); it != graph_dynamic.end(); ++it) {
        tmp = *it;
        
        graph_dynamic_back_up[tmp->name] = tmp;
    }
    tmp = nullptr;
    delete tmp;
    
}

void set_rank_dynamic (map<char, element*> &graph_dynamic_back_up, vector<element*> graph_dynamic, int rank) {
    
    element* tmp = nullptr;
    for(vector<element*>::iterator it = graph_dynamic.begin(); it != graph_dynamic.end(); ++it) {
        tmp = *it;
        graph_dynamic_back_up[tmp->name]->rank = rank;
    }
    tmp = nullptr;
    delete tmp;
    
}

void rank_computation_dynamic (vector<element*> &graph_dynamic, map<char, element*> &graph_dynamic_back_up) {

    create_graph_dynamic_map(graph_dynamic, graph_dynamic_back_up);
    
    element* tmp = nullptr;
    element* it_element = nullptr;
    element* it_element_1 = nullptr;
    
    vector<char> element_to_erase;  //certains éléments sont à effacer en même temps
    
    int flag = 0, k = 1;
    
    while (graph_dynamic.size() > 0) {
        
        for(vector<element*>::iterator it = graph_dynamic.begin(); it != graph_dynamic.end(); ++it) {
            
            it_element = *it;
            
            
            if (flag) {
                it = graph_dynamic.begin();
                flag = 0;
            }
            
            cout << "\nLettre testée : " << it_element->name << " - Size previous : " << it_element->previous.size() << endl;
            
            //pour chaque element on regarde son nombre de previous
            if (it_element->previous.size() == 0) {
                
                //s'il n'en a pas il faut regarder tous les éléments pour lequel il est un previous
                
                element_to_erase.push_back(it_element->name);
                cout << it_element->name << " ajouté à supprimer." << endl;
                //graph_dynamic.erase(it);
            
                
                
                /*
                for(vector<element*>::iterator it_1 = graph_dynamic.begin(); it_1 != graph_dynamic.end(); ++it_1) {
                    
                    it_element_1 = *it_1;
                    
                    for(vector<element*>::iterator it_2 = it_element_1->previous.begin(); it_2 != it_element_1->previous.end(); ++it_2) {
                        cout << it_element_1->name << endl;
                        
                        tmp = *it_2;
                        
                        if (tmp->name == it_element->name) {
                        
                            cout << it_element->name << " ajouté à la suppresion des previous de " << it_element_1->name << endl;
                            //break;
                        }
                    }
                }
                
                cout << "Element " << it_element->name << " ajouté à la suppresion du graphe" << endl;
                */
            }
        }
        if (element_to_erase.size() > 0) {
            for (int i = 0; i < element_to_erase.size(); i++) {
                
                //for(vector<element*>::iterator it_1 = graph_dynamic.begin(); it_1 != graph_dynamic.end(); ++it_1) {
                for (int j = 0; j < graph_dynamic.size(); j++) {
                    
                    //it_element_1 = *it_1;
                    //if (it_element_1->name == element_to_erase[i]) {
                    if (graph_dynamic[j]->name == element_to_erase[i]) {
                        
                        delete graph_dynamic[j];
                        //graph_dynamic.erase(it_1);
                        //cout << it_element_1->name << " supprimé." << endl;
                        flag = 1;
                        break;
                    }
                }
            }
            set_rank_dynamic(graph_dynamic_back_up, graph_dynamic, k);
            
            if (graph_dynamic.size() > 0) {
                cout << "\n\nGraph : " << endl;
                display_graph_dynamic_content(graph_dynamic);
                cout << "\n\nGraph back-up : " << endl;
                display_graph_dynamic_map(graph_dynamic_back_up);
                cout << "Fin tour n°" << k << endl;
            } else {
                break;
            }
            k++;
            
        }
    }
    
    free_dynamic_memory(graph_dynamic);

    tmp = nullptr;
    it_element = nullptr;
    it_element_1 = nullptr;
    delete tmp;
    delete it_element;
    delete it_element_1;
    
}




void display_graph_dynamic_map (map<char, element*> graph_dynamic_back_up) {
    
    for(map<char,element*>::iterator it = graph_dynamic_back_up.begin(); it != graph_dynamic_back_up.end(); ++it) {
        
        cout << "Key : " << it->first << " Name : " << it->second->name << " - Duration : " << it->second->duration << " - Rank : " << it->second->rank;
        
        cout << " - Next : ";
        
        for(vector<element*>::iterator it2 = it->second->next.begin(); it2 != it->second->next.end(); ++it2) {
            element next = **it2;
            cout << next.name << " ";
        }
        
        cout << " - Previous : ";
        
        for(vector<element*>::iterator it2 = it->second->previous.begin(); it2 != it->second->previous.end(); ++it2) {
            element previous = **it2;
            cout << previous.name << " ";
        }
        
        cout << endl;
    }
}































































