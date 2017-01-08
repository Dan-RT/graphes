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
        new_element.earliest_date = 0;
        new_element.latest_date = 0;
        new_element.sum_e_date_duration = 0;
        new_element.diff_l_date_duration = 0;
        new_element.sum_l_date_duration = 0;
        graph.push_back(new_element);
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
    };
    
    delete leGraphe;
    leGraphe = NULL;
    
    
    cout << "\n\nMemory freed." <<endl;
}


int scan_graph (vector<element> graph, element* current) {
    
    cout << current->name;
    current->flag = true;
    
    for(vector<element*>::iterator it = current->next.begin(); it != current->next.end(); ++it) {
        element* tmp =nullptr;
        tmp = *it;
        if (tmp->flag == true) {
            cout << "circuit?" << endl;
            tmp =nullptr;
            //exit(0);
            break;
        } else {
            tmp->flag = true;
            scan_graph(graph, *it);
            cout << "." << endl;
            tmp =nullptr;
        }
    }
    
    return 0;
}







/*      DETECTION DE CIRCUIT        */





void delete_circuit (vector<element> &graph, char depart, char destination) {
    
    int flag = 0;
    
    for(vector<element>::iterator it = graph.begin(); it != graph.end(); ++it) {
        if (depart == it->name) {
            for(vector<element*>::iterator it_1 = it->next.begin(); it_1 != it->next.end(); ++it_1) {
                
                element* tmp = *it_1;
                if (tmp != nullptr) {
                    if (tmp->name == destination) {
                        //cout << "\n" << endl;
                        cout << "Circuit détecté, suppression de l'élément " << tmp->name << " de la liste des next de " << it->name << endl;
                        it->next.erase(it_1);
                        flag++;
                        //display_graph_content(graph);
                        
                        /*
                         for(vector<element*>::iterator it_2 = tmp->previous.begin(); it_2 != tmp->previous.end(); ++it_2) {
                         
                         element* tmp_2 = *it_2;
                         
                         if (tmp_2->name == depart) {
                         cout << "\n" << endl;
                         cout << "Suppression de l'élément " << tmp_2->name << " de la liste des previous de " << tmp->name << endl;
                         tmp->previous.erase(it_2);
                         
                         
                         display_graph_content(graph);
                         flag = 1;
                         break;
                         }
                         tmp_2 = nullptr;
                         }*/
                    }

                } else {
                    break;
                }
                tmp = nullptr;
            }
            /*
            if (flag == 1) {
                break;
            }*/
        }
        if (destination == it->name) {
            for(vector<element*>::iterator it_1 = it->previous.begin(); it_1 != it->previous.end(); ++it_1) {
                
                element* tmp = *it_1;
                if (tmp != nullptr) {
                    if (tmp->name == depart) {
                        cout << "Circuit détecté, suppression de l'élément " << tmp->name << " de la liste des previous de " << it->name << endl;
                        it->previous.erase(it_1);
                        flag++;
                    }
                } else {
                    break;
                }
                
                tmp = nullptr;
            }
        }
        if (flag > 1) {
            break;
        }
    }
}






int set_flag_false (vector<element> &graph, element* current, int indice, bool from_circuit, int profondeur_max, int profondeur) {
    
    //le pramètre indice permet de savoir quel voisin checker, car on ne va pas risque de lire les next+1 si on ne sait pas s'il y a un circuit derrière le next+0
    
    //le paramètre from_circuit sert à savoir d'où on appelle la fonction set_flag_false, si c'est de la fonction de circuit ou par récurrence. Si c'est par récurrence on va alors vouloir parcourir pour le coup tous les next+1
    if (profondeur > profondeur_max) {
        return 0;
    }
    
    if (from_circuit) {
        //cout << current->name << endl;
        //cout << "\n" << endl;
        current->flag = false;
        //display_graph_content(graph);
        if (current->next.size() > 0) {
            if (!set_flag_false(graph, current->next[indice], 0, false, profondeur_max, profondeur)) {
                return 0;
            }
        } else {
            return 0;
        }
        
        
    } else {
        for (int i = 0; i < current->next.size(); i++) {
            //cout << current->name << endl;
            //cout << "\n" << endl;
            //display_graph_content(graph);
            
            current->flag = false;
            profondeur++;
            if (!set_flag_false(graph, current->next[i], 0, false, profondeur_max, profondeur)) {
                return 0;
            }
            
            
        }
    }
    return 0;
}

