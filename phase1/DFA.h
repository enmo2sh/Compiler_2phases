#ifndef DFA_H
#define DFA_H
#include <iostream>
#include <vector>
#include <map>
#include "structures.h"
#include <bits/stdc++.h>
using namespace std;


struct DFA_State{
    int id;
    bool accept_state_flag = false; //0 not accepting ,1 for accepting.
    string name="";
    int priority = 0;
    set <state*> subset;
    set <int> subset_ids; //of NFA_state
    map <string, set<state*>> symbols; //string represents the content of input_symbol
    map <string, set<int>> Group_ids; //vector represents move+epsilon transitions
};

struct DFA_Graph{ //represent the node .
    bool acceptance_state;
    string name = "";
    int priority = 0;
    map<string, int> next_state;  //under input go to id of next state .
};

map<int, DFA_Graph> Subset_Construction(state* original);
void Move_To(DFA_State *Basic_node);
void test(DFA_State *Basic_node);
map<int, DFA_Graph> get_graph ();
void print_graph(map<int, DFA_Graph> graph);
#endif
