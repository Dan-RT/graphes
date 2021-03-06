#include <iostream>
#include <fstream>
#include "course_fonctions.hpp"

using namespace std;

void ajouterContrainte(tt_contraintes* lesContraintes, char tacheCourante, char contrainteCourante, int cpt) {
    
    lesContraintes->contraintes[tacheCourante].push_back(contrainteCourante);
    
}

void afficher_contrainte (tt_contraintes* lesContraintes, char name_contrainte) {
    
    for(vector<char>::iterator it= lesContraintes->contraintes[name_contrainte].begin(); it!=lesContraintes->contraintes[name_contrainte].end(); ++it) {
        
        cout << name_contrainte << " ne peut commencer que lorsque la tache " << *it << " est terminee" << endl;
    }
    
}


int fill_graph (tt_contraintes* lesContraintes, int ligne, int colonne, bool choice) {
    
    /*
     Fonction pour remplir le tableau
     
     Dans nos structures de données les tâches sont identifiées par leur indice dans le
     tableau (à partir de 1 et non 0. On a rempli "lesContraintes.contraintes" dans le 
     ordre donc théoriquement il n'y a pas de soucis à utiliser les données avec ces 
     indices
     
     Ligne représente la tâche étudiée, colonne la tâche potentiellement contraignante
    
     */
    
    char tache_etudiee = lesContraintes->nomTaches[ligne];
    //cout << "Tache etudiee : " << tache_etudiee << endl;
    
    if (lesContraintes->contraintes[tache_etudiee].size() == 0) {
        return -2;
    } else {
        
        char nom_tache_contraignante = lesContraintes->nomTaches[colonne];
        //cout << "Tache contraignante : " << nom_tache_contraignante << endl;
        
        for(vector<char>::iterator it= lesContraintes->contraintes[tache_etudiee].begin(); it!=lesContraintes->contraintes[tache_etudiee].end(); ++it) {
            
            //cout << "Tache lue : " << *it << endl;
            
            if (nom_tache_contraignante == *it) {
                //cout << "Tache reconnue comme identique" << endl << endl;
                //comme les taches sont effectivement liees, l'une commençant seulement quand l'autre finissant, on renvoie la duree
                
                return lesContraintes->durees[colonne];
                
            } else {
                //cout << "Tache differente" << endl << endl;
            }
        }
        return -1;
    }
    
    
}


int loading(string id_graph, tt_contraintes* lesContraintes, tt_graphe* leGraphe)
{
    
    ifstream myStream (id_graph, ios::in);
    
    if (myStream) {
        
        cout << "\nLecture de tableau de contraintes" << endl;
        
        
        char tacheCourante, contrainteCourante;
        //int indiceTacheCourante;
        int dureeTache;
        
        myStream >> lesContraintes->nbTaches;
        
        cout<< "\nNombre de taches : "<< lesContraintes->nbTaches << endl;
        lesContraintes->nomTaches = new char[lesContraintes->nbTaches+1]; // Indices 1 à nbTaches utilisés. Case 0 non utilisée
        lesContraintes->durees = new int[lesContraintes->nbTaches+1]; // Indices 1 à nbTaches utilisés. Case 0 non utilisée
        
        
        
        cout << "\ndurees : " << endl;
        for (int t = 1; t <= lesContraintes->nbTaches; t++)
        {
            myStream >> tacheCourante;
            lesContraintes->nomTaches[t] = tacheCourante;
            myStream >> dureeTache;
            lesContraintes->durees[t] = dureeTache;
            //printf("%c %2d\n", tacheCourante, lesContraintes->durees[t]);
            cout << lesContraintes->nomTaches[t] << " " << lesContraintes->durees[t] << endl;
        };
        
        
        cout << "\nContraintes : " << endl;
        for (int t = 1; t <= lesContraintes->nbTaches; t++)
        {
            int cpt = 0;
            myStream >> tacheCourante;
            myStream >> contrainteCourante;
            while (contrainteCourante != '.')
            {
                cpt++;
                //cout << tacheCourante << " ne peut commencer que lorsque la tache " << contrainteCourante << " est terminee" << endl;
                ajouterContrainte(lesContraintes, tacheCourante, contrainteCourante, cpt);
                myStream >> contrainteCourante;
            };
            afficher_contrainte(lesContraintes, tacheCourante);
            
        };
        
        cout << endl << endl;
        
        
        leGraphe->nbSommets = lesContraintes->nbTaches+2;
        // début = lesContraintes->nbTaches+1
        // fin = lesContraintes->nbTaches+2
        
        leGraphe->adj = new bool* [leGraphe->nbSommets +1]; // ligne 0 non utilisée
        leGraphe-> val = new int* [leGraphe->nbSommets +1]; // idem
        
        for (int ligne = 1; ligne <= leGraphe->nbSommets; ligne++)
        {
            leGraphe->adj[ligne] = new bool[leGraphe->nbSommets +1];
            leGraphe->val[ligne] = new int[leGraphe->nbSommets +1];
            
            for (int colonne = 1; colonne <= leGraphe->nbSommets; colonne++)
            {
                int duree = fill_graph(lesContraintes, ligne, colonne, true);
                if (duree == -1) {
                    leGraphe->adj[ligne][colonne] = false;
                } else if (duree == -2) {
                    leGraphe->adj[ligne][colonne] = false;
                    break;
                    //cette condition est lorsqu'il y a aucune contrainte, on s'embête pas à tester toutes les colonnes
                } else {
                    leGraphe->adj[ligne][colonne] = true;
                    leGraphe->val[ligne][colonne] = duree;
                }
            };
        };
    
        //print_graph_adjacence_reverse(lesContraintes, leGraphe);
        
        return 1;
    } else {
        return 0;
    }
    
}

