/*
int circuit (vector<element> &graph, element* first, element* current, element* previous) {
    
    cout << current->name << endl;
    int flag = 0;
    
    for (int i = 0; i < current->next.size(); i++) {
        
        if (i != 0) {
            if (current->next.size() > 0) {
                set_flag_false(graph, current->next[i], i-1, true, flag, 0);
            }
            current->flag = false;
            cout << current->name << endl;
        }
        
        if (current->flag == true && i == 0) {
            cout << current->name << endl;
            
            cout << "Circuit détecté. " << endl;
            delete_circuit(graph, previous->name, current->name);
            
        } else {
            current->flag = true;
            //On met un flag pour signaler qu'on est passé ici sur cet élément déjà
            
            circuit(graph, first, current->next[i], current);
            cout << "." << endl;
        }
        set_flag_false(graph, current->next[i]);
    }
    
    return 0;
}
*/


int circuit (vector<element> &graph, element* first, element* current, element* previous, bool surface) {
    
    cout << current->name << endl;
    int flag = 0;
    
    for (int i = 0; i < current->next.size(); i++) {
        
        if (i != 0) {
            if (current->next.size() > 0) {
                set_flag_false(graph, current->next[i], i-1, true, flag, 0);
            }
            current->flag = false;
            cout << current->name << endl;
        }
        
        if (current->flag == true) {
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
            current->flag = true;
            //On met un flag pour signaler qu'on est déjà passé sur cet élément
            
            int check = circuit(graph, first, current->next[i], current, false);
            
            //dès qu'on trouve un circuit on sort de la recherche
            //vérifier ce que renvoie la fonction circuit permet de savoir si on doit supprimer l'arc ou non, si on fait pas gaffe et supprime tous les axes testés par réccurence
            if (check > 1) {
                
                flag = 1;
                delete_circuit(graph, previous->name, current->name);
                //delete_circuit(graph, current->name, current->previous[i]->name);
                cout << "\n" << endl;
                //display_graph_content(graph);
                set_flag_false(graph, current, i, true, flag, 0);
                
                /*
                 if (surface == true && i == 0) {
                 check = 0;
                 flag = 0;
                 break;
                 }*/
                
            } else if (check == 1)  {
                flag = 1;
                
                break;
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

void reading_graph (vector<element> &graph) {
    
    //determiner qui est le premier, le premier element est un élément sans previous

    element* first;
    
    for(vector<element>::iterator it = graph.begin(); it != graph.end(); ++it) {
        first = &*it;
        if (first->name == 'J') {
            cout << "debug" << endl;
        }
        cout << "Element de départ testés : " << first->name << endl;
        
        circuit(graph, first, first, first, true);
        /*
        if (first->previous.size() == 0) {
            cout << "\n\nFirst element : " << first->name << endl;
            cout << "\nPath : " << endl;
            circuit(graph, first, first, first);
        }
        if (it == graph.begin()) {
            circuit(graph, first, first, first);
        }*/
    }
    
    
    
    first = NULL;
    
    
    
    //scan_graph(graph, first);
    
    //delete first;
    
}





/*      FIN DETECTION DE CIRCUIT        */







void create_graph_map (vector<element> graph, map<char, element> &graph_back_up) {
    
    for(vector<element>::iterator it = graph.begin(); it != graph.end(); ++it) {
        graph_back_up[it->name] = *it;
    }
}


void set_rank (map<char, element> &graph_back_up, vector<element> graph, int rank) {
    
    for(vector<element>::iterator it = graph.begin(); it != graph.end(); ++it) {
        graph_back_up[it->name].rank = rank;
    }
    
}

void rank_computation (vector<element> graph, map<char, element> &graph_back_up) {
    
    //vector<element> graph_back_up = graph;
    
    create_graph_map(graph, graph_back_up);
    element* tmp = nullptr;
    int k = 1, flag = 0;
    vector<char> element_to_erase;  //certains éléments sont à effacer en même temps
    multimap<char, char> previous_to_erase;
    
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
                            
                            previous_to_erase.insert(pair<char, char>(it_1->name,it->name));
                            //previous_to_erase[it_1->name] = it->name;
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





void set_graph_cresc (map<char, element> graph_back_up, multimap<int, element> &graph_cresc) {
    
    for(map<char,element>::iterator it = graph_back_up.begin(); it != graph_back_up.end(); ++it) {
        graph_cresc.insert(pair<int,element>(it->second.rank,it->second));
        //la création d'un élément map ou multimap ici (besoin d'autoriser des doublons au niveau des clés) met tout seul en ordre de croissant les éléments
    }
}

void modify_element_graph_resc (multimap<int, element> &graph_cresc, char letter, int sum, int rank, int earliest_date) {
    
    //cette fonction parcours les previous pour le tableau d'element classé par rang, comme on est pas dynamique sur les éléments il faut qu'on aille sur chaque previous modifier tout ça
    
    element* current = nullptr;
    
    for(multimap<int,element>::iterator it = graph_cresc.begin(); it != graph_cresc.end(); ++it) {
        //on parcourt chaque élément du graphe
        
        for(vector<element*>::iterator it_1 = it->second.previous.begin(); it_1 != it->second.previous.end(); ++it_1) {
            //puis chaque previous
            current = *it_1;
            if (current->name == letter) {
                //on regarde s'il a pour previous un element du même nom que la lettre testée, si oui, on set la sum_e_date_duration avec value
                current->sum_e_date_duration = sum;
                current->rank = rank;
                current->earliest_date = earliest_date;
                
            }
            current = nullptr;
        }
    }
}


void modify_element_graph_resc (multimap<int, element> &graph_cresc, int early_date, char letter, int date_limit, int sum) {
    
    //surcharge de la fonction d'avant
    
    element* current = nullptr;
    
    for(multimap<int,element>::iterator it = graph_cresc.begin(); it != graph_cresc.end(); ++it) {
        //on parcourt chaque élément du graphe
        
        for(vector<element*>::iterator it_1 = it->second.next.begin(); it_1 != it->second.next.end(); ++it_1) {
            
            if (it->second.name=='7') {
                //cout << "test" << endl;
            }
                
            //puis chaque next
            current = *it_1;
            if (current->name == letter) {
                //on regarde s'il a pour previous un element du même nom que la lettre testée, si oui, on set la sum_e_date_duration avec value
                current->earliest_date = early_date;
                current->latest_date = date_limit;
                current->sum_l_date_duration = sum;
            }
            current = nullptr;
        }
    }
}


void set_earliest_date (multimap<int, element> &graph_cresc) {
    
    vector<int> tmp;
    element* current = nullptr;
    
    for(multimap<int,element>::iterator it = graph_cresc.begin(); it != graph_cresc.end(); ++it) {
        
        //if (it == graph_cresc.begin()) {
        if (it->second.rank == 0) {
            it->second.earliest_date = 0;
            
            it->second.sum_e_date_duration = it->second.earliest_date+it->second.duration;
            modify_element_graph_resc(graph_cresc, it->second.name, it->second.sum_e_date_duration, it->second.rank, it->second.earliest_date);
            
        } else {
            
            for(vector<element*>::iterator it_1 = it->second.previous.begin(); it_1 != it->second.previous.end(); ++it_1) {
                current = *it_1;
                tmp.push_back(current->sum_e_date_duration);
            }
            sort(tmp.begin(), tmp.end());
            
            for (int i = 0; i < tmp.size(); i++) {
                it->second.earliest_date = tmp[i];
            }
            it->second.sum_e_date_duration = it->second.earliest_date+it->second.duration;
            modify_element_graph_resc(graph_cresc, it->second.name, it->second.sum_e_date_duration, it->second.rank, it->second.earliest_date);
        }
        tmp.clear();
    }
}

void set_latest_date (multimap<int, element> &graph_cresc) {
    
    vector<int> tmp;
    element* current = nullptr;
    int difference = 0;
    
    for(multimap<int,element>::iterator it = graph_cresc.end(); it != graph_cresc.begin(); --it) {
        //on parcourt tout les éléments de la fin vers le début
        
        
        
        if (it != graph_cresc.end()) {
            //pour éviter un bad access, faut pas aller trop loin
            
            if (it->second.name == '1') {
                //cout << "test" << endl;
            }
            
            for(vector<element*>::iterator it_1 = it->second.next.begin(); it_1 != it->second.next.end(); ++it_1) {
                //on regarde les next de l'élément
                current = *it_1;
                difference = current->earliest_date - it->second.duration;
                tmp.push_back(difference);
                current = nullptr;
            }
            sort(tmp.begin(), tmp.end());
            
            if (tmp.size() > 0) {
                it->second.latest_date = tmp[0];
            } else {
                it->second.latest_date = it->second.earliest_date;
            }
            
            it->second.sum_l_date_duration = it->second.latest_date + it->second.duration;
            
            modify_element_graph_resc(graph_cresc, it->second.earliest_date, it->second.name, it->second.latest_date, it->second.sum_l_date_duration);
        }
    }
}











