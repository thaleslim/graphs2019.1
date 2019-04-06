/**
 * @author Thales Menezes @thaleslim
 * @date   06/04/2019
 */

#ifndef __NETWORK_H__
#define __NETWORK_H__

#include <bits/stdc++.h>

using namespace std;

bool   fread_until     (ifstream& file, string target, bool stop_before = false);
string fread_after     (ifstream& file, string pre, string delimiter = "\n");
int    print_graph     (map<int,vector<int>> & graph);
bool   create_network  (ifstream& file, map<int,vector<int>>& graph);
bool   fread_edge      (ifstream& file, map<int,vector<int>>& graph);

#endif