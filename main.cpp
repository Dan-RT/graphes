//
//  main.cpp
//  Projet Graphes
//
//  Created by Daniel Regnard on 12/12/2016.
//  Copyright © 2016 A. All rights reserved.
//

#include <iostream>
#include "load.hpp"
#include "course_fonctions.hpp"


int main(int argc, const char * argv[]) {
   
    string id_graph = "";
    
    cout << "ENTER THE NUMBER OF YOUR GRAPH :" << endl;
    cin >> id_graph;
    
    id_graph = chooseGraph(id_graph);
    cout << id_graph << endl;
    
    //if (loading_graph(id_graph)) {
    if (loading(id_graph)) {
        cout << "\nLoading successed" << endl;
    } else {
        cout << "\nLoading failed" << endl;
    }
    return 0;
}
