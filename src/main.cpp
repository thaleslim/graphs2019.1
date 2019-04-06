/**
 * @author Thales Menezes @thaleslim
 * @date   06/04/2019
 */

#include <bits/stdc++.h>
#include "../headers/network.hpp"

using namespace std;

#define print printf

int main(){
    map<int,vector<int>> graph;
    ifstream file;
    file.open("resources/karate.gml");

    if(file.is_open()){
        create_network(file,graph);
        file.close();
        print_graph(graph);
    }else
        print("ERROR: file could not be openned");

    return 0;
}
