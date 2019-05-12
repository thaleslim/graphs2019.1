/**
 * @author Thales Menezes @thaleslim
 * @date   11/05/2019
 */

#ifndef __DIGRAPH_H__
#define __DIGRAPH_H__

#include <bits/stdc++.h>

using namespace std;

bool        file_find     (ifstream& file, string target, bool stop_before = false);
string      file_read     (ifstream& file, string begin, string end = "\n");
string      get_substr    (string str, size_t begin = 0, char sep = ' ', char end = '\n');
bool        graph_init    (ifstream& file, map<int,set<int>> & digraph, map<int,int> & weight);
int         graph_print   (map<int,set<int>> & graph, map<int,int> & weight);
/*bool        graph_insert  ();
vector<int> graph_path    ();   // Djkistra
bool        graph_ordered ();   // ordenação topológica
bool        graph_dump    (ifstream& file); */

#endif