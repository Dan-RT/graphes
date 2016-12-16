//
//  load.hpp
//  Projet Graphes
//
//  Created by Daniel Regnard on 12/12/2016.
//  Copyright © 2016 A. All rights reserved.
//

#ifndef load_hpp
#define load_hpp

#include <iostream>
#include <stdio.h>
#include <fstream>
using namespace std;
#include <vector>
#include <map>


string chooseGraph(string number);
int loading_graph(string id_graph);

typedef struct {
    
    int nbTasks;
    map<int, string> nameTasks;
    map<int, int> duration;
    
} all_obligations;

typedef struct {
    
    /*
    int nb_nodes;
    vector<vector<bool>>
    bool** adj;
    int** val;
    */
     
} all_graph;


void display_memory_content (all_obligations current_graph);

#endif /* load_hpp */
