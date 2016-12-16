#include <iostream>
#include <fstream>
#include "course_fonctions.hpp"

using namespace std;

void ajouterContrainte(tt_contraintes* lesContraintes, char tacheCourante, char contrainteCourante, int cpt) {
    
    lesContraintes->contraintes[tacheCourante].push_back(contrainteCourante);
    
}

void afficher_contrainte (tt_contraintes* lesContraintes, char name_contrainte) {
    
    /*vector<string> tab;    //Un tableau de mots
    
    tab.push_back("les"); //On ajoute deux mots dans le tableau
    tab.push_back("Zeros");
    
    tab.insert(tab.begin(), "Salut"); //On insère le mot "Salut" au début
    
    //Affiche les mots donc la chaîne "Salut les Zeros"
    
    for(vector<string>::iterator it=tab.begin(); it!=tab.end(); ++it)
    {
        cout << *it << " ";
    }*/
    
    
    for(vector<char>::iterator it= lesContraintes->contraintes[name_contrainte].begin(); it!=lesContraintes->contraintes[name_contrainte].end(); ++it) {
        
        cout << "Test : " << name_contrainte << " ne peut commencer que lorsque la tache " << *it << " est terminee" << endl;
    }
    
}





void free_memory (tt_contraintes* lesContraintes, tt_graphe* leGraphe) {
    
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


int loading(string id_graph)
{
    
    ifstream myStream (id_graph, ios::in);
    
    if (myStream) {
        
        cout << "Lecture de tableau de contrainte" << endl;
        
        tt_contraintes* lesContraintes = new tt_contraintes;
        char tacheCourante, contrainteCourante;
        int indiceTacheCourante, dureeTache;
        
        myStream >> lesContraintes->nbTaches;
        
        cout<< "Nombre de taches : "<< lesContraintes->nbTaches << endl;
        lesContraintes->nomTaches = new char[lesContraintes->nbTaches+1]; // Indices 1 à nbTaches utilisés. Case 0 non utilisée
        lesContraintes->durees = new int[lesContraintes->nbTaches+1]; // Indices 1 à nbTaches utilisés. Case 0 non utilisée
        
        
        
        cout << "durees : " << endl;
        for (int t = 1; t <= lesContraintes->nbTaches; t++)
        {
            myStream >> tacheCourante;
            lesContraintes->nomTaches[t] = tacheCourante;
            myStream >> dureeTache;
            lesContraintes->durees[t] = dureeTache;
            printf("%c %2d\n", tacheCourante, lesContraintes->durees[t]);
            cout << lesContraintes->nomTaches[t] << " " << lesContraintes->durees[t] << endl << endl;
        };
        
        cout << endl << endl;
        
        cout << "Contraintes : " << endl;
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
        
        tt_graphe* leGraphe =  new tt_graphe;
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
                leGraphe->adj[ligne][colonne] = false;
            };
        };
        
        
        cout << "Graphe genere" <<endl;
        for (int ligne = 1; ligne <= leGraphe->nbSommets; ligne++)
        {
            cout << ligne << " ";
            for (int colonne = 1; colonne <=leGraphe->nbSommets; colonne++)
            {
                if (leGraphe->adj[ligne][colonne])
                {
                    cout << 1 << " ";
                }
                else
                {
                    cout << 0 << " ";
                };
            };
            cout <<endl;
        };
        
        free_memory(lesContraintes, leGraphe);
        return 1;
    } else {
        return 0;
    }
    
}

