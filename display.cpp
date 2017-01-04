//
//  display.cpp
//  Projet Graphes
//
//  Created by Daniel Regnard on 12/12/2016.
//  Copyright © 2016 A. All rights reserved.
//

#include "display.hpp"
#include "dan_fonctions.hpp"


void print_graph_bool (tt_contraintes* lesContraintes, tt_graphe* leGraphe) {
    cout << "Graphe genere" << endl;
    
    for (int ligne = 0; ligne <= leGraphe->nbSommets - 2; ligne++)
    {
        cout << lesContraintes->nomTaches[ligne] << " ";
        //cout << ligne << " ";
        for (int colonne = 1; colonne <=leGraphe->nbSommets-2; colonne++)
        {
            if (ligne == 0) {
                if (colonne == 1) {
                    cout << " ";
                }
                cout << lesContraintes->nomTaches[colonne] << " ";
                //cout << colonne << " ";
            } else {
                if (leGraphe->adj[colonne][ligne])
                {
                    cout << 1 << " ";
                }
                else
                {
                    cout << 0 << " ";
                };
            }
            
        };
        cout <<endl;
    };
}


void print_graph_adjacence (tt_contraintes* lesContraintes, tt_graphe* leGraphe) {
    cout << "\n\nGraphe duree" <<endl;
    for (int ligne = 0; ligne <= leGraphe->nbSommets - 2; ligne++)
    {
        cout << lesContraintes->nomTaches[ligne] << " ";
        //cout << ligne << " ";
        for (int colonne = 1; colonne <=leGraphe->nbSommets-2; colonne++)
        {
            if (ligne == 0) {
                if (colonne == 1) {
                    cout << " ";
                }
                cout << lesContraintes->nomTaches[colonne] << " ";
                //cout << colonne << " ";
            } else {
                if (leGraphe->adj[colonne][ligne]) {
                    cout << leGraphe->val[colonne][ligne] << " ";
                }
                else {
                    cout << "  ";
                };
            }
            
        };
        cout << endl ;
    };
    cout << endl << endl ;
}




void display_graph_content (vector<element> graph) {
    
    for(vector<element>::iterator it = graph.begin(); it != graph.end(); ++it) {
        
        element current = *it;
        
        cout << "Task : " << current.name << " - Duration : " << current.duration;
        
        cout << " - Next : ";
        
        for(vector<element*>::iterator it2 = current.next.begin(); it2 != current.next.end(); ++it2) {
            element next = **it2;
            cout << next.name << " ";
        }
        
        cout << " - Previous : ";
        
        for(vector<element*>::iterator it2 = current.previous.begin(); it2 != current.previous.end(); ++it2) {
            element previous = **it2;
            cout << previous.name << " ";
        }
        cout << endl;
        
    }
}



void display_graph_map (map<char, element> graph_back_up) {
    
    for(map<char,element>::iterator it = graph_back_up.begin(); it != graph_back_up.end(); ++it) {
        cout << "Key : " << it->first << " Name : " << it->second.name << " - Duration : " << it->second.duration << " - Rank : " << it->second.rank;
        
        
        
        cout << " - Next : ";
        
        for(vector<element*>::iterator it2 = it->second.next.begin(); it2 != it->second.next.end(); ++it2) {
            element next = **it2;
            cout << next.name << " ";
        }
        
        cout << " - Previous : ";
        
        for(vector<element*>::iterator it2 = it->second.previous.begin(); it2 != it->second.previous.end(); ++it2) {
            element previous = **it2;
            cout << previous.name << " ";
        }
        
        cout << endl;
    }
    
    
}


void display_graph_cresc (multimap<int, element> &graph_cresc) {

    for(multimap<int,element>::iterator it = graph_cresc.begin(); it != graph_cresc.end(); ++it) {
        cout << "Key : " << it->first << " Name : " << it->second.name << " - Duration : " << it->second.duration << " - Rank : " << it->second.rank;
        
        
        
        cout << " - Next : ";
        
        for(vector<element*>::iterator it2 = it->second.next.begin(); it2 != it->second.next.end(); ++it2) {
            element next = **it2;
            cout << next.name << " ";
        }
        
        cout << " - Previous : ";
        
        for(vector<element*>::iterator it2 = it->second.previous.begin(); it2 != it->second.previous.end(); ++it2) {
            element previous = **it2;
            cout << previous.name << " ";
        }
        
        cout << endl;
    }

}

void display_earliest_dates (multimap<int, element> &graph_cresc) {
    
    int cpt = 0;
    
    cout << endl << endl << "Dates au plus tôt : " << endl << endl;
    
    for(multimap<int,element>::iterator it = graph_cresc.begin(); it != graph_cresc.end(); ++it) {
        
        if (it == graph_cresc.begin()) {
            while (it != graph_cresc.end()) {
                if (it->second.sum_e_date_duration > cpt) {
                    cpt = it->second.sum_e_date_duration;
                }
                it++;
            }
            //it = graph_cresc.end();
            //it--;
            cout << " ";
            for (int i = 1; i < cpt; i++) {
                if (i < 10) {
                    cout << "  " << i << "  ";
                } else {
                    cout << " " << i << "  ";
                }
                
            }
            cout << endl;
            it = graph_cresc.begin();
        }
        
        cout << it->second.name;
        for (int i = 1; i < cpt; i++) {
            
            if (i >= it->second.earliest_date && i < it->second.earliest_date+it->second.duration) {
                cout << "|===|";
            } else {
                cout << "|   |";
            }
        }
        cout << endl;
    }
}


void display_latest_dates (multimap<int, element> &graph_cresc) {
    
    int cpt = 0;
    
    cout << endl << endl << "Dates au plus tard : " << endl << endl;
    
    for(multimap<int,element>::iterator it = graph_cresc.begin(); it != graph_cresc.end(); ++it) {
        
        if (it == graph_cresc.begin()) {
            while (it != graph_cresc.end()) {
                if (it->second.sum_l_date_duration > cpt) {
                    cpt = it->second.sum_l_date_duration;
                }
                it++;
            }
            cout << " ";
            for (int i = 1; i < cpt; i++) {
                if (i < 10) {
                    cout << "  " << i << "  ";
                } else {
                    cout << " " << i << "  ";
                }
                
            }
            cout << endl;
            it = graph_cresc.begin();
        }
        
        cout << it->second.name;
        for (int i = 0; i < cpt; i++) {
            
            if (i >= it->second.latest_date && i < it->second.sum_l_date_duration) {
                cout << "|===|";
            } else {
                cout << "|   |";
            }
        }
        cout << endl;
    }
}




