#include <bits/stdc++.h>
#include "../headers/digraph.hpp"

using namespace std;
#define print printf

map< int, set<int> > digraph; // conections
map< int, int > weight;     // weights

int main(){
    ifstream file;
    file.open("cic.gml");
    graph_init(file,digraph,weight);
    file.close();
    print("Bacharelado em Ciência da Computação\n");
    print("disciplina [nº creditos] -> { dependentes }\n");
    graph_print(digraph,weight);
    return 0;
}