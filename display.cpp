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
        
        cout << "Task : " << current.name << " - Duration : " << current.duration << " Rank : " << current.rank;
        
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




