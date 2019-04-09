/**
 * @author Thales Menezes @thaleslim
 * @date   06/04/2019
 */

#ifndef __NETWORK_H__
#define __NETWORK_H__

#include <bits/stdc++.h>

using namespace std;

bool    file_find        (ifstream& file, string target, bool stop_before = false);
string  file_read        (ifstream& file, string begin, string end = "\n");
int     print_graph      (map<int,vector<int>> & graph);
bool    create_network   (ifstream& file, map<int,vector<int>>& graph);
bool    fget_edge        (ifstream& file, map<int,vector<int>>& graph);

#endif