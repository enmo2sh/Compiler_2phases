#ifndef MINIMIZATION_H
#define MINIMIZATION_H

#include <iostream>
#include <map>
#include "DFA.h"
using namespace std;

map<int, DFA_Graph> minimize_graph(map<int, DFA_Graph> graph);
vector<set<int>> table_filling(map<int, DFA_Graph> graph);
void join_states(vector<set<int>> &equivalent_states, int id1, int id2);
map<int, DFA_Graph> minimized(map<int, DFA_Graph> graph, vector<set<int>> equivalent_states);
string get_pointer_id(int id, map<int, DFA_Graph> graph);

#endif
