//
//  load.cpp
//  Projet Graphes
//
//  Created by Daniel Regnard on 12/12/2016.
//  Copyright © 2016 A. All rights reserved.
//

#include "load.hpp"


string chooseAutomate(string number)  // fonction qui recupere le nom d'un fichier
{
    string b(".txt");
    
    return number+b;
}


int loading_graph(string id_graph) {
    
    all_obligations current_graph_obligations;
    all_graph current_graph;
    int data = 0;
    char data_char;
    
    ifstream myStream(id_graph);
    if (myStream) {
        
        myStream >> current_graph_obligations.nbTasks;  //on récupère le nb de tâches
        
        for (int i = 0; i < current_graph_obligations.nbTasks; i++) {
            myStream >> data_char;
            current_graph_obligations.nameTasks.push_back(data_char);
            
            myStream >> data;
            current_graph_obligations.duration.push_back(data);
            
        }
        
        //current_graph.nb_nodes = current_graph_obligations.nbTasks + 2;
        
        display_memory_content(current_graph_obligations);
        
        
        return 1;
    } else {
        
        return 0;
    }
}


void display_memory_content (all_obligations current_graph_obligations) {
    
    cout << "\nNumber of tasks : " << current_graph_obligations.nbTasks << endl;
    
    for (int i = 0; i < current_graph_obligations.nbTasks; i++) {
        cout << current_graph_obligations.nameTasks[i] << " " << current_graph_obligations.duration[i] << endl;
    }
    
}


















