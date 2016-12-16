#include <iostream>
#include <fstream>
#include "course_fonctions.hpp"

using namespace std;

void ajouterContrainte(tt_contraintes* lesContraintes, char tacheCourante, char contrainteCourante)
{
    int i = 0;
    lesContraintes->nomTaches[i] = tacheCourante;
}


int loading(string id_graph)
{
    
    ifstream myStream (id_graph, ios::in);
    
    if (myStream) {
        
        cout << "Lecture de tableau de contrainte" <<endl;
        
        tt_contraintes* lesContraintes = new tt_contraintes;
        char tacheCourante, contrainteCourante;
        int indiceTacheCourante, dureeTache;
        myStream >> lesContraintes->nbTaches;
        cout<< "Nombre de taches : "<< lesContraintes->nbTaches <<endl;
        lesContraintes->nomTaches = new char[lesContraintes->nbTaches+1];
        lesContraintes->durees = new int[lesContraintes->nbTaches+1];
        cout << "durees : " << endl;
        for (int t = 1; t <= lesContraintes->nbTaches; t++)
        {
            myStream >> tacheCourante;
            lesContraintes->nomTaches[t] = tacheCourante;
            myStream >> dureeTache;
            lesContraintes->durees[t] = dureeTache;
            printf("%c %2d\n", tacheCourante, lesContraintes->durees[t]);
        };
        
        cout <<endl <<endl;
        
        cout << "Contraintes : " << endl;
        for (int t = 1; t <= lesContraintes->nbTaches; t++)
        {
            myStream >> tacheCourante;
            myStream >> contrainteCourante;
            while (contrainteCourante != '.')
            {
                cout << tacheCourante << " ne peut commencer que lorsque la tache " << contrainteCourante << " est terminee" <<endl;
                ajouterContrainte(lesContraintes, tacheCourante, contrainteCourante);
                myStream >> contrainteCourante;
            };
        };
        
        cout <<endl <<endl;
        
        tt_graphe* leGraphe =  new tt_graphe;
        leGraphe->nbSommets = lesContraintes->nbTaches+2;
        leGraphe->adj = new bool* [leGraphe->nbSommets +1];
        leGraphe-> val = new int* [leGraphe->nbSommets +1];
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
        
        return 1;
    } else {
        return 0;
    }
    
}

